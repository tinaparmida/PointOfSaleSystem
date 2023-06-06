/* Citation and Sources...
Final Project Milestone q=1
Module: PosIO
Filename: Item.cpp
Version 1.0
Author	PARMIDA Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include "Item.h"
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

namespace sdds {
    void Item::name(const char* value) {
        if (value != nullptr && value[0] != '\0') {
            size_t len = strlen(value);
            if (len > 0) {
                m_name = new char[len + 1];
                strcpy(m_name, value);
            }
        }
    }

    char Item::itemType() const {
        // return a default value for the base class
        return 'I';
    }


    const char* Item::name() const {
        return m_name;
    }

    double Item::cost() const {
        return m_price * (1 + (m_taxed ? TAX : 0));
    }

    void Item::message(const char* errorMessage) {
        m_err = errorMessage;
    }

    bool Item::isClear() const {
        return !m_err;
    }

    Item::Item() {
        sku("");
        m_name = nullptr;
        price(0);
        taxed(true);
        quantity(0);
        message("");
        m_displayType = 0;
    }

    Item::Item(const char* sku, const char* name, double price, bool taxed) {
        this->sku(sku);
        this->name(name);
        this->price(price);
        this->taxed(taxed);
        quantity(0);
        message("");
        m_displayType = 0;
    }

    Item::Item(const Item& src) {
        sku(src.m_sku);

        if (src.m_name) {
            m_name = new char[strlen(src.m_name) + 1];
            strcpy(m_name, src.m_name);
        }
        else {
            m_name = nullptr;
        }

        price(src.m_price);
        taxed(src.m_taxed);
        quantity(src.m_quantity);
        message(src.m_err);
        m_displayType = src.m_displayType;
    }
    Item& Item::operator=(const Item& src) {
        if (this != &src) {
            sku(src.m_sku);
            price(src.m_price);
            taxed(src.m_taxed);
            quantity(src.m_quantity);
            message(src.m_err);
            m_displayType = src.m_displayType;

            // Delete the old name only after checking whether the new name is valid
            char* temp = m_name;
            m_name = nullptr;
            if (src.m_name) {
                m_name = new char[strlen(src.m_name) + 1];
                strcpy(m_name, src.m_name);
            }
            if (temp != nullptr) {
                delete[] temp;
            }
        }
        return *this;
    }


    Item::~Item() {
        delete[] m_name;
        m_name = nullptr;
    }

    void Item::sku(const char* value) {
        strncpy(m_sku, value, MAX_SKU_LEN);
        m_sku[MAX_SKU_LEN] = '\0';
    }

    void Item::price(double value) {
        m_price = value;
    }

    void Item::taxed(bool value) {
        m_taxed = value;
    }

    void Item::quantity(int value) {
        m_quantity = value;
    }

    const char* Item::sku() const {
        return m_sku;
    }

    const double Item::price() const {
        return m_price;
    }

    const bool Item::taxed() const {
        return m_taxed;
    }

    const int Item::quantity() const {
        return m_quantity;
    }

    const bool Item::isEmpty() const {
        return m_sku[0] == '\0' || m_name == nullptr || m_price == 0.0 || m_quantity == 0 || m_err;
    }


    bool Item::operator==(const char* sku) const {
        return strcmp(m_sku, sku) == 0;
    }

    bool Item::operator>(const Item& src) const {
        if (m_sku != nullptr && src.m_sku != nullptr) {
            return strcmp(m_sku, src.m_sku) > 0;
        }
        else {
            return false;
        }
    }





    int Item::operator+=(int cnt) {
        if (cnt > 0) {
            m_quantity += cnt;
            if (m_quantity > MAX_QUANTITY_VALUE) {
                message("Too many items!");
                m_quantity = MAX_QUANTITY_VALUE;
            }
        }
        return m_quantity;
    }

    int Item::operator-=(int cnt) {
        if (cnt > 0) {
            m_quantity -= cnt;
            if (m_quantity < 0) {
                message("Too few items!");
                m_quantity = 0;
            }
        }
        return m_quantity;
    }

    Item::operator double() const {
        return cost() * quantity();
    }

    std::ostream& Item::write(std::ostream& os, int format) const {
        if (!isClear()) {
            os << m_err<< endl;
        }
        else {
            if (format == POS_LIST) {
                std::string temp_name = m_name;
                if (temp_name.length() > 20) {
                    temp_name = temp_name.substr(0, 20);
                }
                os << left << setw(6) << m_sku << " |"
                    << left << setw(20) << temp_name << "| "
                    << right << fixed << std::setprecision(2) << std::setw(6) << price() << "| "
                    << right << setw(1) << (taxed() ? "X" : " ") << " | "
                    << right << setw(3) << quantity() << "| "
                    << right << setw(8) << fixed << setprecision(2) << cost() * quantity() << '|';
               
            }

            else if (format == POS_FORM) {
                os << "=============v" << endl
                    << "Name:        " << m_name << endl
                    << "Sku:         " << m_sku << endl
                    << "Price:       " << fixed << setprecision(2) << price() << endl;
                if (taxed()) {
                    os << "Price + tax: " << fixed << setprecision(2) << cost()  << endl;
                }
                else {
                    os << "Price + tax: N/A" << endl;
                }
                os << "Stock Qty:   " << quantity() << endl;

            }
           
        }
        return os;
    }


    Item& Item::displayType(int type) {
     

            m_displayType = type;
    

        return *this;
    
    }



    std::istream& Item::read(std::istream& is) {
        char sku[256] = "";
        char name[256] = "";
        double price = 0.0;
        char taxed = '\0';
        int qty = 0;
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Sku" << endl;
        do {
            cout << "> ";
            is.getline(sku, MAX_SKU_LEN);
            if (strlen(sku) == 0 || strlen(sku) > MAX_SKU_LEN) {
                cout << "SKU too long" << endl;

            }


        } while (strlen(sku) > MAX_SKU_LEN);

        cout << "Name" << endl;
        do {
            cout << "> ";

            is.getline(name, MAX_NAME_LEN + 1);
            if (strlen(name) >= MAX_NAME_LEN) {
                cout << "Item name too long" << endl;

             
                is.ignore(1000, '\n'); // clear the input stream buffer
            }
        } while (strlen(name) >= MAX_NAME_LEN);

        cout << "Price" << endl;
        bool validInput = false;
        while (!validInput) {
            cout << "> ";

            if (is >> price) { // if input is a valid float
                if (price >= 0) { // if price is non-negative
                    validInput = true;
                }
                else {
                    cout << "Invalid price value" << endl;
                    is.clear();
                    is.ignore(1000, '\n'); // clear the input stream buffer
                }
            }
            else { // if input is not a valid float
                cout << "Invalid price value" << endl;
           
                is.ignore(1000, '\n'); // clear the input stream buffer
            }
        }

        cout << "Taxed?\n(Y)es/(N)o: ";
        do {

            cin >> taxed;
            if (taxed != 'y' && taxed != 'n') {
                cout << "Only 'y' and 'n' are acceptable: ";

            }


            is.ignore(1000, '\n'); // clear the input stream buffer
        } while (taxed != 'y' && taxed != 'n');



        cout << "Quantity" << endl;
        validInput = false;
        while (!validInput) {
            cout << "> ";

            if (is >> qty) { // if input is a valid integer
                if (qty > 0 && qty < MAX_STOCK_NUMBER) { // if quantity is in valid range
                    validInput = true;
                }
                else {
                    cout << "Invalid quantity value" << endl;
                   
                    is.ignore(1000, '\n'); // clear the input stream buffer
                }
            }
            else { // if input is not a valid integer
                cout << "Invalid quantity value" << endl;
             
                is.ignore(1000, '\n'); // clear the input stream buffer
            }
        }

        bool taxStatus = (taxed == 'y') ? true : false;
        *this = Item(sku, name, price, taxStatus);
        quantity(qty);

      
        return is;
    }


    std::ofstream& operator<<(std::ofstream& file, const Item& I)

    {

        I.save(file);
        return file;
    }

    Item::operator bool() const {
        return  !m_err;
    }

    std::ifstream& operator>>(std::ifstream& file, Item& I)

    {

        return  I.load(file);

    }

    std::ostream& operator<<(std::ostream& os, const Item& I) {

        I.write(os, I.m_displayType);
        return os;


    }

    std::istream& operator>>(std::istream& is, Item& I) {


        I.read(is);
        return is;
    }


    double operator+=(double& value, const Item& I) {
        value += I.cost() * I.quantity();
        return value;
    }

    std::ofstream& Item::save(std::ofstream& file)const {
        file << itemType() << ',' << sku() << ',' << name() << ',' << std::fixed << std::setprecision(2) << price() << ',' << taxed() << ',' << quantity();
        return file;
    }



    std::ifstream& Item::load(std::ifstream& file)
    {
        m_err.clear();
        bool hasError = false;

        char sku[100];
        char name[100];
        double price;
        bool taxed;
        int quantity;

        file.getline(sku, 100, ',');
        if ((strlen(sku) > MAX_SKU_LEN) || file.fail())
        {
            m_err.error("SKU too long");
            hasError = true;
        }
        file.getline(name, 100, ',');
        if (!hasError && ((strlen(name) > MAX_NAME_LEN) || file.fail()))
        {
            m_err.error("Item name too long");
            hasError = true;
        }
        file >> price;
        if (!hasError && ((price < 0) || file.fail()))
        {
            m_err.error("Invalid price value");
            hasError = true;
        }
        file.ignore();
        file >> taxed;
        if (!hasError && ((taxed != 1 && taxed != 0) || file.fail()))
        {
            m_err.error("Invalid quantity value");
            hasError = true;
        }
        file.ignore();
        file >> quantity;
        if (!hasError && ((quantity > MAX_STOCK_NUMBER) || file.fail()))
        {
            m_err.error("Invalid quantity value");
            hasError = true;
        }

        if (!hasError)
        {
            strcpy(m_sku, sku);
            m_price = price;
            m_quantity = quantity;

            delete[] m_name;
            m_name = nullptr;

            m_name = new char[strlen(name) + 1];
            strcpy(m_name, name);

            if (taxed == 1)
            {
                m_taxed = true;
            }
            else if (taxed == 0)
            {
                m_taxed = false;
            }

          
        }
        
        cout.flush();
        return file;
    }



    void Item::bprint(std::ostream& os) const {
        std::string temp_name = m_name;
        if (temp_name.length() > 20) {
            temp_name = temp_name.substr(0, 20);
        }
        os << "| " << std::left << std::setw(20) << setfill(' ') << temp_name << "| ";
        os << std::right << std::setw(9) << std::fixed << std::setprecision(2) << (taxed() ? m_price * (1 + TAX) : m_price) << " | ";
        os << std::setw(2) << (taxed() ? "T" : " ") << "  |" << endl;

    }






}
