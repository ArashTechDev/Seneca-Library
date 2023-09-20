//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca


#define _CRT_SECURE_NO_WARNINGS
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>


namespace sdds {
    void Publication::setToDefault()
    {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        resetDate();
    }

    Publication::Publication() {
        setToDefault();
    }

    Publication::~Publication()
    {
        delete[] m_title;
    }



    void Publication::set(int member_id) {
        m_membership = member_id;
    }

    void Publication::setRef(int value) {
        m_libRef = value;
    }

    void Publication::resetDate() {
        m_date = Date();
    }

    char Publication::type() const {
        return 'P';
    }

    bool Publication::onLoan() const {
        return (m_membership != 0);
    }

    Date Publication::checkoutDate() const {

        return m_date;
    }

    bool Publication::operator==(const char* title) const {
        return strstr(m_title, title) != NULL;
    }

    Publication::operator const char* () const {
        return m_title;
    }

    int Publication::getRef() const {
        return m_libRef;
    }

    int Publication::getMemID() const {
        return m_membership;
    }

    bool Publication::conIO(std::ios& io) const
    {
        return &io == &std::cin || &io == &std::cout;
    }

    Publication::Publication(const Publication& newPub)
    {
        if (newPub.m_title) {
            *this = newPub;
        }
        else {
            setToDefault();
        }
    }

    Publication& Publication::operator=(const Publication& newPub)
    {
        if (m_title)
        {
            delete[] m_title;
           
        }
        m_title = nullptr;

        set(newPub.m_membership);
        setRef(newPub.m_libRef);
        strcpy(m_shelfId, newPub.m_shelfId);
        m_date = newPub.m_date;

       
        if (newPub.m_title != nullptr)
        {
            m_title = new char[strlen(newPub.m_title) + 1];
            strcpy(m_title, newPub.m_title);
        }
        else
        {
            setToDefault();
        }

        return *this;
    }



    ostream& Publication::write(ostream& os) const
    {
        if (conIO(os))
        {
            os << "| " << m_shelfId << " | ";
            int i = 0;
            for (i = 0; i < SDDS_TITLE_WIDTH; i++)
            {
                if (m_title[i] == '\0')
                    break;
                else                
                    os << m_title[i];
                
            }
            for (i = i; i < SDDS_TITLE_WIDTH; i++)
            {
                os << ".";
            }
            os << " | ";
            if (m_membership == 0) {
                os << " N/A ";
            }
            else {
                os << m_membership;
            }
            os << " | " << m_date << " |";
        }
        else
        {
            os << type();
            os << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";

            if (m_membership == 0) {
                os << "0";
            }
            else {
                os << m_membership;
            }
            os << "\t" << m_date;
            if (type() == 'P')
            {
                os << endl;
            }
        }

        return os;
    }

    std::istream& Publication::read(std::istream& istr){
        char* tempTitle = new  char[256];
    if (!tempTitle) {
        istr.setstate(std::ios::failbit);
        return istr;
    }

    char tempShelf[SDDS_SHELF_ID_LEN + 2] = { '\0' };
    int tempMem = 0, tempLib = -1;
    Date date;
    setToDefault();

    if (conIO(istr)) {
        std::cout << "Shelf No: ";
        istr >> tempShelf;
        if (strlen(tempShelf) != SDDS_SHELF_ID_LEN) {
            istr.setstate(std::ios::failbit);
        }
        else {
            istr.ignore(1000, '\n');
        }
        std::cout << "Title: ";
        istr.getline(tempTitle, 256, '\n');
        std::cout << "Date: ";
        istr >> date;
    }
    else {
        istr >> tempLib;
        if (istr.peek() == '\t') {            // saw it on https://www.geeksforgeeks.org/basic_istreampeek-in-c-with-examples/
            istr.ignore();
        }

        istr.get(tempShelf, SDDS_SHELF_ID_LEN + 2, '\t');
        istr.ignore();

        istr.get(tempTitle, 256, '\t');
        istr.ignore();

        istr >> tempMem;
        if (istr.peek() == '\t') {
            istr.ignore();
        }

        istr >> date;
    }

    if (!date) {
        istr.setstate(ios::failbit);
    }

    if (istr) {
        delete[] m_title;
        m_title = nullptr;

        m_title = new char[strlen(tempTitle) + 1];
        if (!m_title) {
            istr.setstate(ios::failbit);
        }
        else {
            strcpy(m_title, tempTitle);
            strcpy(m_shelfId, tempShelf);
            m_membership = tempMem;
            m_date = date;
            m_libRef = tempLib;
        }
    }

    delete[] tempTitle;
    return istr;
    }


    Publication::operator bool() const {
        return m_title != nullptr && m_shelfId[0] != '\0';
    }

}