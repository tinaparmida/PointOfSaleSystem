/* Citation and Sources...
Final Project Milestone q=1
Module: PosIO
Filename: Item.h
Version 1.0
Author	PARMIDA Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "Error.h"

namespace sdds {

    class Item : public PosIO {

        char m_sku[MAX_SKU_LEN + 1];
        char* m_name;
        double m_price;
        bool m_taxed;
        int m_quantity;
        Error m_err;
       



    protected:
        void name(const char* value);
      

        void message(const char* errorMessage);
        bool isClear() const;

    public:
          const char* name() const;
          int m_displayType;
         
        operator bool() const;

        Item& displayType(int type);

        void bprint(std::ostream& os) const;
        Item();
        Item(const char* sku, const char* name, double price, bool taxed);
        Item(const Item&);
        Item& operator=(const Item&);
        virtual ~Item();

        void sku(const char* value);
        void price(double value);
        void taxed(bool value);
        void quantity(int value);
        double cost() const;

        const char* sku() const;
        const double price() const;
        const bool taxed() const;
        const int quantity() const;
        const bool isEmpty() const;


      

        bool operator==(const char*) const;
        bool operator>(const Item& src) const;

        int operator+=(int);
        int operator-=(int);

        operator double() const;

       
        virtual char itemType() const;

        virtual std::ostream& write(std::ostream& os, int format) const;
        virtual std::istream& read(std::istream& is);

        virtual std::ofstream& save(std::ofstream& file)const;
        virtual std::ifstream& load(std::ifstream& file);
    };



    std::ostream& operator<<(std::ostream& os, const Item& I);
    std::istream& operator>>(std::istream& is, Item& I);
    std::ofstream& operator<<(std::ofstream& file, const Item& I);
    std::ifstream& operator>>(std::ifstream& file, Item& I);

    double operator+=(double&, const Item&);


}

#endif
