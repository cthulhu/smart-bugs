#ifndef _BUGSUPER_H_
#define _BUGSUPER_H_

/// @class bug
/// The super class for all bugs in the project
class bug
{
protected:

    /// @var posPositionOnTheField
    /// Member for setting Bug's position
    /// on the map from respound.
    /// @see Position
    Position posPositionOnTheField;
    /// @var TimeOfLiving
    /// Member for controling
    /// time of living
    /// @see GetTimeOfLiving()
    unsigned short TimeOfLiving;
    /// @var Action
    /// Member for action which
    /// the bug whant to do
    unsigned short Action;
    /// @var strBugName
    /// The member to containg the bug name.
    std::string strBugName;
    /// @var cBugNum
    /// Number of bug for indexing
    unsigned int cBugNum;

    /// Method for setting bug's time
    /// of living. Calling after the bug's
    /// found the food
    void AddTimeOfLiving(unsigned short nTimeOfLiving);
    void DecreaseTimeOfLiving(void);

public:
    bug();
    ~bug();

    /// method for testing all around
    /// for avery bug it's individual for all bugs
    virtual void GetField(Field &fild) = 0;
    void Initialize(std::string strNewBugName,
                    unsigned int cNewBugNum, unsigned short nNewAction, unsigned short NewTimeOfLiving);
#if defined (__TRACE)
    /// Method for getting bug's coordinates
    /// on the map from the respound
    Position GetBugPos(void);
#endif
    /// Method for getting Bug's Time of living
    unsigned short GetTimeOfLiving(void);
    /// Method for asking about what does bug want to do.
    unsigned short WhatDoYouWhantToDo(void);
    unsigned int GetBugNum(void);
};
#endif
