// Name: Parth Gulati
// Seneca Student ID: 131697211
// Seneca email: pgulati9@myseneca.ca
// Date of completion: July 3,2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<string>
#include<fstream>
#include<vector>
#include<unordered_set>
#include<algorithm>
#include "LineManager.h"
#include "Workstation.h"

using namespace std;
using namespace sdds;

LineManager::LineManager(const string& filename, const vector<Workstation*>& stations)
{
    ifstream in(filename);

    if (!in.is_open())
    {
        throw "Unable to open file" + filename;
    }

    unordered_set<string> stationNames, alreadyInserted;

    string line;
    try {
        while (getline(in, line)) {
            const size_t length = line.length();

            string station_name, next_station_name;
            station_name = next_station_name = "";

            size_t pos = line.find('|');
            if (pos == string::npos)
            {
                pos = length;
            }

            station_name = line.substr(0, pos);

            if (!station_name.length())
            {
                continue;
            }

            if (pos != length)
            {
                next_station_name = line.substr(pos + 1);
            }

            Workstation* curr, * next;
            curr = next = nullptr;

            curr = *find_if(stations.begin(), stations.end(), [&](Workstation* station) -> bool {
                return (station->getItemName()) == station_name;
                });

            if (next_station_name.length()) {
                next = *find_if(stations.begin(), stations.end(), [&](Workstation* station) -> bool {
                    return (station->getItemName()) == next_station_name;
                    });
            }

            curr->setNextStation(next);
            m_activeLine.push_back(curr);

            //To Find the First Station
            stationNames.insert(station_name);

            if (next_station_name != "")
            {
                alreadyInserted.insert(next_station_name);
            }

            if (alreadyInserted.find(station_name) != alreadyInserted.end() && stationNames.find(station_name) != stationNames.end())
            {
                stationNames.erase(stationNames.find(station_name));
            }

            if (alreadyInserted.find(next_station_name) != alreadyInserted.end() && stationNames.find(next_station_name) != stationNames.end())
            {
                stationNames.erase(stationNames.find(next_station_name));
            }
        }
        in.close();

        //There will be always be one parent since it will
        //be not removed from the set
        string first_station_name = *stationNames.begin();
        m_firstStation = *find_if(stations.begin(), stations.end(), [&](Workstation* station) -> bool {
            return (station->getItemName()) == first_station_name;
            });

        m_cntCustomerOrder = g_pending.size();
    }
    catch (const string& err) {
        throw err;
    }
}

void LineManager::reorderStations() 
{
    vector<Workstation*> temp;
    temp.reserve(m_activeLine.size());

    Workstation* curr = m_firstStation;

    while (curr != nullptr) {
        temp.push_back(curr);
        curr = curr->getNextStation();
    }

    m_activeLine.clear();
    m_activeLine.assign(temp.begin(), temp.end());
}

bool LineManager::run(ostream& os) 
{
    static size_t count = 0;

    os << "Line Manager Iteration: " << ++count << endl;

    if (g_pending.size()) 
    {
        (*m_firstStation) += std::move(g_pending.front());
        g_pending.pop_front();
    }

    for (Workstation* workstation : m_activeLine)
    {
        workstation->fill(os);
    }

    bool isStillProcessing = true;
    for (Workstation* workstation : m_activeLine)
    {
        isStillProcessing |= workstation->attemptToMoveOrder();
    }

    //Return true if all customer orders have been filled or cannot be filled
    return (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder);
}

void LineManager::display(ostream& os) const 
{
    for (Workstation* workstation : m_activeLine)
    {
        workstation->display(os);
    }
}