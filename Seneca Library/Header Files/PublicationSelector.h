//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca

#ifndef SDDS_PUBLICATIONSELECTOR_H
#define SDDS_PUBLICATIONSELECTOR_H
#include "Publication.h"
namespace sdds {
    class PublicationSelector {
        const int allocationUnit{ 10 };
        const int m_pageSize{ };
        const Publication** m_pub{};
        char m_title[81]{};
        int m_currentPage{ 1 };
        int m_arraySize{};
        int m_noOfPubs{};
        void display(int page)const;
        int getSelectedLibRef()const;
    public:
        PublicationSelector(const char* title = "Select a publication: ", int pageSize = 15);
        ~PublicationSelector();
        PublicationSelector(const PublicationSelector&) = delete;
        PublicationSelector& operator=(const PublicationSelector&) = delete;
        PublicationSelector& operator<<(const Publication* pub);
        PublicationSelector& operator<<(const Publication& pub);
        operator bool()const;
        void reset();
        void sort();
        int run();
    };
}
#endif // !SDDS_PUBLICATIONSELECTOR_H