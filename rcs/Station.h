#ifndef STATION_H
#define STATION_H
#include <iomanip> //for display
#include <string>
#include <iostream>
#include "Utilities.h"
namespace order {
	class Station {
		int m_stId{};
		std::string m_nameItem{};
		std::string m_desc{};
		size_t m_nextSerNum{};
		size_t m_numStock{};
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string& file);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif