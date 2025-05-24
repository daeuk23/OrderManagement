#include "Utilities.h"
using namespace std;

namespace order {
	// Initialize delemeter, no need constructors so..
	char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth){
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
		string token{};
		if (more) {
			size_t delFound = str.find(m_delimiter, next_pos);

			if (delFound == next_pos) {
				more = false;
				// error reporting
				throw string("Err. Delemeter found at next_pos");
			}

			else if (delFound != string::npos) {
				more = true;
				//extraction token
				token = str.substr(next_pos, delFound - next_pos);
				token = token.erase(0, token.find_first_not_of(" "));
				token = token.erase(token.find_last_not_of(" ") + 1);
				next_pos = delFound + 1;
			}
			else {
				more = false;
				// for last string (after delimiter)
				token = str.substr(next_pos);
				token = token.erase(0, token.find_first_not_of(" "));
				token = token.erase(token.find_last_not_of(" ") + 1);
			}

			if (token.length() > m_widthField) {
				m_widthField = token.length();
			}

		}
		
		return token;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}