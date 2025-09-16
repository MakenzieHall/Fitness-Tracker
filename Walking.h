#ifndef WALKING_H_INCLUDED
#define WALKING_H_INCLUDED
#include <string>
using namespace std;

class Walking : public Activity{
public:

// constructor with set name and calories burned per hour
    Walking(string dt, int dur)
        : Activity("Walking", dt, dur, 275.00){}



};


#endif // WALKING_H_INCLUDED
