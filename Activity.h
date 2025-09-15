//****************************************************************************
// Activity class includes the name of activity done, date done, duration in
// minutes, and amount of calories burned per hour. Has subclasses of some
// different activities but also a constructor to create your own activity.
//****************************************************************************


#ifndef ACTIVITY_H
#define ACTIVITY_H


class Activity
{
    public:
        // Constructors and destructor
        Activity(string nm, string dt, int durM, double calBurn);
        Activity();
        virtual ~Activity();

        // Display Details
        virtual void displayDetails();

        // Basic virtual accessor functions
        virtual string getName() const {return name;}
        virtual string getDate() const {return date;}
        virtual int getDurMin() const {return durMin;}
        virtual double getDurH() const {return durH;}
        virtual double getCalPerH() const {return calPerH;}

        // Basic virtual mutator functions
        virtual void setName(const string& newName){name = newName;}
        virtual void setDate(const string& newDate) {date = newDate;}
        virtual void setDurMin (const int& newDur){
            durMin = newDur;
            durH = ((double)durMin/60);
        }
        virtual void setCalPH (const double& newCal) {calPerH = newCal;}

        // function to get total calories burned for the activity
        virtual double calBurned() const {return calPerH * durH;}


        // Operators for comparison (same if same name, date, duration, calPerH)
        virtual bool operator==(const Activity& other) const {
            return name == other.name && date == other.date && durMin == other.durMin && calPerH == other.calPerH;
        }
        virtual bool operator!=(const Activity& other) const {
            return !(*this == other);
        }

        // Assignment operator
        virtual Activity& operator=(const Activity& other){
            if (this != &other)
            {
                name = other.name;
                date = other.date;
                durMin = other.durMin;
                durH = other.durH;
                calPerH = other.calPerH;
            }
            return *this;
        }


        // Helper: Parse date into day, month, year
        void parseDate(const string& dateStr, int& month, int& day, int& year) const {
            char sep;
            istringstream iss(dateStr);
            iss >> month >> sep >> day >> sep >> year;
        }

        // Compare dates accurately
        virtual bool operator<(const Activity& other) const {
            int m1, d1, y1, m2, d2, y2;
            parseDate(date, m1, d1, y1);
            parseDate(other.date, m2, d2, y2);

            // check year then month then day
            if (y1 != y2) return y1 < y2;
            if (m1 != m2) return m1 < m2;
            return d1 < d2;
        }

        virtual bool operator>(const Activity& other) const {
            return other < *this;
        }

        virtual bool operator<=(const Activity& other) const {
            return !(*this > other);
        }

        virtual bool operator>=(const Activity& other) const {
            return !(*this < other);
        }

        // takes the formatted line and creates activity out of it
        void fromFormattedLine(const string& line);


        // Stream output
        friend std::ostream& operator << (std::ostream& os, const Activity& act){
            os << "Activity: " << act.getName() << "\n"
               << "Date: " << act.getDate() << "\n"
               << "Duration (min): " << act.getDurMin() << "\n"
               << "Duration (hr): " << act.getDurH() << "\n"
               << "Calories Burned per Hour: " << act.getCalPerH() << "\n";
            return os;
        }

        // toFile that formats activity in way to print to a file
        void toFile(ostream & out) const {
        out << left  << setw(12) << date
            << left  << setw(15) << name
            << right << setw(10) << durH
            << right << setw(15) << fixed << setprecision(2) << calPerH
            << right << setw(18) << fixed << setprecision(2) << calBurned()
            << '\n';
    }

    protected:
        string name;                             // name of activity done
        string date;                             // mm/dd/yyyy
        int durMin;                              // duration of activity in minutes
        double durH;                             // duration of activity in hours
        double calPerH;                          // calories burned per hour of activity


    private:
};

#endif // ACTIVITY_H
