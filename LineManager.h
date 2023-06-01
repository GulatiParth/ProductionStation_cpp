// Name: Parth Gulati
// Seneca Student ID: 131697211
// Seneca email: pgulati9@myseneca.ca
// Date of completion: July 3,2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINE_MANAGER_H
#define LINE_MANAGER_H

#include<fstream>
#include<string>
#include<vector>
#include "Workstation.h"

using namespace std;

namespace sdds 
{
    class LineManager 
    {
        vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder;
        Workstation* m_firstStation;

    public:
        LineManager(const string& file, const vector<Workstation*>& stations);
        void reorderStations();
        bool run(ostream& os);
        void display(ostream& os) const;
    };
}

#endif