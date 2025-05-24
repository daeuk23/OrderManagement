#include <algorithm>
#include "Workstation.h"
#include "Utilities.h"

using namespace std;
namespace order {
    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            //filling items from deque list -> to os
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        bool isMoved = false;
        if (!m_orders.empty()) {
            //order will be moved
            if (m_orders.front().isItemFilled(getItemName()) || getQuantity() < 1) {
                //if there is next station in the assembly line
                if (m_pNextStation != nullptr) {
                    *m_pNextStation += std::move(m_orders.front());
                    m_orders.pop_front();
                }

                else {
                    //condition order filled
                    if (!m_orders.front().isOrderFilled()) {
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                    else { 
                        g_completed.push_back(std::move(m_orders.front()));         
                    }
                    m_orders.pop_front();
                }
                isMoved = true;
            }
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

    void Workstation::display(std::ostream& os) const {
        os << getItemName();
        if (m_pNextStation != nullptr) {
            // Station::getItemName
            os << " --> " << m_pNextStation->getItemName();
        }
        else {
            os << " --> End of Line";
        }
        os << '\n';
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        // add element back
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}