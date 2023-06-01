// Name: Parth Gulati
// Date of completion: July 3,2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H

#include<fstream>
#include<string>

using namespace std;

namespace sdds 
{
    class Station 
    {
        string name;
        string description;
        size_t id;
        size_t  next_serial_no;
        size_t  quantity;

        static size_t m_widthField;
        static size_t id_generator;

    public:
        Station();
        Station(const string& str);

        const string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(ostream& os, bool full) const;

        string trimString(string str);
    };
}

#endif