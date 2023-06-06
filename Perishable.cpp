/* Citation and Sources...
Final Project Milestone q=1
Module: Perishable
Filename: Perishable.cpp
Version 1.0
Author	PARMIDA Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "Perishable.h"
#include "Date.h"

using namespace std;

namespace sdds {

    char Perishable::itemType() const {
        return 'P';
    }


    std::ofstream& Perishable::save(std::ofstream& file) const {
        Item::save(file);
        file << ',' << m_expiry << endl;
        return file;
    }

    std::ifstream& Perishable::load(std::ifstream& file) {
        Item::load(file);
        file.ignore();
        m_expiry.readFrom(file);
        return file;
    }

    std::ostream& Perishable::write(std::ostream& os, int linear) const {
        Item::write(os, linear);
        if (isClear()) {
            // If the object is in POS_LIST display mode, print the date as follows:
                if (linear == POS_LIST) {
                    os << "  " << m_expiry << " |";
                  
                }

                // If the object is in POS_FORM display mode, print the date as follows:
              if (linear == POS_FORM) {
                    os << "Expiry date: " << m_expiry << endl;
                    os << "=============^" << endl;

              
                }
          
        }
    
        return os;
    }

    std::istream& Perishable::read(std::istream& is) {
        Date temp;
        Item::read(is);
        if (is.good()) {
            cout << "Expiry date (YYYY/MM/DD)"<< endl;
            cout << "> ";
            is >> temp;
            if (!is.fail() && temp.error() == nullptr) {
                m_expiry = temp;
            }
            else {
                is.setstate(ios::failbit);
                message("Invalid Date Entry");
            }
        }
        is.ignore(1000, '\n'); // clear the input buffer
        return is;
    }


}
