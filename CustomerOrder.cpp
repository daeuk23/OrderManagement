#include <iomanip>
#include <vector>
#include <algorithm>
#include "CustomerOrder.h"
using namespace std;

namespace order {
	size_t CustomerOrder::m_widthField = 0; //initialization class var

	CustomerOrder::CustomerOrder(const std::string& string) {
        try {
            Utilities util;
            bool more = true;// for parameter bool value
            std::vector<std::string> itemList;
            size_t next_pos = 0u;

            m_name = util.extractToken(string, next_pos, more);
            m_product = util.extractToken(string, next_pos, more);

            while (more) {
                itemList.push_back(util.extractToken(string, next_pos, more));
            }
            m_cntItem = itemList.size();
            m_lstItem = new Item * [m_cntItem];

            for (size_t item = 0; item < this->m_cntItem; ++item) {
                m_lstItem[item] = new Item(itemList[item]);
            }

            m_widthField = max(m_widthField, util.getFieldWidth());
        }
        catch (...) {
            throw ("Error while creating object");
        }
	}

    CustomerOrder::CustomerOrder(const CustomerOrder& src)
    {
        throw ("Error: couldn't handle copy constructor");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
    {
        *this = std::move(src);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
    {
        if (this != &src) {
            deallocate();
            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            // setting after move ownership
            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder()
    {
        deallocate();
    }

    void CustomerOrder::deallocate() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }

    bool CustomerOrder::isOrderFilled() const
    {
        // list item to (item number) iteration
        return std::all_of(m_lstItem, m_lstItem + m_cntItem, [](const Item* list) { return list->m_isFilled; });
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const
    {
        return std::all_of(m_lstItem, m_lstItem + m_cntItem, [&](const Item* list) {
            // if the item doesn't exist in the order => true, iteration lstItem to (number of cntItem)
            return (list->m_itemName == itemName) ? list->m_isFilled : true;
            });
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();

                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;

                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
                    break;
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << endl;

        for (size_t itemIdex = 0; itemIdex < m_cntItem; ++itemIdex)
        {
            os << setfill('0') << "[" << right << setw(6) << m_lstItem[itemIdex]->m_serialNumber << "] ";
            os << setfill(' ') << left << setw(m_widthField);
            os << m_lstItem[itemIdex]->m_itemName << " - ";
            m_lstItem[itemIdex]->m_isFilled ? os << "FILLED" : os << "TO BE FILLED";

            os << std::endl;
        }
    }
}