#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <tuple>
using namespace std;
#include "Activity.h"
#include "Activity.cpp"
#include "Cycling.h"
#include "Running.h"
#include "Walking.h"
#include "Activity_Tracker.h"
#include "Activity_Tracker.cpp"
#include "Input_Helper.h"
#include "Input_Helper.cpp"

//***********************************************************************************
// Name:       Makenzie Hall
// Program:    Fitness Tracker
// Last Updated:  09/16/2025
// This program is a fitness tracker system where you can pick an activity, or make
// your own, and track the dates done, duration of activity, and calories burned.
// Data for calories burned per hour on average for activity:
// https://www.dhs.wisconsin.gov/publications/p4/p40109.pdf
//***********************************************************************************

//***********************************************************************************
// VECTOR SORT
//***********************************************************************************
void sortVec(vector<Activity>& vec){
    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                // Swap elements
                Activity temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
        }
    }
}

//***********************************************************************************
// FILE MANIPULATION
//***********************************************************************************
// Prints the tracker to output file
void trackerToFile(ofstream& out, const Activity_Tracker& tracker) {
    out.flush();

    // Print column headers
    out << left  << setw(12) << "Date"
        << left  << setw(15) << "Name"
        << right << setw(10) << "Hours"
        << right << setw(15) << "Cal/Hr"
        << right << setw(18) << "Total Calories"
        << '\n';

    out << string(70, '-') << '\n'; // divider line

    double totalCalories = 0.0;

    for (const Activity& act : tracker.getActivities()) {
        act.toFile(out);
        totalCalories += act.calBurned();
    }

    out << string(70, '-') << '\n'; // divider line

    // Print total calories burned
    out << right << setw(52) << "Total Calories Burned:"
        << setw(18) << fixed << setprecision(2) << totalCalories
        << '\n';

    cout << "Saving fitness tracker to file..." << endl;
}

// Creates a vector based on activities from input file
vector<Activity> loadActivitiesFromFile(ifstream& inFile) {
    vector<Activity> activities;

    string line;

    // Skip header lines
    getline(inFile, line);
    getline(inFile, line);

    while (getline(inFile, line)) {
        // Skip divider and total line
        if (line.find("Total Calories Burned:") != string::npos || line.find('-') != string::npos) {
            continue;
        }

        Activity act;
        act.fromFormattedLine(line);
        activities.push_back(act);
    }

    cout << "Adding activities to fitness tracker......" << endl;
    return activities;
}

//***********************************************************************************
// OPTIONS FUNCTION
//***********************************************************************************
void printOptions(){
    cout << "\n========= FITNESS TRACKER MENU =========\n";
    cout << "1. Add Activity\n";
    cout << "2. Remove Activity\n";
    cout << "3. Update Activity\n";
    cout << "4. View All Activities\n";
    cout << "5. View Total Calories Burned\n";
    cout << "6. View Total Time Active\n";
    cout << "7. Sort Fitness Tracker\n";
    cout << "8. Quit\n";
    cout << "Enter your choice (1-8): ";
    cout<< "\n========================================="
     <<"\nReady for Input:"<<endl;
}

//***********************************************************************************
// MAIN
//***********************************************************************************
int main (int argc, char *argv[]){


//***********************************************************************************
// Check command line arguments to make sure there are enough of them
// Produce a usage message if there is not enough
//***********************************************************************************
if (argc != 3)
{
    cout << "Usage: " << argv[0] << " <tracker_input> <tracker_output>" << endl;
    exit(0);
}

//***********************************************************************************
// Open the tracker input and tracker output files
//***********************************************************************************
ifstream trackIn(argv[1]);
if (!trackIn.is_open()) {
    cout << "Error: Could not open the tracker input file!" << endl;
    exit(1);
}

// Load activities from input file and create activity tracker from that
vector<Activity> acts = loadActivitiesFromFile(trackIn);
Activity_Tracker actTracker = Activity_Tracker(acts);

trackIn.close();

//**************************************************************************
// While loop to allow commands until the user inputs 8
//**************************************************************************
   string input;

   while (input != "8")
   {
        printOptions();
        cin >> input;
        cin.ignore();
//**************************************************************************
// If input is 1 set up for add activity
//**************************************************************************
        if(input == "1")
        {
            // Choose an activity or make your own
            cout << "\n============= ACTIVITY MENU =============\n";
            cout << "A. Cycling\n";
            cout << "B. Running\n";
            cout << "C. Walking\n";
            cout << "D. Other\n";
            cout << "Enter your choice (A-D): ";
            cout << "\n=========================================\n"
             <<"\nReady for Input:"<<endl;

             cin >> input;
             cin.ignore();

             if (input == "A" || input == "a")
             {
                // get input
                auto [date, mins] = getActivityData();

                // create activity and add to tracker
                Cycling newCycle = Cycling(date, mins);
                actTracker.addAct(newCycle);

                cout << "\nAdding Activity...... \n" << endl;
             }
             else if (input == "B" || input == "b")
             {
                // get input
                auto [date, mins] = getActivityData();

                // create activity and add to tracker
                Running newRun = Running(date, mins);
                actTracker.addAct(newRun);

                cout << "\nAdding Activity...... \n" << endl;
             }
             else if (input == "C" || input == "c")
             {

                // get input
                auto [date, mins] = getActivityData();

                // create activity and add to tracker
                Walking newWalk = Walking(date, mins);
                actTracker.addAct(newWalk);

                cout << "\nAdding Activity...... \n" << endl;
             }
             else if (input == "D" || input == "d")
             {
                auto [name, date, mins, cal] = getFullActivityData("\nEnter Activity Data:");
                Activity newAct = Activity(name, date, mins, cal);
                actTracker.addAct(newAct);
                cout << "\nAdding Activity...... \n" << endl;
             }
             else
             {
                 cout << "Invalid selection.\n";
             }

        }

//**************************************************************************
// If input is 2 set up for remove activity
//**************************************************************************
        else if (input == "2")
        {
            auto [name, date, mins, cal] = getFullActivityData("\nEnter Activity Data for Which to Remove:");
            Activity oldAct = Activity(name, date, mins, cal);
            if(actTracker.found(oldAct)) {
                cout << "\nRemoving Activity...... \n" << endl;
                actTracker.removeAct(oldAct);
            } else {
                cout << "Activity not found. Nothing removed.\n";
}

        }

//**************************************************************************
// If input is 3 set up for update activity (removes old, adds new)
//**************************************************************************
        else if (input == "3")
        {

            auto [oldName, oldDate, oldMins, oldCal] = getFullActivityData("\nEnter Activity Data for Which to Update:");
            Activity oldAct = Activity(oldName, oldDate, oldMins, oldCal);

            if (!actTracker.found(oldAct)) {
                cout << "\nActivity not found. Update aborted.\n" << endl;
                continue;
            }

            actTracker.removeAct(oldAct);

            auto [newName, newDate, newMins, newCal] = getFullActivityData("Enter Updated Activity Data:");
            Activity newAct = Activity(newName, newDate, newMins, newCal);
            actTracker.addAct(newAct);

            cout << "\nUpdating Activity...... \n" << endl;

        }

//**************************************************************************
// If input is 4 set up for view all activities
//**************************************************************************
        else if( input== "4" )
        {
            // Print column headers
            cout << '\n';
            cout << left  << setw(12) << "Date"
                << left  << setw(15) << "Name"
                << right << setw(10) << "Hours"
                << right << setw(15) << "Cal/Hr"
                << right << setw(18) << "Total Calories"
                << '\n';

            cout << string(70, '-') << '\n'; // divider line

            double totalCalories = 0.0;

            for (const Activity& act : actTracker.getActivities()) {
                act.toFile(cout);
                totalCalories += act.calBurned();
            }

            cout << string(70, '-') << '\n'; // divider line

            // Print total calories burned
            cout << right << setw(52) << "Total Calories Burned:"
                << setw(18) << fixed << setprecision(2) << totalCalories
                << '\n';
        }
//**************************************************************************
// If input is 5 set up for view total calories burned
//**************************************************************************
        else if (input == "5")
        {
            cout << "\nTotal Calories Burned: " << actTracker.totalCalAll()<< '\n';
        }

//**************************************************************************
// If input is 6 set up for view total time active
//**************************************************************************
        else if (input == "6")
        {
            cout<< "\nTotal time Active: " << actTracker.totalTime()<< " hours \n";
        }
//**************************************************************************
// If input is 7 set up for sort fitness tracker
//**************************************************************************
        else if (input == "7")
        {
            sortVec(actTracker.getActivitiesNonConst());
            cout << "\nSorting Fitness Tracker...... \n";
        }
   }

   ofstream trackOut(argv[2]);
    if (!trackOut.is_open()) {
        cout << "Error: Could not open the tracker output file!" << endl;
        exit(1);
    }
    sortVec(actTracker.getActivitiesNonConst());
    cout << "\nSorting Fitness Tracker...... \n";
    trackerToFile(trackOut, actTracker);

    cout << "Fitness tracker saved to file. Goodbye!\n";

    return 0;
}
