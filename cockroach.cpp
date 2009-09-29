#include <vector>
#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include "utils.h"
#include "field.h"
#include "bugsuper.h"
#define __TRACE
#include "cockroach.h"
#if defined(__TRACE)
#include "trace.h"
#endif

BugCockroach::BugCockroach()
{}
BugCockroach::~BugCockroach(void)
{
#if defined(__TRACE)
    if(!TimeOfLiving)
    {
        LogBug << "I'm going to die. Good bye!!! " << std::endl;
    }
    else
    {
        LogBug << "Hey boys I've found the exit !!! " << std::endl;
    }
    LogBug.close();
#endif


}
void BugCockroach::GetField(Field &fild)
{
    if(fild.WhatIsHere(cBugNum) == CellTypes::eFood)
    {
        Action = BugActions::eEating;
        return;
    }
    if(fild.WhatIsHere(cBugNum) == CellTypes::eExit)
    {
        Action = BugActions::eStaying;
        return;
    }
#if defined(__TRACE)

    if(!LogBug.is_open())
    {
        std::string __str__trace_tmp_("__" + strBugName + "Bug.log");
        LogBug.open(__str__trace_tmp_.c_str());
        LogBug << "The Cockroach is ready to the battle" <<std::endl;
    }

    LogBug << std::endl << "Let's see what is all around " << std::endl;
    __TRACE_INFOR::trace _TRACE_INFORMATION_;

    LogBug << "Forward direction " <<
    _TRACE_INFORMATION_.GetCellTypesByNumber(fild.WhatIsForward(cBugNum)) << std::endl
    << "Left hand " << _TRACE_INFORMATION_.GetCellTypesByNumber(fild.WhatIsLeft(cBugNum))
    << std::endl << "Right hand " << _TRACE_INFORMATION_.GetCellTypesByNumber(fild.WhatIsRight(cBugNum))
    << std::endl << "Here on the cell " << _TRACE_INFORMATION_.GetCellTypesByNumber(fild.WhatIsHere(cBugNum))
    << std::endl;

#endif

    if(fild.WhatIsLeft(cBugNum) == CellTypes::eExit)
    {
        Action = BugActions::eRotatingLeft;
        return;
    }
    if(fild.WhatIsRight(cBugNum) == CellTypes::eExit)
    {
        Action = BugActions::eRotatingRight;
        return;
    }
    if(fild.WhatIsForward(cBugNum) == CellTypes::eClear || fild.WhatIsForward(cBugNum) == CellTypes::eFood|| fild.WhatIsForward(cBugNum) == CellTypes::eExit)
    {
        Action = BugActions::eMoving;
        return;
    }
    if(fild.WhatIsLeft(cBugNum) == CellTypes::eClear || fild.WhatIsLeft(cBugNum) == CellTypes::eFood)
    {
        Action = BugActions::eRotatingLeft;
        return;
    }
    if(fild.WhatIsRight(cBugNum) == CellTypes::eClear || fild.WhatIsRight(cBugNum) == CellTypes::eFood)
    {
        Action = BugActions::eRotatingRight;
        return;
    }
    Action = BugActions::eRotatingLeft;
}
