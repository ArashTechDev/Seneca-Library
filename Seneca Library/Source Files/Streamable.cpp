//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca

#include "Streamable.h"
#define _CRT_SECURE_NO_WARNINGS
namespace sdds {
    Streamable::~Streamable() {};
    std::ostream& operator<<(std::ostream& os, const Streamable& s)
    {
        if (s)
        {
            s.write(os);
        }
        return os;
    }

    std::istream& operator>>(std::istream& is, Streamable& s)
    {
        return (s.read(is));
    }
}