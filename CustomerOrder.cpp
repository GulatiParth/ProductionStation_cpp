// Name: Parth Gulati
// Seneca Student ID: 131697211
// Seneca email: pgulati9@myseneca.ca
// Date of completion: July 3,2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<string>
#include<iostream>
#include<iomanip>
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"

using namespace std;
using namespace sdds;

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder()
{
    m_name = "";
    m_product = "";
    m_cntItem = 0;
    m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(const string& str)
{
    m_cntItem = 0;
    m_lstItem = nullptr;

    Utilities util;
    bool more = true;
    size_t pos = 0u;

    m_name = util.extractToken(str, pos, more);
    m_product = util.extractToken(str, pos, more);

    size_t itemsStart = pos;
    while (more) {
        util.extractToken(str, pos, more);
        m_cntItem++;
    }

    m_lstItem = new Item * [m_cntItem];
    more = true;
    pos = itemsStart;

    size_t count = 0;
    while (more) {
        m_lstItem[count++] = new Item(util.extractToken(str, pos, more));
    }

    size_t util_width_field = util.getFieldWidth();

    if (util_width_field > m_widthField)
    {
        m_widthField = util_width_field;
    }

}

CustomerOrder::CustomerOrder(const CustomerOrder&) 
{
    throw "Copy constructor called";
}

CustomerOrder::~CustomerOrder() 
{
    if (m_lstItem != nullptr) 
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
{
    m_name = src.m_name;
    m_product = src.m_product;
    m_cntItem = src.m_cntItem;
    m_lstItem = src.m_lstItem;
    src.m_lstItem = nullptr;
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
{
    if (m_lstItem != nullptr)
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    m_name = src.m_name;
    m_product = src.m_product;
    m_cntItem = src.m_cntItem;
    m_lstItem = src.m_lstItem;

    src.m_name = "";
    src.m_product = "";
    src.m_cntItem = 0u;
    src.m_lstItem = nullptr;

    return *this;
}
bool CustomerOrder::isOrderFilled() const 
{
    for (size_t i = 0; i < m_cntItem; i++) 
    {
        if (!m_lstItem[i]->m_isFilled)
        {
            return false;
        }
    }
    return true;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const
{
    for (size_t i = 0; i < m_cntItem; i++) 
    {
        if (m_lstItem[i]->m_itemName == itemName && !(m_lstItem[i]->m_isFilled))
        {
            return false;
        }
    }
    return true;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os) 
{
    for (size_t i = 0; i < m_cntItem; i++)
    {
        if (station.getItemName() == m_lstItem[i]->m_itemName && !(m_lstItem[i]->m_isFilled)) 
        {
            if (station.getQuantity())
            {
                station.updateQuantity();

                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;

                os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;

                break;
            }
            else
            {
                os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
        }
    }
}

void CustomerOrder::display(std::ostream& os) const 
{
    os << m_name << " - " << m_product << endl;

    for (size_t i = 0; i < m_cntItem; i++) 
    {
        os << "[" << setfill('0') << right << setw(6) << m_lstItem[i]->m_serialNumber << "] ";
        os << left << setfill(' ') << setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";

        if (m_lstItem[i]->m_isFilled)
        {
            os << "FILLED";
        }
        else
        {
            os << "TO BE FILLED";
        }
        os << endl;
    }
}