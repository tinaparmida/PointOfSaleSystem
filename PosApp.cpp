/* Citation and Sources...
Final Project Milestone q=1
Module: PosApp
Filename: PosApp.cpp
Version 1.0
Author	Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>
#include <algorithm>
#include "PosApp.h"
#include "NonPerishable.h"
#include "Perishable.h"
#include "Bill.h"


using namespace std;

namespace sdds {
    PosApp::PosApp(const char* filename) {

        if (filename != nullptr && filename[0] != '\0' && strlen(filename) < 128) {
            strcpy(m_filename, filename);
            m_isValid = true;
        }
        else {
            m_filename[0] = '\0';
            m_isValid = false;
        }
    }
    void PosApp::POS() {
        cout << ">>>> Starting Point of Sale.................................................." << endl;
        bool done = false;
        Bill bill;
        string sku;
        double total = 0;
        cin.ignore(1000, '\n');

        while (!done) {
            cout << "Enter SKU or <ENTER> only to end sale..." << endl;
            cout << "> ";
            getline(cin, sku);
           
            // Check if the input is empty or whitespace
            if (sku.empty() || isspace(sku[0])) {

                 done = true;

                continue;
            }
          

            int index = -1;
            for (int i = 0; i < nptr; i++) {
                if (Iptr[i]->sku() == sku) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                cout << "!!!!! Item Not Found !!!!!" << endl;
            }
            else {
                Item* item = Iptr[index];
                if (item->quantity() == 0) {
                    cout << "Item out of stock" << endl;
                }
                else {
                    item->quantity(item->quantity() - 1);
                    item->write(cout, POS_FORM);
                    bill.add(item);
                    cout << endl << ">>>>> Added to bill" << endl;
                    total += item->cost();                
                    cout << ">>>>> Total: " << fixed << setprecision(2) << total << endl;
                    
                }
            }
        }
        bill.print(cout);

    }


    void PosApp::pause() const {
        cout << "Press <ENTER> to start....";
        cin.ignore(1000, '\n');
        cout << endl;
    }
 
    int PosApp::getIntChoice() {
        cin.clear(); 
        int choice = -1;
        bool validInput = false;
        while (!validInput) {
        
            cin >> choice;

            if (cin.fail()) { // Check for invalid input
                cin.clear();
                cin.ignore(1000, '\n');
              cout << "Invalid Integer, try again: ";
            }
            else if (choice < 0 || choice > 5) { // Check for out-of-range input
                cout << "[0<=value<=5], retry: > ";
            }  
            else {
                validInput = true;
            }
        }
        return choice;
    }




    void PosApp::listItems() {
        printTitle("Listing Items");
        double total = 0;
        int row = 1;
        sortItemsByName(const_cast<Item**>(Iptr), nptr);
        cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
        cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
        for (int i = 0; i < nptr; i++) {
            cout << setw(4) << row << " | ";
            Iptr[i]->write(cout, true);
            cout << endl;
            total += Iptr[i]->cost() * Iptr[i]->quantity();
            row++;
        }
        cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
        cout << setw(42) << "Total Asset: $  |" << setw(15) << fixed << setprecision(2) << total << "|" << endl;
        cout << "-----------------------------------------------^--------------^" << endl << endl;
    }



    void PosApp::addItem() {
        printTitle("Adding Item to the store");
        if (nptr == MAX_NO_ITEMS) {
            cout << "Inventory Full!" << endl;
            return;
        }
        Item* item = nullptr;
        bool isPerishable = false;
        cout << "Is the Item perishable? (Y)es/(N)o: ";
        char answer;
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            isPerishable = true;
        }
        if (isPerishable) {
            item = new Perishable();
       

        }
        else if (!isPerishable) {
            item = new NonPerishable();
     
        }
              item->read(cin); 
                 

                Iptr[nptr] = item;
                nptr++;
       
                printTitle("DONE!");

    }

    int PosApp::selectItem() {
        int choice = -1;
        bool validInput = false;
         printTitle("Item Selection by row number");
            pause();
            printTitle("Listing Items");
            double total = 0;
            int row = 1;
            sortItemsByName(const_cast<Item**>(Iptr), nptr);
            cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
            cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
            for (int i = 0; i < nptr; i++) {
                cout << setw(4) << row << " | ";
                Iptr[i]->write(cout, true);
                cout << endl;
                total += Iptr[i]->cost() * Iptr[i]->quantity();
                row++;
            }
            cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
            cout << "Enter the row number: ";
            while (!validInput) {
           
           
            if (!(cin >> choice)) { // Check for invalid input
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Integer, try again: ";
                continue;
            }
            if (choice < 0 || choice > nptr) { // Check for out-of-range input
                cout << "[1<=value<=" << nptr << "], retry: Enter the row number: ";
                continue;
            }
            validInput = true;
        }
        return choice - 1;
    }


// Remove an item from the Iptr array and deallocate memory
    void PosApp::removeItem() {
     
        printTitle("Remove Item");
        int index = selectItem();
        Item* item = Iptr[index];
        for (int i = index; i < nptr - 1; i++) {
            Iptr[i] = Iptr[i + 1];
        }
        cout << "Removing...." << endl;
        item->write(cout, POS_FORM);
        Iptr[nptr - 1] = nullptr;
        nptr--;
        delete item;
        item = nullptr;
        printTitle ("DONE!");
    }

    void PosApp::stockItem() {

        printTitle("Select an item to stock");
        int index = selectItem();
        Item* item = Iptr[index];
        
        cout << "Selected Item:" << endl;

        item->write(cout, POS_FORM);
        cout  << "Enter quantity to add: ";
        int quantity = -1;
        bool validInput = false;
        while (!validInput) {
            cin >> quantity;
            if (cin.fail() ) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Integer, try again: ";
            } else if ( quantity < 1 || quantity > MAX_STOCK_NUMBER - item->quantity()) {
                cout << "[" << 1 << "<=value<=" << MAX_STOCK_NUMBER - item->quantity() << "], retry: Enter quantity to add: ";
                continue;
            }
            else {
                validInput = true;
            }
        }
        item->quantity(item->quantity() + quantity);
        printTitle("DONE!");
    }


    void PosApp::loadRecs() {
       
        printTitle("Loading Items");

        ifstream input(m_filename);
        if (!input) {
            // If the file cannot be opened, create it.
            ofstream output(m_filename);
            output.close();
            input.open(m_filename);
        }

        if (!input) {
            cerr << "Cannot create data file: " << m_filename << endl;
            m_isValid = false;
            return;
        }

       

        // Read in the items.
        
        char type;
        while (input >> type && !input.eof() && nptr < MAX_NO_ITEMS) {
            Item* item = nullptr;
            if (type == 'N') {
                item = new NonPerishable();
            }
            else if (type == 'P') {
                item = new Perishable();
            }

            if (item != nullptr) {
                input.ignore(); // Ignore the delimiter.
                item->load(input);
                Iptr[nptr] = item;
                nptr++;
            }
        }

        input.close();
     }

    void PosApp::saveRecs() {
        printTitle("Saving Data");
        ofstream file(m_filename);
        if (!file) {
            cerr << "Error: Cannot open file " << m_filename << " for writing." << endl;
            return;
        }
        for (int i = 0; i < nptr && i < MAX_NO_ITEMS; i++) { // check bounds of Iptr array
            Iptr[i]->save(file);
            
        }
    }


    PosApp::~PosApp() {
        for (int i = 0; i < nptr; i++) {
            delete Iptr[i];
            Iptr[i] = nullptr; // Optional: set the pointer to null to avoid accessing invalid memory.
        }
    }

    void PosApp::run() {
        if (m_isValid) {
            loadRecs();

            bool done = false;
            int choice = -1;
           
            while (!done) {
                
                cout << "The Sene-Store\n"
                    << "1- List items\n"
                    << "2- Add item\n"
                    << "3- Remove item\n"
                    << "4- Stock item\n"
                    << "5- POS\n"
                    << "0- exit program\n"
                    << "> ";
                choice = getIntChoice();
                
                switch (choice) {
                    case 1:
                        listItems();
                        
                        break;
                    case 2:
                        addItem();
                        
                        break;
                    case 3:
                        removeItem();
                        
                        break;
                    case 4:
                        stockItem();
                        
                        break;
                    case 5:
                        POS();
                       
                        break;
                    case 0:
                        saveRecs();
                        cout << "Goodbye!" << endl;
                        done = true;
                        break;
                   }
                }
            }
       
        else {
            cout << "Unable to load the data file: " << m_filename << endl;
        }
    }

    void PosApp::sortItemsByName(Item* items[], int n) const {
        std::sort(items, items + n, [](const Item* a, const Item* b) { return strcmp(a->name(), b->name()) < 0; });
    }

    void PosApp::printTitle(const char* title) {

        cout << ">>>> ";
        cout << left << setw(72) << setfill('.');
        cout << title << endl;
        cout.unsetf(ios::left);
        cout << setfill(' ');
    }


}