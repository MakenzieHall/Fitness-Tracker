#ifndef RUNNING_H_INCLUDED
#define RUNNING_H_INCLUDED
#include <string>
using namespace std;

class Running : public Activity{
public:

// constructor with set name and calories burned per hour
    Running(string dt, int dur)
        : Activity("Running", dt, dur, 800.00){}



};


#endif // RUNNING_H_INCLUDED
