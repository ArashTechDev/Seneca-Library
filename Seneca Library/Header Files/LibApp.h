//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H

#include <iostream>
#include "Menu.h"
#include "Lib.h"
#include "Streamable.h"
#include "Publication.h"
#include "Book.h"

namespace sdds {
    class LibApp {
    private:
        char m_filename[256];
        Publication* PPA[SDDS_LIBRARY_CAPACITY];
        int NOLP;
        int LLRN;
        bool m_changed;
        Menu m_mainMenu;
        Menu m_exitMenu;
        Menu m_publicationMenu;

        bool confirm(const char* message);
        void load();
        void save();
        int search(int searchMode);
        void returnPub();
        void newPublication();
        void removePublication();
        void checkOutPub();

    public:
        LibApp(const char* fileName);
        ~LibApp();
        void run();
        Publication* getPub(int libRef);

    };
}

#endif