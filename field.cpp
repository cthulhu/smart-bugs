#define __TRACE

#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>
#if defined(__TRACE)
#include <conio.h>
#include "trace.h"
#endif
#include "exept.h"
#include "utils.h"
#include "field.h"
// for debugin information


#if defined(__TRACE)
std::ofstream LogField;
#endif


bool Field::LoadField(std::string strFileName)
{
    std::ifstream inField(strFileName.c_str());
	if(inField == NULL)
    {
		throw eExeption("Can't open the source file.");
    }
    std::string tmp;

    while(std::getline(inField,tmp))
    {
        if(tmp.find("#name") < tmp.size())
        {
#if defined (__TRACE)
            assert(tmp.find("=") + 1 != tmp.size());
#endif

            strFieldName = tmp.substr(tmp.find("=") + 1);
#if defined (__TRACE)

            LogField <<"The field name is "<< strFieldName << std::endl;
		//  std::cout <<"The field name is "<< strFieldName << std::endl;
#endif

        }
        else if(tmp.find("#num_of_bugs") < tmp.size())
        {
            iNumOfBugs = atoi((tmp.substr(tmp.find("=") + 1)).c_str());
#if defined (__TRACE)

            assert((tmp.find("=")+ 1) != tmp.length());
#endif

            vecBugsOnTheField.reserve(iNumOfBugs);
            vecBugsOnTheField.assign(iNumOfBugs,Field::_BUG_INFOR_());
#if defined (__TRACE)

            // std::cout <<"There are (is) "<< iNumOfBugs << " bugs on the field"<< std::endl;
            LogField <<"There are (is) "<< iNumOfBugs << " bugs on the field"<< std::endl;
#endif

        }
        else if(tmp.find("#map") < tmp.size())
        {
            std::getline(inField,tmp);
            unsigned int i = 0;
            do
            {

                vecField.push_back(std::vector<unsigned short>::vector(tmp.size()));
                for(unsigned int j = 0;j < tmp.size();++j)
                {
                    vecField[i][j] = ConvertFieldCell(tmp[j]);
                    if(((vecField[i][j])&0xff) == CellTypes::eBug)
                    {
#if defined (__TRACE)
                        assert((short)((ConvertFieldCell(tmp[j]) >> 8)) - 1 >= 0);
#endif

                        vecBugsOnTheField[(short)((ConvertFieldCell(tmp[j]) >> 8)) - 1].SetBugPosition(j,i);
                        vecBugsOnTheField[(short)((ConvertFieldCell(tmp[j]) >> 8)) - 1].SetBugLookDirection(rand() % BugDirections::eImpossibleLookDirection);
                    }
#if defined (__TRACE)

                    if(vecField[i][j] >> 8)
                    {
                        //std ::cout <<(int)(vecField[i][j] >> 8)<< (char)vecField[i][j];
                        LogField <<(char)vecField[i][j];
                    }
                    else
                    {
                        //std ::cout <<(char)(vecField[i][j] >> 8)<< (char)vecField[i][j];
                        LogField <<(char)vecField[i][j];
                    }
#endif
                    if(((vecField[i][j])&0xff) == CellTypes::eExit)
                    {
                        posExit = Position(j,i);
                    }
                }
                ++i;
#if defined (__TRACE)

                //std ::cout << std::endl;
                LogField << std::endl;

#endif

            }
            while(std::getline(inField,tmp));
        }
        else if(tmp.find("#") < tmp.size())
        {
            static unsigned int iCountOfBugs = 0;
            if(iCountOfBugs == iNumOfBugs)
            {
                continue;
            }
#if defined (__TRACE)
            assert(tmp.find("=") + 1 < tmp.length());
#endif

            vecBugsOnTheField[iCountOfBugs].SetBugName(tmp.substr(tmp.find("=") + 1));
#if defined (__TRACE)

            assert(tmp.find("#") + 1 != tmp.find("="));
#endif

            vecBugsOnTheField[iCountOfBugs].SetBugNum(atoi((tmp.substr(tmp.find("#") + 1,tmp.find("="))).c_str()));
#if defined (__TRACE)

            //std ::cout << vecBugsOnTheField[iCountOfBugs].GetBugNum()
            //<< " is " << vecBugsOnTheField[iCountOfBugs].GetBugName() << std::endl;
            LogField << vecBugsOnTheField[iCountOfBugs].GetBugNum()
            << " is " << vecBugsOnTheField[iCountOfBugs].GetBugName() << std::endl;
#endif

            ++iCountOfBugs;
        }
        // this is for comments in the file
        else if(tmp.find("//") < tmp.size())
        {
            continue;
        }
        // wrong file format
        else
        {}
    }
#if defined (__TRACE)

    for(unsigned int __i__ = 0;__i__ < iNumOfBugs; ++__i__)
    {
        __TRACE_INFOR::trace _TRACE_INFORMATION_;

//        std ::cout << vecBugsOnTheField[__i__].GetBugPosition().x << " "
//        << vecBugsOnTheField[__i__].GetBugPosition().y
//        << ". The Bug is looking to the "
//        << _TRACE_INFORMATION_.GetLookDirectionsByNumber(vecBugsOnTheField[__i__].GetBugLookDirection())
//        << " is " << vecBugsOnTheField[__i__].GetBugName() << std::endl;
        LogField << vecBugsOnTheField[__i__].GetBugPosition().x << " "
        << vecBugsOnTheField[__i__].GetBugPosition().y
        << ". The Bug is looking to the "
        << _TRACE_INFORMATION_.GetLookDirectionsByNumber(vecBugsOnTheField[__i__].GetBugLookDirection())
        << " is " << vecBugsOnTheField[__i__].GetBugName() << std::endl;
    }
//    std ::cout <<"Exit is in the ("<< posExit.x << ", "<< posExit.y << ")" << std::endl;
    LogField << "Exit is in the (" << posExit.x << ", "<< posExit.y << ")" << std::endl;
#endif

    return true;
}
void Field::_BUG_INFOR_::SetBugName(std::string strBName)
{
#if defined (__TRACE)
    assert(!strBName.empty());
#endif

    strBugName = strBName;
}
std::string  Field::_BUG_INFOR_::GetBugName(void)
{
    return strBugName;
}

void Field::_BUG_INFOR_::SetBugNum(unsigned int cBNum)
{
#if defined (__TRACE)
    assert(cBNum >= 0);
#endif

    cBagNum = cBNum;
}

unsigned int Field::_BUG_INFOR_::GetBugNum(void)
{
    return cBagNum;
}
void Field::_BUG_INFOR_::SetBugPosition(Position pNewBugPosition)
{
    pBugPosition = pNewBugPosition;
}
void Field::_BUG_INFOR_::SetBugPosition(short nNewX,short nNewY)
{
    pBugPosition.x = nNewX;
    pBugPosition.y = nNewY;
}
Position Field::_BUG_INFOR_::GetBugPosition(void)
{
    return pBugPosition;
}
Field::Field(std::string strFileName)
{
#if defined (__TRACE)
    assert(!strFileName.empty());
#endif

#if defined (__TRACE)

    LogField.open("__TraceField.log");
#endif

    strFieldFile = strFileName;
    strFieldName = "";
    iNumOfBugs = 0;
    vecField.reserve(0);
    LoadField(strFileName);
}
Field::Field()
{
#if defined (__TRACE)
    LogField.open("__TraceField.log");
#endif

    posExit.x = 0;
    posExit.y = 0;
    strFieldFile = "";
    strFieldName = "";
    iNumOfBugs = 0;
    vecField.reserve(0);
}
unsigned short Field::ConvertFieldCell(char cell)
{
    if((cell >= 0x30 && cell <= 0x39)
            ||(cell >= 0x41 && cell <= 0x5a)
            ||(cell >= 0x61 && cell <= 0x7a))
    {
        return ((atoi(&cell) << 8)| CellTypes::eBug);
    }
    else
    {
        switch(cell)
        {
            case '&':
                return CellTypes::eWall;
            case ' ':
                return CellTypes::eClear;
            case '*':
                return CellTypes::eFood;
            case '@':
                return CellTypes::eExit;
            default:
                assert(false);
#if defined (__TRACE)

//                std::cout << cell << std::endl;
                LogField << "Undefined cell type - " << cell << std::endl;
#endif

        }
    }
    return 0;
}
void Field::AskToBug(unsigned int nBugAction,unsigned int nBugNum)
{

    assert(nBugAction <= BugActions::eImpossibleAction);
#if defined (__TRACE)

    __TRACE_INFOR::trace __TRACE_;
    //	LogField << "Let's look to bug number "<< nBugNum
    //	<< ". He's going to " << __TRACE_.GetActionByNumber(nBugAction) <<std::endl;
#endif

    switch(nBugAction)
    {
            // do nothing
        case BugActions::eStaying:
            break;
            // eat some food
        case BugActions::eEating:
            {
                Position pPos = GetBugPosition(nBugNum);
                if((GetCell(pPos) & 0xf) == CellTypes::eFood)
                    vecField[pPos.y][pPos.x] &=~ CellTypes::eFood;
                break;
            }
        case BugActions::eTracing:
            {
                Position pPos = GetBugPosition(nBugNum);
                vecField[pPos.y][pPos.x] |= CellTypes::eTrace;
                break;
            }
        case BugActions::eMoving:
            {
                BugMoveForward(nBugNum);
                break;
            }
        case BugActions::eRotatingLeft:
            {
                BugRotateLeft(nBugNum);
                break;
            }
        case BugActions::eRotatingRight:
            {
                BugRotateRight(nBugNum);
                break;
            }
        default:
            assert(false);
    }
}
bool Field::CanGo(Position pos, unsigned short nBugLookDirection)
{
    switch(nBugLookDirection)
    {
        case BugDirections::eWestLook:
            {
                if((vecField[pos.y][--pos.x] & 0xff) != CellTypes::eWall)
                    return true;
                else
                    break;
            }
        case BugDirections::eEastLook:
            {
                if((vecField[pos.y][++pos.x] & 0xff) != CellTypes::eWall)
                    return true;
                else
                    break;
            }
        case BugDirections::eSouthLook:
            {
                if((vecField[++pos.y][pos.x] & 0xff) != CellTypes::eWall)
                    return true;
                else
                    break;
            }
        case BugDirections::eNorthLook:
            {
                if((vecField[--pos.y][pos.x] & 0xff) != CellTypes::eWall)
                    return true;
                else
                    break;
            }
        default:
            assert(false);
    }
    return false;
}
void Field::BugMoveForward(unsigned int nBugNum)
{
    Position pos = GetBugPosition(nBugNum);
    Position oldPos = GetBugPosition(nBugNum);
    unsigned int nBugLookDir = GetBugLookDirection(nBugNum);
    switch(nBugLookDir)
    {
        case BugDirections::eWestLook:
            {
                if(CanGo(pos,BugDirections::eWestLook))
                {
                    --pos.x;
#if defined (__TRACE)
                    //			LogField << "He can go West"<<std::endl;
#endif

                }
                break;
            }
        case BugDirections::eEastLook:
            {
                if(CanGo(pos,BugDirections::eEastLook))
                {
                    ++pos.x;
#if defined (__TRACE)
                    //			LogField << "He can go East"<<std::endl;
#endif

                }
                break;
            }
        case BugDirections::eSouthLook:
            {
                if(CanGo(pos,BugDirections::eSouthLook))
                {
                    ++pos.y;
#if defined (__TRACE)
                    //			LogField << "He can go South"<<std::endl;
#endif

                }
                break;
            }
        case BugDirections::eNorthLook:
            {
                if(CanGo(pos,BugDirections::eNorthLook))
                {
#if defined (__TRACE)
                    //			LogField << "He can go South"<<std::endl;
#endif
                    --pos.y;
                }
                break;
            }
        default:
            assert(false);
    }
    if(pos == posExit)
    {
        bAnyBugOnTheExit = true;
        nTheBugAtTheExit = nBugNum;
#if defined (__TRACE)

        LogField << "Bug number "<< nBugNum << " riched the exit" << std::endl;
#endif

    }
    else
    {
        vecField[pos.y][pos.x] |= vecField[oldPos.y][oldPos.x];
        vecField[oldPos.y][oldPos.x] &=0xf;
        SetBugPosition(nBugNum,pos);
    }
#if defined (__TRACE)
    // LogField << "Let's move forward bug number "<< nBugNum << std::endl;
#endif
}
void Field::BugRotateLeft(unsigned int nBugNum)
{
    switch(GetBugLookDirection(nBugNum))
    {
        case BugDirections::eWestLook:
            SetBugLookDirection(nBugNum,BugDirections::eSouthLook);
            break;
        case BugDirections::eEastLook:
            SetBugLookDirection(nBugNum,BugDirections::eNorthLook);
            break;
        case BugDirections::eSouthLook:
            SetBugLookDirection(nBugNum,BugDirections::eEastLook);
            break;
        case BugDirections::eNorthLook:
            SetBugLookDirection(nBugNum,BugDirections::eWestLook);
            break;
        default:
            assert(false);
    }
#if defined (__TRACE)
    // LogField << "Let's rotate left bug number "<< nBugNum << std::endl;
#endif
}
void Field::BugRotateRight(unsigned int nBugNum)
{
    switch(GetBugLookDirection(nBugNum))
    {
        case BugDirections::eWestLook:
            SetBugLookDirection(nBugNum,BugDirections::eNorthLook);
            break;
        case BugDirections::eEastLook:
            SetBugLookDirection(nBugNum,BugDirections::eSouthLook);
            break;
        case BugDirections::eSouthLook:
            SetBugLookDirection(nBugNum,BugDirections::eWestLook);
            break;
        case BugDirections::eNorthLook:
            SetBugLookDirection(nBugNum,BugDirections::eEastLook);
            break;
        default:
            assert(false);
    }
#if defined (__TRACE)
    // LogField << "Let's rotate right bug number "<< nBugNum << std::endl;
#endif
}
void Field::SetBugLookDirection(unsigned int nBugNum,unsigned short nBugLookDirection)
{
    std::vector<_BUG_INFOR_>::iterator iNum;
    for(iNum = vecBugsOnTheField.begin();iNum != vecBugsOnTheField.end(); ++ iNum)
    {
        if(iNum->GetBugNum() == nBugNum)
        {
            iNum->SetBugLookDirection(nBugLookDirection);
            break;
        }
    }

}
void Field::SetBugPosition(unsigned int nBugNum,Position pos)
{
#if defined (__TRACE)
    for(unsigned int __i__ = 0;__i__ < vecField.size(); ++__i__)
    {
        for(unsigned int __j__ = 0;__j__ < vecField[__i__].size(); ++__j__)
        {
           /* if(vecField[__i__][__j__] >> 8)
            {
                LogField <<(int)(vecField[__i__][__j__] >> 8)<< (char)vecField[__i__][__j__];
                std::cout <<(int)(vecField[__i__][__j__] >> 8)<< (char)vecField[__i__][__j__];
            }
            else
            {*/
               // LogField << (char)(vecField[__i__][__j__] >> 8)<< (char)vecField[__i__][__j__];
                LogField << (char)vecField[__i__][__j__];
               // std::cout << (char)(vecField[__i__][__j__] >> 8)<< (char)vecField[__i__][__j__];
           // }
        }
        LogField << std::endl ;//<< std::endl;
        //std::cout << std::endl<< std::endl;
    }
    LogField << std::endl;
    //std::cout << std::endl << std::endl;

#endif

    std::vector<_BUG_INFOR_>::iterator iNum;
    for(iNum = vecBugsOnTheField.begin();iNum != vecBugsOnTheField.end(); ++ iNum)
    {
        if(iNum->GetBugNum() == nBugNum)
        {
            iNum->SetBugPosition(pos);
            break;
        }
    }

}
void Field::_BUG_INFOR_::SetBugLookDirection(unsigned short nNewBugLookDirection)
{
    assert(nNewBugLookDirection >= 0);
    nBugLookDirection = nNewBugLookDirection;
}
unsigned short Field::_BUG_INFOR_::GetBugLookDirection(void)
{
    return nBugLookDirection;
}
unsigned int Field::GetNumberOfBugs(void)
{
    return iNumOfBugs;
}
Position Field::GetBugPosition(unsigned int nBugNum)
{
    assert(nBugNum >= 0);
    std::vector<_BUG_INFOR_>::iterator iNum;
    for(iNum = vecBugsOnTheField.begin();iNum != vecBugsOnTheField.end(); ++ iNum)
        if(iNum->GetBugNum() == nBugNum)
            break;
    return iNum->GetBugPosition();
}
unsigned short Field::GetBugLookDirection(unsigned int nBugNum)
{
    assert(nBugNum >= 0);
    std::vector<_BUG_INFOR_>::iterator iNum;
    for(iNum = vecBugsOnTheField.begin();iNum != vecBugsOnTheField.end(); ++ iNum)
        if(iNum->GetBugNum() == nBugNum)
            break;
    return iNum->GetBugLookDirection();
}
Position Field::CorrectToLookDirection(Position pPositionOfTheBug,
                                       unsigned short nBugLookDirection, unsigned int nTestPlace)
{
    switch(nBugLookDirection)
    {
        case BugDirections::eNorthLook:
            {
                switch(nTestPlace)
                {
                    case TestPlace::forward:
                        {
                            pPositionOfTheBug.y --;
                            return pPositionOfTheBug;
                        }
                    case TestPlace::lefthand:
                        {
                            pPositionOfTheBug.x --;
                            return pPositionOfTheBug;
                        }
                    case TestPlace::righthand:
                        {
                            pPositionOfTheBug.x ++;
                            return pPositionOfTheBug;
                        }
                    default:
                        assert(false);
                }
                break;
            }
        case BugDirections::eEastLook:
            {
                switch(nTestPlace)
                {
                    case TestPlace::forward:
                        {
                            pPositionOfTheBug.x ++;
                            return pPositionOfTheBug;
                        }
                    case TestPlace::lefthand:
                        {
                            pPositionOfTheBug.y --;
                            return pPositionOfTheBug;
                        }
                    case TestPlace::righthand:
                        {
                            pPositionOfTheBug.y ++;
                            return pPositionOfTheBug;
                        }
                    default:
                        assert(false);
                }
                break;
            }
        case BugDirections::eWestLook:
            {
                switch(nTestPlace)
                {
                    case TestPlace::forward:
                        {
                            pPositionOfTheBug.x --;
                            return pPositionOfTheBug;
                        }
                    case TestPlace::lefthand:
                        {
                            pPositionOfTheBug.y ++;
                            return pPositionOfTheBug;
                        }
                    case TestPlace::righthand:
                        {
                            pPositionOfTheBug.y --;
                            return pPositionOfTheBug;
                        }
                    default:
                        assert(false);
                }
                break;
            }
        case BugDirections::eSouthLook:
            {
                switch(nTestPlace)
                {
                    case TestPlace::forward:
                        {
                            pPositionOfTheBug.y ++;
                            return pPositionOfTheBug;
                        }
                    case TestPlace::lefthand:
                        {
                            pPositionOfTheBug.x ++;
                            return pPositionOfTheBug;
                        }
                    case TestPlace::righthand:
                        {
                            pPositionOfTheBug.x --;
                            return pPositionOfTheBug;
                        }
                    default:
                        assert(false);
                }

                break;
            }
        default:
            assert(false);
    }
    return pPositionOfTheBug;
}
unsigned short Field::GetCell(Position pPosCell)
{
    return vecField[pPosCell.y][pPosCell.x] & 0xff;
}
unsigned short Field::WhatIsForward(unsigned int nBugNum)
{
    int i = GetCell(CorrectToLookDirection(GetBugPosition(nBugNum),GetBugLookDirection(nBugNum),TestPlace::forward));
    return i;
}
unsigned short Field::WhatIsHere(unsigned int nBugNum)
{
    return GetCell(GetBugPosition(nBugNum)) & 0xf;
}
unsigned short Field::WhatIsLeft(unsigned int nBugNum)
{
    return GetCell(CorrectToLookDirection(GetBugPosition(nBugNum),GetBugLookDirection(nBugNum),TestPlace::lefthand));
}
unsigned short Field::WhatIsRight(unsigned int nBugNum)
{
    return GetCell(CorrectToLookDirection(GetBugPosition(nBugNum),GetBugLookDirection(nBugNum),TestPlace::righthand));
}
std::string Field::GetBugName(unsigned int nBugNum)
{
#if defined (__TRACE)
    assert(nBugNum <= iNumOfBugs);
#endif

    return vecBugsOnTheField[nBugNum].GetBugName();
}
Field::~Field()
{
    LogField.close();
}
void Field::RemoveBug(unsigned int nBugNum)
{
    iNumOfBugs --;
    std::vector<_BUG_INFOR_>::iterator itBugToRemove;
    for(itBugToRemove = vecBugsOnTheField.begin();
            itBugToRemove != vecBugsOnTheField.end();++itBugToRemove)
    {
        if((*itBugToRemove).GetBugNum() == nBugNum)
        {
            break;
        }
    }
    vecField[((*itBugToRemove).GetBugPosition()).y][((*itBugToRemove).GetBugPosition()).x] &= 0xf;
    vecBugsOnTheField.erase(itBugToRemove);
}
unsigned int Field::WhatBugIsOntheExit(void)
{
    return nTheBugAtTheExit;
}
bool Field::IsAnyBugAtTheExit()
{
    if(bAnyBugOnTheExit)
    {
        bAnyBugOnTheExit = false;
        return true;
    }
    else
    {
        return false;
    }
}
