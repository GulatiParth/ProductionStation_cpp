// Name: Parth Gulati
// Date of completion: July 3,2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<string>
#include<iostream>
#include "Utilities.h"

using namespace std;
using namespace sdds;

char Utilities::m_delimiter = ' ';      //Initializing static member

Utilities::Utilities()
{
    m_widthField = 1;
}

void Utilities::setFieldWidth(size_t newWidth)
{
    m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const
{
    return m_widthField;
}

string Utilities::trimString(string str)
{
    string buffer = "";
    int start = 0, end = str.length() - 1;

    while (str[start] == ' ') {
        ++start;
    }

    while (str[end] == ' ') {
        --end;
    }

    for (int i = start; i <= end; i++)
    {
        buffer += str[i];
    }

    return buffer;
}


string Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
{
    const size_t n = str.length();

    //reports an exception if a delimiter is found at next_pos
    if (str[next_pos] == m_delimiter)
    {
        more = false;
        throw std::string("Error: Delimiter is found at next_pos");
    }

    //Find the position of delimiter
    size_t pos = str.find(m_delimiter, next_pos);
    if (pos == string::npos)
    {
        pos = n;
    }

    string res = "";

    if (more)       // successful, return a copy of the extracted token found
    {
        res = str.substr(next_pos, pos - next_pos);
        next_pos = pos + 1;

        if (m_widthField < res.length())
        {
            m_widthField = res.length();
        }
    }

    more = !(pos == n); // if pos == n ==> more = 0 Otherwise more = 1 

    return trimString(res);
}

void Utilities::setDelimiter(char newDelimiter)
{
    m_delimiter = newDelimiter;
}

char Utilities::getDelimiter()
{
    return m_delimiter;
}
