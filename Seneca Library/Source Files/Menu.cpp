//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include "Menu.h"
#include <limits>
#include <iostream>
using namespace std;

namespace sdds {
    MenuItem::MenuItem(const char* str) {
        if (str != nullptr) {
            item = new char[strlen(str) + 1];
            strcpy(item, str);
        }
        else {
            item = nullptr;
        }
    }

    MenuItem::~MenuItem() {
        delete[] item;
    }

    MenuItem::operator bool() const {
        return item != nullptr;
    }


    MenuItem::operator const char* () const {
        return item;
    }

    void MenuItem::display(ostream& os) const {
        if (item != nullptr) {
            os << item;
        }
    }

    Menu::Menu(const char* str) : title(str), counter(0) {
        for (unsigned int i = 0; i < MAX_MENU_ITEMS; ++i) {
            items[i] = nullptr;
        }
    }

    Menu::~Menu() {
        for (int i = 0; i < counter; ++i) {
            delete items[i];
        }
    }

    Menu& Menu::operator<<(const char* menuItemContent) {

        if (unsigned(counter) < MAX_MENU_ITEMS) {
            items[counter++] = new MenuItem(menuItemContent);
        }

        return *this;
    }



    void Menu::displayTitle(std::ostream& os) const {

        if ((const char*)title != nullptr) {
            os << (const char*)title;
        }
    }



    void Menu::display(ostream& os) const {

        if ((const char*)title != nullptr) {
            displayTitle(os);
            os << "\n";
            for (int i = 0; i < counter; ++i) {
                os << setw(2) << i + 1 << "- " << (const char*)*items[i] << "\n";
            }

            if (counter > 0) {
                os << " 0- Exit\n";
            }
            os << "> ";
        }

        else if (counter > 0) {
            for (int i = 0; i < counter; ++i) {
                os << setw(2) << i + 1 << "- " << (const char*)*items[i] << "\n";
            }
            os << " 0- Exit\n";
            os << "> ";
        }

    }


    Menu::operator bool() const {
        return counter > 0;
    }

    Menu::operator int() const {
        return counter;

    }
    Menu::operator unsigned int() const {
        return counter;
    }

    ostream& operator<<(ostream& os, const Menu& menu) {
        menu.displayTitle(os);
        return os;
    }



    const char* Menu::operator[](int index) const {

        return (const char*)*items[index % counter];
    }


    unsigned int Menu::run() {

        display(cout);
        unsigned int selection = 0;

        while (true) {
            cin >> selection;
            if (cin.fail() || selection > unsigned(counter)) {
                cin.clear();
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Selection, try again: ";
            }
            else {
                break;
            }
        }

        return selection;
    }

    unsigned int Menu::operator~() {
        return run();
    }

}





