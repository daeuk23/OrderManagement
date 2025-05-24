#include <string>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;
namespace order {
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		Utilities util;
		Utilities::setDelimiter('|');
		string line;
		ifstream fileData(file);
		if (!fileData) {
			throw string("Unable to open [") + file + "] file.";
		}

		else {
			while (getline(fileData, line)) {
				bool more = true;
				size_t idx = 0;
				//ext tokens
				string fStation = util.extractToken(line, idx, more);
				string nStation = util.extractToken(line, idx, more);
				// return token but set more =>bool
				auto fWork = find_if(stations.begin(), stations.end(), [&](const Workstation* w) {
					return w->getItemName() == fStation;
					});
				auto nWork = find_if(stations.begin(), stations.end(), [&](const Workstation* w) {
					return w->getItemName() == nStation;
					});

				if (fWork != stations.end() && nWork != stations.end()) {
					(*fWork)->setNextStation(*nWork);
				}
				// if bool not false
				if (fWork != stations.end()) {
					m_activeLine.push_back(*fWork);
				}
			}
			// set first station by reference
			auto firstW = std::find_if(stations.begin(), stations.end(), [&](const Workstation* fW) {
				return std::none_of(m_activeLine.begin(), m_activeLine.end(),
	            [&](const Workstation* nW) { 
						return fW == nW->getNextStation();
				});
			});

			//first workst cant be end of the station
			if (firstW != stations.end()) {
				m_firstStation = *firstW;
			}
		}
		fileData.close();
		m_cntCustomerOrder = g_pending.size();
	}

	void LineManager::reorderStations() {
		vector<Workstation*> newOrder;
		Workstation* firstStation = m_firstStation;

		//starting from idx1
		newOrder.push_back(firstStation);
		while (newOrder.size() != m_activeLine.size()) {
			firstStation = firstStation->getNextStation();
			newOrder.push_back(firstStation);
		}
		m_activeLine = move(newOrder);
	}

	bool LineManager::run(std::ostream& os){
		static size_t count = 0;
		os << "Line Manager Iteration: " << ++count << std::endl;

		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* w) {
			w->fill(os);
		});
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* w) {
			w->attemptToMoveOrder();
		});

		return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
	}

	void LineManager::display(std::ostream& os) const {
		for (auto& workstation : m_activeLine) {
			workstation->display(os);
		}
	}
}