#include <iostream>
#include <fstream>
#include <algorithm>
#include "Utilities.h"
#include "LineManager.h"

Workstation* LineManager::findFirst(Workstation* ws) const {
  auto prev = std::find_if(AssemblyLine.begin(), AssemblyLine.end(),
    [&ws](Workstation* prev) {
      return prev->getNextStation() == ws;
    });
  if (prev != AssemblyLine.end()) {
    prev = std::find(AssemblyLine.begin(), AssemblyLine.end(), findFirst(*prev));
  }
  else
    prev = std::find(AssemblyLine.begin(), AssemblyLine.end(), ws);
  return *prev;
}

LineManager::LineManager(const std::string& str, std::vector<Workstation*>& al, std::vector<CustomerOrder>& tbf) {
  std::for_each(tbf.begin(), tbf.end(),
    [this](CustomerOrder& ws) {
      ToBeFilled.push_back(std::move(ws));
      m_cntCustomerOrder++;
    });

  std::for_each(al.begin(), al.end(),
    [this](Workstation* ws) {
      AssemblyLine.push_back(ws);
    });

  std::ifstream file(str);
  Utilities u;
    while (file) {
      std::string record;
      size_t nextPos = 0;
      bool more = false;
      std::string current;
      std::string next = "";

      std::getline(file, record);
      current = u.extractToken(record, nextPos, more);
      try {
        next = u.extractToken(record, nextPos, more);
        (*std::find_if(AssemblyLine.begin(), AssemblyLine.end(),
          [current](Workstation* ws) {
            return ws->getItemName() == current;
          }))->setNextStation(
            **std::find_if(AssemblyLine.begin(), AssemblyLine.end(),
              [next](Workstation* ws) {
                return ws->getItemName() == next;
              }));
      }
      catch (std::invalid_argument&) {
        std::getline(file, record);
      }
    }
}

bool LineManager::run(std::ostream& os) {
  bool result = false;
  static size_t cnt = 0;
  os << "Line Manager Iteration: " << ++cnt << std::endl;

  Workstation* ws = *std::find_if(AssemblyLine.begin(), AssemblyLine.end(),
    [](Workstation* last) {
      return last->getNextStation() == nullptr;
    });
  if (!ToBeFilled.empty()) {
    findFirst(ws)->operator+=(std::move(ToBeFilled.front()));
    ToBeFilled.pop_front();
  }

  for (size_t i = 0; i < AssemblyLine.size(); i++)
    AssemblyLine[i]->runProcess(os);

  do {
    CustomerOrder temp;
    if(!ws->moveOrder())
     if (ws->getIfCompleted(temp))
      Completed.push_back(std::move(temp));
    auto wsIt = std::find_if(AssemblyLine.begin(), AssemblyLine.end(),
      [&ws](Workstation* prev) {
        return prev->getNextStation() == ws;
      });
    if (wsIt != AssemblyLine.end())
      ws = *wsIt;
    else
      ws = nullptr;
  } while (ws);
  if (!Completed.empty() && Completed.size() == m_cntCustomerOrder)
    result = true;
  return result;
}

void LineManager::displayCompletedOrders(std::ostream& os) const {
  std::for_each(Completed.begin(), Completed.end(),
    [&os](const CustomerOrder& co) {
      co.display(os);
    });
}

void LineManager::displayStations() const {
  std::for_each(AssemblyLine.begin(), AssemblyLine.end(),
    [](Workstation* ws) {
      ws->display(std::cout);
    });
}

void LineManager::displayStationsSorted() const {
  Workstation* ws = findFirst(*std::find_if(AssemblyLine.begin(), AssemblyLine.end(),
    [](Workstation* last) {
      return last->getNextStation() == nullptr;
    }));
  ws->display(std::cout);
  while (ws->getNextStation()) {
    if (ws->getNextStation())
      ws = *std::find(AssemblyLine.begin(), AssemblyLine.end(), ws->getNextStation());
    ws->display(std::cout);
  }
}
