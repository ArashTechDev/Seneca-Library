//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca


#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
using namespace std;


namespace sdds {
    Book::Book()
    { m_author = nullptr;

    }



   Book::Book(const Book& b) : Publication(b) {
    if (b.m_author) {
        m_author = new char[strlen(b.m_author) + 1];
        strcpy(m_author, b.m_author);
    }
    else {
        m_author = nullptr;
    }
}

    Book& Book::operator=(const Book& src)
    {
        Publication::operator=(src);
        

        if (src.m_author != nullptr)
        {
            if (m_author)
            {
                delete[] m_author;
               
            }
            m_author = nullptr;
            m_author = new char[strlen(src.m_author) + 1];
            strcpy(m_author, src.m_author);
        }
        else
        {
            m_author = nullptr;
        }
        return *this;
    }

    Book::~Book()
    {
        delete[] m_author;
    }

    bool Book::conIO(std::ios& io) const
    {
        return &io == &std::cin || &io == &std::cout;
    }

    char Book::type() const{
        return 'B';
    }


    ostream& Book::write(std::ostream& os) const
        
    {
        Publication::write(os);
        if (conIO(os))
        {
            os << " ";
            int i = 0;
            for (i = 0; i < SDDS_AUTHOR_WIDTH; i++)
            {
                if (m_author[i] == '\0')
                {
                    break;
                }
                else
                {
                    os << m_author[i];
                }
            }
            for (i = i; i < SDDS_AUTHOR_WIDTH; i++)
            {
                os << " ";
            }
            os << " |";
        }
        else
        {
            os << '\t' << m_author;
            os << '\n';
        }
        return os;
    }


    std::istream& Book::read(std::istream& istr)
    {      
        Publication::read(istr);
        char temp[256];

        if (m_author)
        {
            delete[] m_author;
        }
        m_author = nullptr;

        if (conIO(istr))
        {
            istr.ignore();
            std::cout << "Author: ";
            istr.getline(temp, 256,'\n');
        }
        else
        {
            istr.ignore();
            istr.get(temp, 256,'\n');
        }

        if (istr)
        {
            m_author = new char[strlen(temp) + 1];
            strcpy(m_author, temp);
        }
        return istr;
    }

    void Book::set(int member_id)
    {
        Publication::set(member_id);
        Publication::resetDate();
    }

   
        Book::operator bool() const {
        return m_author && Publication::operator bool();
    }

}

