/* Citation and Sources...
Final Project Milestone q=1
Module: Date
Filename: Date.cpp
Version 1.0
Author	Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/


#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include "POS.h"
#include "Error.h"
#include <time.h>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

namespace sdds {
    void Date::validate() {
        errorM.clear();
        if (year < MIN_YEAR || year > MAX_YEAR) {
            errorM.error("Invalid Year");

        }
        else if (month < 1 || month > 12) {
            errorM.error("Invalid Month");
        }
        else if (day < 1 || day > daysOfMonth(year, month)) {
            errorM.error("Invalid Day");
        }
        else if (!isDateOnly && (hour < 0 || hour > 23)) {
            errorM.error("Invalid Hour");
        }
        else if (!isDateOnly && (minute < 0 || minute > 59)) {
            errorM.error("Invlid Minute");
        }
    }

    void Date::dateOnly(bool flag) {
        isDateOnly = flag;
        if (isDateOnly) {
            hour = 0;
            minute = 0;
        }
    }

    Date::Date() {
        int sysYear, sysMonth, sysDay, sysHour, sysMinute;
        getSystemDate(sysYear, sysMonth, sysDay, sysHour, sysMinute, true);
        year = sysYear;
        month = sysMonth;
        day = sysDay;
        hour = sysHour;
        minute = sysMinute;
        isDateOnly = false;
        validate();
    }

    Date::Date(int y, int m, int d) : year(y), month(m), day(d), hour(0), minute(0), isDateOnly(true) {
        validate();
    }

    Date::Date(int y, int m, int d, int h) : year(y), month(m), day(d), hour(h), minute(0), isDateOnly(false) {
        validate();
    }


    Date::Date(int y, int m, int d, int h, int min) : year(y), month(m), day(d), hour(h), minute(min), isDateOnly(false) {
        validate();
    }


    bool Date::operator==(const Date& other) const {
        return uniqueDateValue(year, month, day, hour, minute) == uniqueDateValue(other.year, other.month, other.day, other.hour, other.minute);
    }

    bool Date::operator!=(const Date& other) const {
        return !(*this == other);
    }

    bool Date::operator<(const Date& other) const {
        return uniqueDateValue(year, month, day, hour, minute) < uniqueDateValue(other.year, other.month, other.day, other.hour, other.minute);
    }

    bool Date::operator>(const Date& other) const {
        return uniqueDateValue(year, month, day, hour, minute) > uniqueDateValue(other.year, other.month, other.day, other.hour, other.minute);
    }

    bool Date::operator<=(const Date& other) const {
        return !(*this > other);
    }

    bool Date::operator>=(const Date& other) const {
        return !(*this < other);
    }

    Date::operator bool() const {
        return !errorM;
    }


    istream& Date::readFrom(istream& istr) {
        bool flag = true; 
        if (istr.peek() == char_traits<char>::eof() && flag) {
            errorM.error("Empty input stream");
            istr.setstate(ios::failbit);
            flag = false;
        }

        char delimiter1 = '\0', delimiter2 = '\0', delimiter3 = '\0';
        istr >> setw(4) >> year >> delimiter1;

        if (istr.fail() && flag) {
            if (delimiter1 != '/') {
                errorM.error("Cannot read year entry");
                istr.setstate(ios::failbit);
                year = 0;
                month = 0;
                day = 0;
                hour = 0;
                minute = 0;
               flag = false;
            }
            else {
                istr.clear();
                istr.seekg(-1, ios::cur);
            }
        }

        char c = '\0';

        if (istr.get(c) && isalpha(c) && flag) {
            errorM.error("Cannot read month entry");
            istr.setstate(ios::failbit);
            month = 0;
            day = 0;
            hour = 0;
            minute = 0;
            flag = false;
        }
        else {
            istr.unget();
        }

        istr >> setw(2) >> month >> delimiter2;

        if (istr.get(c) && isalpha(c) && flag) {
            errorM.error("Cannot read day entry");
            istr.setstate(ios::failbit);
            day = 0;
            hour = 0;
            minute = 0;
            flag = false;
        }
        else {
            istr.unget();
        }

        istr >> setw(2) >> day;

        if (istr.get(c) && isalpha(c) && flag) {
            errorM.error("Cannot read hour entry");
            istr.setstate(ios::failbit);

            hour = 0;
            minute = 0;
             flag = false;
        }
        else {
            istr.unget();
        }

        if (istr.peek() == ',' && flag) {
            istr.ignore();
            istr >> setw(2) >> hour >> delimiter3 >> setw(2) >> minute;
            if (istr.fail() || delimiter3 != ':') {
                errorM.error("Cannot read minute entry");
                istr.setstate(ios::failbit);

                minute = 0;
                flag = false;
            }
            isDateOnly = false;
        }
        else {
            hour = 0;
            minute = 0;
            isDateOnly = true;
        }

        validate();
        return istr;
    }




    std::ostream& operator<<(std::ostream& ostr, const Date& date) {



        if (!date) {
            ostr << date.error() << "(" << setw(4) << setfill('0') << date.getYear() << "/"
                << setw(2) << setfill('0') << date.getMonth() << "/" << setw(2) << setfill('0') << date.getDay();
            if (!date.getDateOnly()) {
                ostr << ", " << setw(2) << setfill('0') << date.getHour() << ":" << setw(2) << setfill('0') << date.getMinute();
            }
            ostr << ")";
        }
        else {
            if (date.getDateOnly()) {
                ostr << date.getYear() << "/" << setw(2) << setfill('0') << std::right << std::setfill('0') << std::setw(2) << date.getMonth() << "/" << std::right << std::setfill('0') << std::setw(2) << date.getDay() << setfill(' ');
            }
            else {
                ostr << date.getYear() << "/" << setw(2) << setfill('0') << std::right << std::setfill('0') << std::setw(2) << date.getMonth() << "/" << std::right << std::setfill('0') << std::setw(2) << date.getDay() << ", "
                    << setw(2) << setfill('0') << date.getHour() << ":" << setw(2) << setfill('0') << date.getMinute() << setfill(' ');
                
            }
           
        }

        return ostr;
    }

    std::istream& operator>>(std::istream& istr, Date& date) {
        return date.readFrom(istr);
    }

    int Date::getYear() const {
        return year;
    }

    int Date::getMonth() const {
        return month;
    }

    int Date::getDay() const {
        return day;
    }

    int Date::getHour() const {
        return hour;
    }

    int Date::getMinute() const {
        return minute;
    }

    bool Date::getDateOnly() const {
        return isDateOnly;
    }

    int Date::daysOfMonth(int year, int mon) {
        int days = 31;
        if (mon == 4 || mon == 6 || mon == 9 || mon == 11) {
            days = 30;
        }
        else if (mon == 2) {
            if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
                days = 29;
            }
            else {
                days = 28;
            }
        }
        return days;
    }

    // Sets the parameters to the system date and time.

    void Date::getSystemDate(int& year, int& month, int& day, int& hour, int& minute, bool local) {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        month = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if (!local) {
            hour = 0;
            minute = 0;
        }
        else {
            hour = lt.tm_hour;
            minute = lt.tm_min;
        }
    }


    // Returns a unique integer value for the given date and time.
    unsigned long long Date::uniqueDateValue(int year, int mon, int day, int hour, int min) const {
        return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
    }

    const char* Date::error() const {
        return errorM;
    }



}