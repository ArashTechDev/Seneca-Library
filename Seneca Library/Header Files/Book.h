//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include "Publication.h"


namespace sdds {
    class Book : public Publication {
        char* m_author;
    public:
        Book();
        Book(const Book& b);
        Book& operator=(const Book& b);
        ~Book();
       
        char type() const;
        bool conIO(std::ios& io) const;

        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);

        void set(int member_id);
        operator bool() const;
    };
}


#endif //SDDS_BOOK_H
