#include <iostream>
using namespace std;
#include "Activity.h"

// No parameter constructor to establish "blank" activity
Activity::Activity(){
    name = "No Activity Named";
    date = "mm/dd/yyyy";
    durMin = 0;
    durH = ((double)durMin/60);
    calPerH = 0;

}

// Constructor to create own activity
Activity::Activity(string nm, string dt, int durM, double calBurn)
{
    name = nm;
    date = dt;
    durMin = durM;
    durH = ((double)durMin/60);
    calPerH = calBurn;
}

// Empty Destructor
Activity::~Activity() {
}

// Display details for details of activity
void Activity::displayDetails(){
    cout << "Activity: " << name << "\n"
         << "Date: " << date << "\n"
         << "Duration (min): " << durMin << "\n"
         << "Duration (hr): " << durH << "\n"
         << "Calories Burned per Hour: " << calPerH << endl;
}

// Takes the formatted line and creates activity out of it
void Activity::fromFormattedLine(const string& line) {
    // Extract substrings by fixed width
    string dateStr = line.substr(0, 12);
    string nameStr = line.substr(12, 15);
    string durHStr = line.substr(27, 10);
    string calPerHStr = line.substr(37, 15);

    // Trim spaces
    auto trim = [](string s) {
        size_t start = s.find_first_not_of(" \t");
        size_t end   = s.find_last_not_of(" \t");
        return (start == string::npos) ? "" : s.substr(start, end - start + 1);
    };

    date     = trim(dateStr);
    name     = trim(nameStr);
    durMin   = (stod(trim(durHStr)) * 60);
    durH     = stod(trim(durHStr));
    calPerH  = stod(trim(calPerHStr));
}

