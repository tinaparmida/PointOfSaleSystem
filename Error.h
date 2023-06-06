/* Citation and Sources...
Final Project Milestone q=1
Module: Error
Filename: Error.h
Version 1.0
Author	PARMIDA Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H
#include <iostream>

#include "PosIO.h"


namespace sdds {
    class Error {
    private:
        char* errorMessage;



    public:

        void set(const char* str);
        void clear();
        Error(const char* err = nullptr);
        Error(const Error& other);
        Error& operator=(const Error& other);
        Error& operator=(const char* str);
        virtual ~Error();

        bool operator!() const;
        operator bool() const;
        operator const char* () const;
        std::ostream& writeTo(std::ostream& ostr) const;
        void error(const char* errorMessage);
    };

    std::ostream& operator<<(std::ostream& ostr, const Error& err);
}
#endif
