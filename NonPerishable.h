/* Citation and Sources...
Final Project Milestone q=1
Module: NonPerishable
Filename: NonPerishable.h
Version 1.0
Author	PARMIDA Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#ifndef SDDS_NONPERISHABLE_H
#define SDDS_NONPERISHABLE_H

#include "Item.h"

namespace sdds {
    class NonPerishable : public Item {
    public:
        virtual char itemType() const override;
        virtual std::ostream& write(std::ostream& os, int writeMode) const;
        virtual std::ofstream& save(std::ofstream& file) const;
      
    };
}

#endif // !SDDS_NONPERISHABLE_H
