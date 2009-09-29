#ifndef _UTILS_H_
#define _UTILS_H_

/// utility class for
/// dealing with coordinates
class Position
{
public:
    Position(short nX,short nY)
            :x(nX),y(nY)
    {}
    Position()
            :x(0x00),y(0x00)
    {}
    bool operator==(Position b);

    /// x - coordinate
    short x;
    /// y - coordinate
    short y;
};

/// The definitions of the bugs look directions
namespace BugDirections
{
    enum BugLookDirections
    {
        /// The bug is looking to the
        /// west
        eWestLook  = 0x00,
        /// The bug is looking to the
        /// east
        eEastLook  = 0x01,
        /// The bug is looking to the
        /// north
        eNorthLook = 0x02,
        /// The bug is looking to the
        /// south
        eSouthLook = 0x03,
        /// For controling
        eImpossibleLookDirection

    };
}

namespace BugActions
{
    /// The definitions of actions
    enum ActionsOfTheBug
    {
        /// The value of the bug's
        /// action when it's do nothing
        eStaying = 0x00,
        /// The value of the bug's
        /// action when it's eating
        eEating  = 0x01,
        /// The value of the bug when
        /// it's putting the trace
        eTracing = 0x02,
        /// The value of the bug when
        /// moving forward
        eMoving  = 0x03,
        /// The value of the bug when
        /// it's rotating
        eRotatingLeft = 0x04,
        /// The value of the bug when
        /// it's rotating
        eRotatingRight = 0x05,
        /// For controling
        eImpossibleAction
    };
}
/// The definition of cell types
namespace CellTypes
{
    enum CELLS
    {
        /// nothing is here, bug can move
        /// in to the cell
        eClear = 0x00,
        /// the wall is here, bug can't
        /// move in to the cell
        eWall  = 0x01,
        /// the cell with food. Bug can it that
        /// but if he doesn't want, he may not
        eFood  = 0x02,
        /// the cell with trace point. Bug can
        /// read traces (Every trace is one food)
        eTrace = 0x04,
        /// cell with exit
        eExit  = 0x08,
        /// cell with bug
        eBug   = 0x10,
        /// For controling
        eImpossibleCell
    };
}
#endif
