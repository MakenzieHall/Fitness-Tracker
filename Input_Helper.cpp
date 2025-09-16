
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
// ACTIVITY DATA INPUT
//***********************************************************************************
pair<string, int> getActivityData() {
    string date, minStr;
    int mins = 0;
    bool valid = false;

    date = validDate();

    while (!valid) {
        cout << "Duration (Mins): ";
        getline(cin, minStr);
        try {
            mins = stoi(minStr);
            if (mins <= 0) throw invalid_argument("Duration must be positive.");
            valid = true;
        } catch (...) {
            cout << "Invalid input. Please enter a valid positive number for minutes.\n";
        }
    }

    return {date, mins};
}


tuple<string, string, int, double> getFullActivityData(const string& prompt) {
    string name, date, minStr, calStr;
    int mins = 0;
    double cal = 0.0;

    if (!prompt.empty())
        cout << prompt << endl;

    cout << "Name: ";
    getline(cin, name);

    date = validDate();

    bool valid = false;
    while (!valid) {
        cout << "Duration (Mins): ";
        getline(cin, minStr);
        try {
            mins = stoi(minStr);
            if (mins <= 0) throw invalid_argument("Must be positive.");
            valid = true;
        } catch (...) {
            cout << "Invalid input. Please enter a positive number.\n";
        }
    }

    valid = false;
    while (!valid) {
        cout << "Calories Burned Per Hour: ";
        getline(cin, calStr);
        try {
            cal = stod(calStr);
            if (cal <= 0) throw invalid_argument("Must be positive.");
            valid = true;
        } catch (...) {
            cout << "Invalid input. Please enter a positive number.\n";
        }
    }

    return {name, date, mins, cal};
}
