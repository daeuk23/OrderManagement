#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include "Utilities.h"
#include "Station.h"
#include <string>
#include <iostream>

namespace order {
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };
		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder
	{
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;
	public:
		CustomerOrder() = default;
		CustomerOrder(const std::string& string);

		CustomerOrder(const CustomerOrder& cusOr); //(implemented to error handling)
		CustomerOrder& operator=(const CustomerOrder& cusOr) = delete;

		CustomerOrder(CustomerOrder&& cusOr) noexcept;
		CustomerOrder& operator=(CustomerOrder&& cusOr) noexcept;

		~CustomerOrder(); 
		void deallocate(); //deallocating arrays
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif