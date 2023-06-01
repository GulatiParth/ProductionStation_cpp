// Name: Parth Gulati
// Date of completion: July 3,2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<string>
#include<fstream>
#include<iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;
using namespace sdds;

size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;

Station::Station() 
{
    id = 0;
    next_serial_no = 0;
    quantity = 0;
    name = "";
    description = "";
}

Station::Station(const string& str) 
{
    Utilities util;
    bool more = true;
    size_t pos = 0u;

    id = (++id_generator);

    name = util.extractToken(str, pos, more);

    next_serial_no = stoi(util.extractToken(str, pos, more));
    quantity = stoi(util.extractToken(str, pos, more));

    size_t util_width_field = util.getFieldWidth();

    if (util_width_field > m_widthField)
    {
        m_widthField = util_width_field;
    }
    description = util.extractToken(str, pos, more);
}

const string& Station::getItemName() const 
{
    return name;
}

size_t Station::getNextSerialNumber() 
{
    size_t res = next_serial_no;
    next_serial_no++;
    return res;
}

size_t Station::getQuantity() const 
{
    return quantity;
}

void Station::updateQuantity() 
{
    //Should not drop below 0
    if (quantity)
    {
        quantity--;
    }
}

void Station::display(ostream& os, bool full) const 
{
    os << setfill('0') << setw(3) << id << " | ";

    os << left << setfill(' ') << setw(m_widthField) << name << " | ";

    os << right;

    os << setfill('0') << setw(6) << next_serial_no << " | ";

    if (full) 
    {
        os << setfill(' ') << setw(4) << quantity << " | ";
        os << description;
    }

    os << endl;
}