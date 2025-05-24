#include "Station.h"
using namespace std;

namespace order {
	// initialization class member
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& file) {
		Utilities utilities;

		size_t next_pos = 0;
		bool more = true; //for parameter extract token

		m_stId = ++id_generator;
		m_nextSerNum = 0; //initially 0

		m_nameItem = utilities.extractToken(file, next_pos, more);
		m_nextSerNum = stoi(utilities.extractToken(file, next_pos, more));
		m_numStock = stoi(utilities.extractToken(file, next_pos, more));

		m_widthField = max(m_widthField, utilities.getFieldWidth());
		m_desc = utilities.extractToken(file, next_pos, more);
	}

	const std::string& Station::getItemName() const {
		return m_nameItem;
	}
	size_t  Station::getNextSerialNumber() {
		return m_nextSerNum++;
	}
	size_t  Station::getQuantity() const {
		return m_numStock;
	}
	void  Station::updateQuantity() {
		if (m_numStock > 0) {
			m_numStock--;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		os << right << setw(3) << setfill('0') << m_stId << " | ";
		os << left << setw(m_widthField) << setfill(' ') << m_nameItem << " | ";
		os << right << setw(6) << setfill('0') << m_nextSerNum << " | ";
		if (full) {
			os << right << setw(4) << setfill(' ') << m_numStock << " | ";
			os << left << m_desc;
		}
		os << std::endl;
	}
}