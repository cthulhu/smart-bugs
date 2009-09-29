#ifndef __COCKROACH_H_
#define __COCKROACH_H_

#if defined (__TRACE)
#include <fstream>
#endif
/// @class BugCockroach
/// Class for cockroach. This class is for
/// cockroach in the Labyrinth.
class BugCockroach:public bug
{
public:
#if defined (__TRACE)

    std::ofstream LogBug;
#endif

    BugCockroach();
    void Initialize();
    void GetField(Field &fild);
    ~BugCockroach();
};
#endif
