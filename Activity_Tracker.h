#ifndef ACTIVITY_TRACKER_H
#define ACTIVITY_TRACKER_H
#include <vector>


class Activity_Tracker
{
    public:
        // empty constructor to make blank tracker
        Activity_Tracker();

        // constructor to make tracker out of vector
        Activity_Tracker(vector<Activity> acts){activities = acts;}

        // destructor
        virtual ~Activity_Tracker();

        // accessor to the activities vector
        const vector<Activity>& getActivities()const { return activities;}

        vector<Activity>& getActivitiesNonConst() {return activities;}

        // function to add activity to the end of the vector
        void addAct(Activity act){
            activities.push_back(act);
        }

        // function to remove specific activity from the vector
        void removeAct(const Activity& act);

        // function to find total calories burned of all activities in the vector
        double totalCalAll();

        // function to find total time active in all activities (hr)
        double totalTime();

        // function to return specific activity in vector
        Activity getActivity(const Activity& target) const;

        // function to return if activity was found in vector
        bool found(const Activity& act);


    private:
        vector<Activity> activities;

};

#endif // ACTIVITY TACKER_H
