#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <iostream>
#include <vector>
#include "Workstation.h"
namespace order {
	class LineManager
	{
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{ nullptr };

	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif