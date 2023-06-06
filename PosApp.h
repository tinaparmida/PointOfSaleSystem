/* Citation and Sources...
Final Project Milestone q=1
Module: PosApp
Filename: PosApp.h
Version 1.0
Author	Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

#include "Item.h"
#include "NonPerishable.h"
#include "Perishable.h"

// PosApp.h
#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H

namespace sdds {
    class PosApp {
        char m_filename[128];
        bool m_isValid;
    

        Item* Iptr[MAX_NO_ITEMS] = { nullptr };
        int nptr = 0;
        void pause() const;
        int getIntChoice();
        void listItems();
        void addItem();
        int selectItem();
        void removeItem();
        void stockItem();
        void saveRecs();
        void loadRecs();

    public:
        PosApp(const char* filename);
        void POS();
        void run();
        void sortItemsByName(Item* items[], int n) const;
        void printTitle(const char* title);
        ~PosApp();

    };
}
#endif