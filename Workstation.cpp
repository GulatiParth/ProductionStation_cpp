// Name: Parth Gulati
// Seneca Student ID: 131697211
// Seneca email: pgulati9@myseneca.ca
// Date of completion: July 3,2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<string>
#include<fstream>
#include<iostream>
#include "Workstation.h"
#include "CustomerOrder.h"

using namespace sdds;

deque<CustomerOrder> g_pending, g_completed, g_incomplete;

void Workstation::fill(ostream& os) 
{
    if (!m_orders.empty())
    {
        m_orders.front().fillItem(*this, os);
    }
}

bool Workstation::attemptToMoveOrder() 
{
    if (m_orders.empty())
    {
        return false;
    }

    const string& itemName = getItemName();
    CustomerOrder& order = m_orders.front();

    bool isMoved = true;

    //If the order requires no more service at this station OR 
    //cannot be filled (not enough inventory), move it to the next station
    if (order.isItemFilled(itemName) || !getQuantity()) 
    {
        if (m_pNextStation != nullptr)
        {
            (*m_pNextStation) += std::move(order);
        }
        else 
        {
            if (order.isOrderFilled())
            {
                g_completed.push_back(std::move(order));
            }
            else
            {
                g_incomplete.push_back(std::move(order));
            }
            isMoved = false;
        }
        m_orders.pop_front();
    }
    else                     //Otherwise do nothing
    {
        isMoved = false;
    }
    return isMoved;
}

void Workstation::setNextStation(Workstation* station = nullptr) 
{
    m_pNextStation = station;
}

Workstation* Workstation::getNextStation() const 
{
    return m_pNextStation;
}

void Workstation::display(std::ostream& os) const 
{
    os << getItemName() << " --> ";

    if (m_pNextStation == nullptr)
    {
        os << "End of Line";
    }
    else
    {
        os << m_pNextStation->getItemName();
    }
    os << "\n";
}

Workstation& Workstation::operator+=(CustomerOrder&& newOrder) 
{
    m_orders.push_back(std::move(newOrder));
    return *this;
}