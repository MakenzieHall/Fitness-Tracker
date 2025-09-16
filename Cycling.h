#ifndef CYCLING_H_INCLUDED
#define CYCLING_H_INCLUDED
#include <string>
using namespace std;

class Cycling : public Activity{
public:

// constructor with set name and calories burned per hour
    Cycling(string dt, int dur)
        : Activity("Cycling", dt, dur, 600.00){}



};


#endif // CYCLING_H_INCLUDED
