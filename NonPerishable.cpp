/* Citation and Sources...
Final Project Milestone q=1
Module: NonPerishable
Filename: NonPerishable.cpp
Version 1.0
Author	PARMIDA Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#include "NonPerishable.h"
#include "Item.h"
#include "iostream"

using namespace std;

namespace sdds {
    char NonPerishable::itemType() const {
        return 'N';
    }


    std::ostream& NonPerishable::write(std::ostream& os, int writeMode) const {
        Item::write(os, writeMode);
        if (isClear()) {
            if (writeMode == POS_LIST) {
                os << "     N / A   |";
               
            }
            
            
            
            if (writeMode == POS_FORM) {
                os << "=============^"<< endl;
            }
            
          
        }  
     
        return os;
    }


    std::ofstream& NonPerishable::save(std::ofstream& file) const {
        Item::save(file);
        file << endl;
        return file;
    }
}
