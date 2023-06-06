/* Citation and Sources...
Final Project Milestone q=1
Module: Error
Filename: Error.cpp
Author	Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include "Error.h"
#include <cstring>

using namespace std;
namespace sdds {
    void Error::set(const char* str) {
        if (str != nullptr && str[0] != '\0') {
            errorMessage = new char[strlen(str) + 1];
            strcpy(errorMessage, str);
        }
        else {
            errorMessage = nullptr;
        }
    }

    void Error::clear() {
        delete[] errorMessage;
        errorMessage = nullptr;
    }

    Error::Error(const char* err) {
        set(err);
    }

    Error::Error(const Error& other) {
        set(other.errorMessage);
    }

    Error& Error::operator=(const Error& other) {
        if (this != &other) {
            clear();
            set(other.errorMessage);
        }
        return *this;
    }

    Error& Error::operator=(const char* str) {
        clear();
        set(str);
        return *this;
    }

    Error::~Error() {
        clear();
    }

    bool Error::operator!() const {
        return errorMessage == nullptr;
    }

    Error::operator bool() const {
        return errorMessage == nullptr;
    }

    Error::operator const char* () const {
        return errorMessage;
    }

    std::ostream& Error::writeTo(std::ostream& ostr) const {
        if (errorMessage != nullptr) {
            ostr << errorMessage;
        }
        return ostr;
    }

    void Error::error(const char* errorMsg)
    {
        clear();
        set(errorMsg);
    }



    std::ostream& operator<<(std::ostream& ostr, const Error& err) {
        return err.writeTo(ostr);
    }

}
