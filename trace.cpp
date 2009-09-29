#include <vector>
#include <string>
#include "trace.h"
__TRACE_INFOR::trace::trace()
{
    vecStrActions.push_back("Staying on that cell");
    vecStrActions.push_back("Eating some food");
    vecStrActions.push_back("Tracing");
    vecStrActions.push_back("Moving forward");
    vecStrActions.push_back("Rotating left");
    vecStrActions.push_back("Rotating right");
    vecStrActions.push_back("Making some thing impossible");

    vecStrCellTypes.push_back("It's clear cell");
    vecStrCellTypes.push_back("It's a wall");
    vecStrCellTypes.push_back("It's a food");
    vecStrCellTypes.push_back("");
    vecStrCellTypes.push_back("It's a trace");
    vecStrCellTypes.push_back("");
    vecStrCellTypes.push_back("");
    vecStrCellTypes.push_back("");
    vecStrCellTypes.push_back("It's an exit");
    vecStrCellTypes.push_back("");
    vecStrCellTypes.push_back("");
    vecStrCellTypes.push_back("");
    vecStrCellTypes.push_back("");
    vecStrCellTypes.push_back("");
    vecStrCellTypes.push_back("");
    vecStrCellTypes.push_back("It's a bug");
    vecStrCellTypes.push_back("It's something impossible");

    vecStrLookDirections.push_back("West");
    vecStrLookDirections.push_back("East");
    vecStrLookDirections.push_back("North");
    vecStrLookDirections.push_back("South");
    vecStrLookDirections.push_back("It's something impossible");
}
std::string __TRACE_INFOR::trace::GetCellTypesByNumber(unsigned short nCellTypeNumber)
{
    return vecStrCellTypes[nCellTypeNumber];
}
std::string __TRACE_INFOR::trace::GetLookDirectionsByNumber(unsigned short nActionLookDirection)
{
    return vecStrLookDirections[nActionLookDirection];
}
std::string __TRACE_INFOR::trace::GetActionByNumber(unsigned short nActionNumber)
{
    return vecStrActions[nActionNumber];
}
__TRACE_INFOR::trace::~trace()
{
    vecStrActions.clear();
    vecStrCellTypes.clear();
    vecStrLookDirections.clear();
}
