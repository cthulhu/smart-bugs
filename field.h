#ifndef _FIELD_H_
#define _FIELD_H_

// for debuging and tracing
#define __TRACE
/// @class Field
/// Main class to manage the labyrinth with the bugs
class Field
{
protected:
    /// @class _BUG_INFOR_
    /// class to collect information
    /// about bugs
    class _BUG_INFOR_
    {

        /// The number of the bug in the labyrinth
        unsigned int cBagNum;
        /// The name of he bug in the labyrinth
        std::string strBugName;
        /// Coordinates of the bug in the labirynth
        Position pBugPosition;
        /// Bug look direction
        unsigned short nBugLookDirection;
    public:
        /// constructor
        /// @param cBNum The number of the bug in the labyrinth
        /// @param strBName The name of the bug in the labirynth
        _BUG_INFOR_(unsigned int cBNum,std::string strBName):
                cBagNum(cBNum),strBugName(strBName),pBugPosition()
        {}
        /// default constructor
        _BUG_INFOR_():cBagNum(0),strBugName(""),pBugPosition()
        {}
        void SetBugName(std::string strBName);
        std::string GetBugName(void);

        void SetBugNum(unsigned int cBNum);
        unsigned int GetBugNum(void);

        void SetBugPosition(Position pNewBugPosition);
        void SetBugPosition(short nNewX,short nNewY);
        Position GetBugPosition(void);
        void GetBugPosition(short &nPosX,short &nPosY);

        void SetBugLookDirection(unsigned short nNewBugLookDirection);
        unsigned short GetBugLookDirection(void);
    };

    std::vector<std::vector<unsigned short> > vecField;
    std::vector<_BUG_INFOR_> vecBugsOnTheField;
    std::string strFieldFile;
    std::string strFieldName;
    Position posExit;
    unsigned int iNumOfBugs;
    bool bAnyBugOnTheExit;
    unsigned int nTheBugAtTheExit;
private:
    unsigned short ConvertFieldCell(char cell);
    unsigned short GetCell(Position pPosCell);

    void BugMoveForward(unsigned int nBugNum);
    void BugRotateLeft(unsigned int nBugNum);
    void BugRotateRight(unsigned int nBugNum);

    Position GetBugPosition(unsigned int nBugNum);
    void SetBugPosition(unsigned int nBugNum,Position pos);

    void SetBugLookDirection(unsigned int nBugNum,unsigned short nBugLookDirection);
    unsigned short GetBugLookDirection(unsigned int nBugNum);

    Position CorrectToLookDirection(Position pPositionOfTheBug,	unsigned short nBugLookDirection, unsigned int nTestPlace);
    bool CanGo(Position pos, unsigned short nBugLookDirection);

public:
    unsigned int WhatBugIsOntheExit(void);
    void RemoveBug(unsigned int nBugNum);
    bool IsAnyBugAtTheExit(void);
    /// Constructor to load file
    /// with battle
    /// @param strFileName
    /// string with filename
    Field(std::string strFileName);

    /// Default constructor. For load the battle
    /// use LoadField()
    /// @see LoadField()
    Field();

    std::string GetBugName(unsigned int nBugNum);
    unsigned int GetNumberOfBugs(void);

    /// for Loading Field from File
    /// @return true if fail. false if succeeded
    /// @param strFileName
    /// string with filename
    bool LoadField(std::string strFileName);
    ///
    unsigned short WhatIsLeft(unsigned int nBugNum);
    ///
    unsigned short WhatIsRight(unsigned int nBugNum);
    ///
    unsigned short WhatIsForward(unsigned int nBugNum);
    ///
    unsigned short WhatIsHere(unsigned int nBugNum);
    /// Method for asking bug's action
    void AskToBug(unsigned int nBugAction,unsigned int nBugNum);
    /// destructor
    ~Field();
};
namespace TestPlace
{
    enum  TestPlaceAroundBug
    {
        forward,
        lefthand,
        righthand
    };
};

#endif
