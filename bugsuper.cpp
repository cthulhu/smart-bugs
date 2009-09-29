#define __TRACE
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>
#include "utils.h"
#if defined (__TRACE)
#include "trace.h"
#endif
#include "field.h"
#include "bugsuper.h"

#if defined (__TRACE)
std::ofstream LogBugSuper;
#endif

#if defined(__TRACE)
/// Method for getting bug's position
/// on the map from respound
Position bug::GetBugPos()
{
    return posPositionOnTheField;
}
#endif
/// Method for getting bug's time
/// for living left which is left
unsigned short bug::GetTimeOfLiving()
{
    return TimeOfLiving;
}
bug::bug():
        Action(BugActions::eStaying),TimeOfLiving(100),
        posPositionOnTheField(),
        strBugName(""),
        cBugNum(0)
{
#if defined (__TRACE)
    if(!LogBugSuper.is_open())
        LogBugSuper.open("__BugSuper.log");
#endif
}
void bug::Initialize(std::string strNewBugName,
                     unsigned int cNewBugNum, unsigned short nNewAction, unsigned short NewTimeOfLiving)
{
#if defined(__TRACE)
    assert(!strNewBugName.empty());
    assert(nNewAction < BugActions::eImpossibleAction);
    assert(NewTimeOfLiving != 0);
#endif

    strBugName = strNewBugName;
    cBugNum	= cNewBugNum;
    Action = nNewAction;
    TimeOfLiving = NewTimeOfLiving;
#if defined (__TRACE)

    __TRACE_INFOR::trace __TRACE_;
    LogBugSuper << "Bug number " << cBugNum << " is "
    << strBugName << ". " << "Now It's " << __TRACE_.GetActionByNumber(nNewAction) << ". "
    << "It's have only " << TimeOfLiving << " Seconds" << std::endl;

#endif
}
void bug::DecreaseTimeOfLiving(void)
{
#if defined (__TRACE)
    assert(TimeOfLiving >= 0);
#endif

    if(TimeOfLiving)
        --TimeOfLiving;
}
/// Method for asking to bug
/// what he wants to do.
unsigned short bug::WhatDoYouWhantToDo(void)
{
    if(Action == BugActions::eEating)
        AddTimeOfLiving(50);
    else
        DecreaseTimeOfLiving();

    return Action;
}
void bug::AddTimeOfLiving(unsigned short nTimeOfLiving)
{
    TimeOfLiving += nTimeOfLiving;
}
unsigned int bug::GetBugNum(void)
{
    return cBugNum;
}
bug::~bug()
{
#if defined (__TRACE)
    LogBugSuper.close();
#endif
}

