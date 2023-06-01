// Name: Parth Gulati
// Seneca Student ID: 131697211
// Seneca email: pgulati9@myseneca.ca
// Date of completion: July 3,2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef WORKSTATION_H
#define WORKSTATION_H

#include<fstream>
#include<string>
#include<deque>
#include "CustomerOrder.h"
#include "Station.h"

using namespace std;

extern deque<sdds::CustomerOrder> g_pending, g_completed, g_incomplete;

namespace sdds
{
    class Workstation : public Station 
    {
        deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation;

    public:
        Workstation(const string& str) : Station(str) {}

        Workstation(const Workstation&) = delete;
        Workstation& operator=(Workstation const&) = delete;

        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;

        void fill(ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}

#endif