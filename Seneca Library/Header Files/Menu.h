//Name: Arashdeep Singh
//Student_Id: 165871229
//Email: asarashdeep-singh@myseneca.ca

#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__


using namespace std;
namespace sdds {
    const unsigned int MAX_MENU_ITEMS = 20;

    class Menu;
    class MenuItem {
    private:
        friend class Menu;
        char* item;
        MenuItem(const char* str = nullptr);
        MenuItem(const MenuItem& menu) = delete;
        MenuItem& operator=(const MenuItem& menu) = delete;
        ~MenuItem();
        operator bool() const;
        operator const char* () const;
        void display(ostream& os) const;

    };

    class Menu {
    private:
        MenuItem title;
        MenuItem* items[MAX_MENU_ITEMS];
        int counter;

    public:
        Menu(const char* str = nullptr);
        Menu(const Menu& menu) = delete;
        Menu& operator=(const Menu& menu) = delete;
        ~Menu();

        void displayTitle(ostream& os) const;
        void display(ostream& os) const;
        unsigned int run() const;

        Menu& operator<<(const char* menuitemContent);
        operator int() const;
        operator unsigned int() const;
        operator bool() const;

        friend ostream& operator<<(ostream& os, const Menu& menu);
        const char* operator[](int index) const;

        unsigned int run();
        unsigned int operator~();
    };
}



#endif // SDDS_MENU_H__