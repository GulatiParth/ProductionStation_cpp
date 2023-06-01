// Name: Parth Gulati
// Seneca Student ID: 131697211
// Seneca email: pgulati9@myseneca.ca
// Date of completion: July 3,2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef CUSTOMER_ORDERS_H
#define CUSTOMER_ORDERS_H

#include<string>
#include "Station.h"

using namespace std;

namespace sdds 
{
    class CustomerOrder 
    {
        struct Item 
        {
            string m_itemName;
            size_t m_serialNumber{ 0 };
            bool m_isFilled{ false };

            Item(const std::string& src) : m_itemName(src) {};
        };

        string m_name, m_product;
        size_t m_cntItem;
        Item** m_lstItem;

        static size_t m_widthField;

    public:
        CustomerOrder();
        CustomerOrder(const string& str);

        CustomerOrder(const CustomerOrder&);
        CustomerOrder& operator=(const CustomerOrder&) = delete;

        ~CustomerOrder();

        CustomerOrder(CustomerOrder&&) noexcept;
        CustomerOrder& operator=(CustomerOrder&&) noexcept;

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif