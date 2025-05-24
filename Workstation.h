#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <iostream>
#include <deque>
#include "CustomerOrder.h"

namespace order {
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;
	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};
	public:
		// object cannot be copied or moved
		Workstation(const Workstation& workstation) = delete;
		Workstation& operator=(const Workstation& workstation) = delete;
		Workstation(Workstation&& workstation) = delete;
		Workstation& operator=(Workstation&& workstation) = delete;

		//constructor destructor
		Workstation(const std::string& workstation) :Station(workstation), m_pNextStation(nullptr) {};
		~Workstation() {};

		//functions
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif