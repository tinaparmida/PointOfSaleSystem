/* Citation and Sources...
Final Project Milestone q=1
Module: PosIO
Filename: PosIO.h
Version 1.0
Author	PARMIDA Tina Khakian 133117226

-----------------------------------------------------------
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

#ifndef SDDS_POSIO_H_
#define SDDS_POSIO_H_
#include <iostream>
#include <fstream>

#include "POS.h"

namespace sdds {

    class PosIO {
    public:
        virtual std::ofstream& save(std::ofstream& file)const = 0;
        virtual std::ifstream& load(std::ifstream& file) = 0;
        virtual std::ostream& write(std::ostream& os, int format) const = 0;
        virtual std::istream& read(std::istream& is) = 0;

        virtual char itemType() const = 0;

        virtual ~PosIO() {}
    };
    std::ostream& operator<<(std::ostream& os, const PosIO& D);
    std::istream& operator>>(std::istream& is, PosIO& D);
    std::ofstream& operator<<(std::ofstream& file, const PosIO& D);
    std::ifstream& operator>>(std::ifstream& file, PosIO& D);
}
#endif // !SDDS_POSIO_H_
