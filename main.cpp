#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;
#include "Activity.h"
#include "Activity.cpp"
#include "Activity_Tracker.h"
#include "Activity_Tracker.cpp"

//***********************************************************************************
// Name:       Makenzie Hall
// Program:    Fitness Tracker
// Last Updated:  09/15/2025
// This program is a fitness tracker system where you can pick an activity, or make
// your own, and track the dates done, duration of activity, and calories burned.
//***********************************************************************************

//***********************************************************************************
// DATE CHECKING
//***********************************************************************************
// Checks if the year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Checks if the date is valid by using a array for how many days in the month
// also takes into account leap years
bool isValidDate(int month, int day, int year) {
    if (year < 1900 || month < 1 || month > 12 || day < 1) return false;

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if (month == 2 && isLeapYear(year)) {
        return day <= 29;
    }

    return day <= daysInMonth[month - 1];
}

// collects and returns a date and checks if the date is valid, if not prompt another input
string validDate() {
    bool valid = false;
    int month, day, year;
    char slash1, slash2;
    string input;

    // runs while valid is still false
    while (!valid) {
        cout << "Enter a date (mm/dd/yyyy): ";
        getline(cin, input);
        stringstream ss(input);
        ss >> month >> slash1 >> day >> slash2 >> year;

        if (ss.fail() || slash1 != '/' || slash2 != '/' || !ss.eof()) {
            cout << "Error: Incorrect date format. Please use mm/dd/yyyy." << endl;
            continue;
        }

        if (!isValidDate(month, day, year)) {
            cout << "Error: Invalid date. Please enter a valid calendar date." << endl;
            continue;
        }

        valid = true;
    }

    // Format date with zero-padding
    stringstream formattedDate;
    formattedDate << setfill('0') << setw(2) << month << '/'
                  << setw(2) << day << '/'
                  << year;

    return formattedDate.str();
}

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
    cout << "Usage: " << argv[0] << " tracker input, tracker output" << endl;
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
ofstream trackOut(argv[2]);
if (!trackOut.is_open()) {
    cout << "Error: Could not open the tracker output file!" << endl;
    exit(1);
}

// Load activities from input file and create activity tracker from that
vector<Activity> acts = loadActivitiesFromFile(trackIn);

Activity_Tracker actTracker = Activity_Tracker(acts);


//**************************************************************************
// While loop to allow commands until the user inputs 8
//**************************************************************************
   string input;

   while (input != "8")
   {
        printOptions();
        input.clear();
        cin >> input;
//**************************************************************************
// If input is 1 set up for add activity
//**************************************************************************
        if(input == "1")
        {
            string date, name, minStr, calStr;
            int mins;
            double cal;

            // get input
            cout << "\n Enter Activity Data:" << endl;
            cout << "Name: " << endl;
            cin.ignore(256, '\n');
            getline(cin, name);
            date = validDate();
            cout << "Duration (Mins): " << endl;
            getline(cin, minStr);
            mins = stoi(minStr);
            cout << "Calories Burned Per Hour: " << endl;
            getline(cin, calStr);
            cal = stod(calStr);

            // create activity and add to tracker
            Activity newAct = Activity(name, date, mins, cal);
            actTracker.addAct(newAct);

            cout << "\n Adding Activity...... \n" << endl;
        }

//**************************************************************************
// If input is 2 set up for remove activity
//**************************************************************************
        if (input == "2")
        {
            string date, name, minStr, calStr;
            int mins;
            double cal;

            // get input
            cout << "\n Enter Activity Data for Which to Remove:" << endl;
            cout << "Name: " << endl;
            cin.ignore(256, '\n');
            getline(cin, name);
            date = validDate();
            cout << "Duration (Mins): " << endl;
            getline(cin, minStr);
            mins = stoi(minStr);
            cout << "Calories Burned Per Hour: " << endl;
            getline(cin, calStr);
            cal = stod(calStr);

            // create activity and remove from tracker
            Activity oldAct = Activity(name, date, mins, cal);
            if(actTracker.found(oldAct))
            {
                cout << "\n Removing Activity...... \n" << endl;
            }
            actTracker.removeAct(oldAct);

        }

//**************************************************************************
// If input is 3 set up for update activity (removes old, adds new)
//**************************************************************************
        if (input == "3")
        {

            string date, name, minStr, calStr;
            int mins;
            double cal;

            bool found = false;

            // get input to find activity to update
                cout << " \n Enter Activity Data for Which to Update:" << endl;
                cout << "Name: " << endl;
                cin.ignore(256, '\n');
                getline(cin, name);
                date = validDate();
                cout << "Duration (Mins): " << endl;
                getline(cin, minStr);
                mins = stoi(minStr);
                cout << "Calories Burned Per Hour: " << endl;
                getline(cin, calStr);
                cal = stod(calStr);




            // create activity and remove from tracker, if not found continue
            Activity oldAct = Activity(name, date, mins, cal);
            found = actTracker.found(oldAct);
                if (!found){
                    cout<< "\n Activity not found. Update aborted. \n" << endl;
                    continue;
                }
            actTracker.removeAct(oldAct);

             // get input to update activity
            cout << "Enter Updated Activity Data:" << endl;
            cout << "Name: " << endl;
            getline(cin, name);
            date = validDate();
            cout << "Duration (Mins): " << endl;
            getline(cin, minStr);
            mins = stoi(minStr);
            cout << "Calories Burned Per Hour: " << endl;
            getline(cin, calStr);
            cal = stod(calStr);

            // create activity and add to tracker
            Activity newAct = Activity(name, date, mins, cal);
            actTracker.addAct(newAct);

            cout << "\n Updating Activity...... \n" << endl;

        }

//**************************************************************************
// If input is 4 set up for view all activities
//**************************************************************************
        if( input== "4" )
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
        if (input == "5")
        {
            cout << "\n Total Calories Burned: " << actTracker.totalCalAll()<< '\n';
        }

//**************************************************************************
// If input is 6 set up for view total time active
//**************************************************************************
        if (input == "6")
        {
            cout<< "\n Total time Active: " << actTracker.totalTime()<< " hours \n";
        }
//**************************************************************************
// If input is 7 set up for sort fitness tracker
//**************************************************************************
        if (input == "7")
        {
            sortVec(actTracker.getActivitiesNonConst());
            cout << "\n Sorting Fitness Tracker...... \n";
        }
   }

sortVec(actTracker.getActivitiesNonConst());
cout << "\n Sorting Fitness Tracker...... \n";
trackerToFile(trackOut, actTracker);

    return 0;

};
