#ifndef INPUT_HELPER_H_INCLUDED
#define INPUT_HELPER_H_INCLUDED

//***********************************************************************************
// DATE CHECKING
//***********************************************************************************
// Checks if the year is a leap year
bool isLeapYear(int year);

// Checks if the date is valid by using a array for how many days in the month
// also takes into account leap years
bool isValidDate(int month, int day, int year);

// collects and returns a date and checks if the date is valid, if not prompt another input
string validDate();

//***********************************************************************************
// ACTIVITY DATA INPUT
//***********************************************************************************
pair<string, int> getActivityData();

tuple<string, string, int, double> getFullActivityData(const string& prompt = "");

#endif // INPUT_HELPER_H_INCLUDED
