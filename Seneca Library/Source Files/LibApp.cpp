//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits> 
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Lib.h"
#include "Menu.h"
#include "Publication.h"
#include "LibApp.h"
#include "PublicationSelector.h"
#include "Book.h"
#include "Date.h"

using namespace std;

namespace sdds {
    LibApp::LibApp(const char* filename) : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_publicationMenu("Choose the type of publication:") {
        if (filename)        {
            strcpy(m_filename, filename);
        }
        m_changed = false;
        NOLP = 0;
        LLRN = 0;
     
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_publicationMenu << "Book" << "Publication";
        load();
    }

    LibApp::~LibApp() {
        for (int i = 0; i < NOLP; i++)
        {
            delete PPA[i];
        }
    }


    bool LibApp::confirm(const char* message) {
        Menu confirm(message);

        confirm << "Yes";
        return confirm.run() == 1;
    }


    void LibApp::load() {
        cout << "Loading Data" << std::endl;
        ifstream readFile(m_filename);

        char type{};
        int i;
        for (i = 0; readFile && i < SDDS_LIBRARY_CAPACITY; i++)
        {
            readFile >> type;
            readFile.ignore();
            if (readFile)
            {
                if (type == 'P')
                    PPA[i] = new Publication;

                else if (type == 'B')
                    PPA[i] = new Book;


                if (PPA[i])
                {
                    readFile >> *PPA[i];
                    NOLP++;
                    LLRN = PPA[i]->getRef();
                }

            }
        }
    }



    Publication* LibApp::getPub(int libRef) {
        Publication* found = nullptr;
        for (int i = 0; i < NOLP; i++)
        {
            if (PPA[i]->getRef() == libRef)
            {
                found = PPA[i];
            }
        }

        return found;
    }


    void LibApp::save() {

        cout << "Saving Data" << endl;
        ofstream savedFile(m_filename);
        int i = 0;

        for (i = 0; i < NOLP; i++) {
            if (PPA[i]->getRef() != 0)
            {
                savedFile << *PPA[i];
            }
        }

        savedFile.close();
    }

    int LibApp::search(int searchMode) {

        char title[256]{};
        char type;
        int libRef = 0;
        bool matched = false;

        switch (m_publicationMenu.run()) {
        case 1:
            type = 'B';
            break;
        case 2:
            type = 'P';
            break;
        default:
            return libRef; 
        }
        cin.ignore(1000, '\n');

        cout << "Publication Title: ";
        cin.getline(title, 256);

        PublicationSelector pubSel("Select one of the following found matches:", 15);

        for (int i = 0; i < NOLP; i++) {

            if (PPA[i]->operator== (title) 
                   && type == PPA[i]->type()
                && PPA[i]->getRef() != 0) 
            {
                switch (searchMode) {
                case 1:
                    matched = true;
                    break;
                    
                case 2:
                    matched = PPA[i]->onLoan();
                    break;
                case 3:
                    matched = !PPA[i]->onLoan();

                    break;
                }
                if (matched) {

                    pubSel << PPA[i];
                }
            }
        }

        if (pubSel)
        {
            pubSel.sort();
            libRef = pubSel.run();

            if (libRef > 0) {
               cout << *getPub(libRef) << std::endl;
            }
            else {
               cout << "Aborted!" << std::endl;
            }
        }
        else{
            cout << "No matches found!" << std::endl;
        }

        return libRef;
    }


    void LibApp::returnPub() {
        bool exit = false;
        cout << "Return publication to the library" << endl;

        int libRef = search(2);
        if (!(libRef > 0))
        {
            exit = true;
        }

        if (!exit)
        {
            bool confirmed = confirm("Return Publication?");

            if (confirmed)
            {
                int numdaysL = Date() - getPub(libRef)->checkoutDate();
                if (numdaysL > SDDS_MAX_LOAN_DAYS) {
                    double penalty = (numdaysL - SDDS_MAX_LOAN_DAYS) * 0.5;
                    cout << std::fixed << setprecision(2);
                    cout << "Please pay $" << penalty << " penalty for being " << (numdaysL - SDDS_MAX_LOAN_DAYS) 
                        << " days late!" <<endl;
                }
                getPub(libRef)->set(0);
                m_changed = true;
            }

           cout << "Publication returned" << endl;
        }

       cout << "\n";
    }

    void LibApp::newPublication()
    {
        bool menu = false;

        if (NOLP == SDDS_LIBRARY_CAPACITY)
        {
            cout << "Library is at its maximum capacity!" << endl;
            menu = true;
        }

        if (!menu)
        {
            cout << "Adding new publication to the library" << endl;
            int pubType = m_publicationMenu.run();
            std::cin.ignore(1000, '\n');
            Publication* newPub = nullptr;

            if (pubType == 0)
            {
                cout << "Aborted!" << endl;
                menu = true;
            }

            else if (pubType == 1)
            {
                newPub = new Book;
                cin >> *newPub;
            }
             else if (pubType == 2)
            {
                newPub = new Publication;
                cin >> *newPub;
            }

            if (cin.fail())
            {
                cin.ignore(1000, '\n');
                cin.clear();
                cout << "Aborted!" << endl;
                exit(0);
            }
            else
            {
                if (!menu && confirm("Add this publication to the library?"))
                {
                    if (!(*newPub))
                    {
                        cout << "Failed to add publication!" << endl;
                        delete newPub;
                    }


                    else
                    {
                        LLRN++;
                        newPub->setRef(LLRN);
                        PPA[NOLP] = newPub;

                        NOLP++;
                        m_changed = true;

                       cout << "Publication added" << std::endl;
                    }
                }
            }
        }

        cout << endl;
    }

    void LibApp::removePublication()
    {
        cout << "Removing publication from the library" << endl;
        int libRef = search(1);
        if (libRef)
        {
            if (confirm("Remove this publication from the library?"))
            {
                getPub(libRef)->setRef(0);
                m_changed = true;

                cout << "Publication removed" << endl;
            }
        }

        cout << endl;
    }
    int validateInput(int min, int max, const char* errorMsg) {
        int input;

        do {
            cin >> input;

            if (!std::cin || input < min || input > max) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << errorMsg;
            }
            else {
                return input;
            }
        } while (true);
    }

    void LibApp::checkOutPub()
    {
        cout << "Checkout publication from the library" << endl;
        int libRef = search(3);
        if (libRef > 0)
        {
            bool confirmed = confirm("Check out publication?");
            if (confirmed)
            {
                std::cout << "Enter Membership number: ";

                int inputMembership = validateInput(10000, 99999, "Invalid membership number, try again: ");
                getPub(libRef)->set(inputMembership);

                m_changed = true;
                cout << "Publication checked out" << endl;
            }
        }
        cout << "\n";
    }

    void LibApp::run()
    {
        int menu, exit;

        do {
            menu = m_mainMenu.run();
            switch (menu)
            {
            case 0:
                if (m_changed == true)
                {
                    exit = m_exitMenu.run();
                    switch (exit)

                    {
                    case 0:
                        if (confirm("This will discard all the changes are you sure?"))
                        {
                            m_changed = false;
                        }
                        break;

                    case 1:
                        save();
                        break;

                    case 2:
                        menu = 1;
                        break;
                    }
                }
                cout << endl;
                break;
            case 1:
                newPublication();
                break;
            case 2:
                removePublication();
                break;
            case 3:
                checkOutPub();
                break;
            case 4:
                returnPub();
                break;
            }
        } while (menu != 0);

       cout << "-------------------------------------------" << endl;
       cout << "Thanks for using Seneca Library Application" << endl;
    }
}
