// Name: Parth Gulati
// Seneca Student ID: 131697211
// Seneca email: pgulati9@myseneca.ca
// Date of completion: July 3,2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

using namespace std;

namespace sdds 
{
    class Utilities 
    {
        size_t m_widthField;
        static char m_delimiter;

    public:
        Utilities();

        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        string extractToken(const string& str, size_t& next_pos, bool& more);

        static void setDelimiter(char newDelimiter);
        static char getDelimiter();

        string trimString(string str);
    };
}

#endif