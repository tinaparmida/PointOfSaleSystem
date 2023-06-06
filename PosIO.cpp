/* Citation and Sources...
Final Project Milestone q=1
Module: PosIO
Filename: PosIO.cpp
Version 1.0
Author	PARMIDA Tina Khakian 133117226

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "PosIO.h"
using namespace std;
namespace sdds {

    std::ostream& operator<<(std::ostream& os, const PosIO& D) {
        D.write(os, true);
        return os;
    }

    std::istream& operator>>(std::istream& is, PosIO& D) {
        D.read(is);
        return is;
    }

    std::ofstream& operator<<(std::ofstream& file, const PosIO& D) {
        D.save(file);
        return file;
    }

    std::ifstream& operator>>(std::ifstream& file, PosIO& D) {

        return  D.load(file);
    }

}
