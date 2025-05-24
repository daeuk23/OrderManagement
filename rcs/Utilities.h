#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
namespace order {
	class Utilities {
		size_t m_widthField{ 1 };
		static char m_delimiter; //share the same delimiter. so either static string or static char
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}
#endif