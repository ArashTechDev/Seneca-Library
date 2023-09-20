//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca
#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H

#include "Date.h"
#include "Streamable.h"
#include "Lib.h"
using namespace std;

namespace sdds {
    class Publication : public Streamable {
    private:
        char* m_title;
        char m_shelfId[SDDS_SHELF_ID_LEN + 1];
        int m_membership;
        int m_libRef;
        Date m_date;
    public:
        Publication(); 
        ~Publication();
        Publication(const Publication& newPub);
        Publication& operator=(const Publication& newPub);
        void setToDefault();
        virtual void set(int member_id);
        void setRef(int value);
        void resetDate();
        virtual char type() const;
        bool onLoan() const;
        Date checkoutDate() const;
        bool operator==(const char* title) const;
        operator const char* () const;
        int getRef() const;
        int getMemID() const;
        bool conIO(std::ios& io) const;
        ostream& write(ostream& os) const;
        istream& read(istream& is);
        operator bool() const;
    };
}

#endif //SDDS_PUBLICATION_H
