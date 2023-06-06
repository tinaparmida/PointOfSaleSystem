/* Citation and Sources...
Final Project Milestone q=1
Module: Perishable
Filename: Perishable.h
Version 1.0
Author	PARMIDA Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds {

    class Perishable : public Item {

        Date m_expiry;

    public:
        
        virtual ~Perishable() {}
        virtual char itemType() const override;
        std::ofstream& save(std::ofstream& file) const;
        std::ifstream& load(std::ifstream& file);
        std::ostream& write(std::ostream& os, int linear) const;
        std::istream& read(std::istream& is);

    };

}
#endif // !SDDS_PERISHABLE_H
