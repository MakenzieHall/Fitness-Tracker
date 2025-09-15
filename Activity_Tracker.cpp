#include "Activity_Tracker.h"

// destructor
Activity_Tracker::~Activity_Tracker(){}

// function to remove specific activity from the vector
void Activity_Tracker::removeAct(const Activity& act){

        bool found = false;

        for(size_t i = 0; i < activities.size(); i++)
        {
            if(activities[i]==act)
            {
                activities.erase(activities.begin() + i);
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Activity not found.\n" << endl;
        }
}

// function to find total calories burned of all activities in the vector
double Activity_Tracker::totalCalAll(){
    double total = 0;
    for (const Activity& a : activities)
    {
        total += a.calBurned();
    }
    return total;
}

// function to find total time active in all activities (hr)
double Activity_Tracker::totalTime(){
    double total = 0;
    for (const Activity& a : activities)
    {
        total += a.getDurH();
    }
    return total;
}

// function to return specific activity in vector
Activity Activity_Tracker::getActivity(const Activity& target) const {
    for (const Activity& a : activities) {
        if (a == target) {
            return a; // return copy
        }
    }
    throw std::runtime_error("Activity not found.");
}

// function to return if activity was found in vector
bool Activity_Tracker::found(const Activity& act){
    bool found = false;

        for(size_t i = 0; i < activities.size(); i++)
        {
            if(activities[i]==act)
            {
                found = true;
                break;
            }
        }

        return found;
}




