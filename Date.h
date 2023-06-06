/* Citation and Sources...
Final Project Milestone q=1
Module: Date
Filename: Date.h
Version 1.0
Author	Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include "Error.h"
#include <iostream>

namespace sdds {

    class Date {
    private:
        int year, month, day, hour, minute;
        bool isDateOnly;
        Error errorM;


    public:
        void validate();
        void dateOnly(bool flag);

        int getYear() const;
        int getMonth() const;
        int getDay() const;
        int getHour() const;
        int getMinute() const;
        bool getDateOnly() const;

        Date();
        Date(int y, int m, int d);
        Date(int y, int m, int d, int h);
        Date(int y, int m, int d, int h, int min);

        bool operator==(const Date& other) const;
        bool operator!=(const Date& other) const;
        bool operator<(const Date& other) const;
        bool operator>(const Date& other) const;
        bool operator<=(const Date& other) const;
        bool operator>=(const Date& other) const;

        operator bool() const;

        const char* error() const;


      
        std::istream& readFrom(std::istream& istr);

        int daysOfMonth(int year, int mon);
        void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool isDateOnly);
        unsigned long long uniqueDateValue(int year, int mon, int day, int hour, int min) const;
    };

    std::ostream& operator<<(std::ostream& ostr, const Date& date);
    std::istream& operator>>(std::istream& istr, Date& date);

}
#endif