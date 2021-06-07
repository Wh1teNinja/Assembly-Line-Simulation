#pragma once
#ifndef LINEMANAGER_H__
#define LINEMANAGER_H__
#include <vector>
#include "Workstation.h"

class LineManager {
  std::vector<Workstation*> AssemblyLine;
  std::deque<CustomerOrder> ToBeFilled;
  std::deque<CustomerOrder> Completed;
  unsigned int m_cntCustomerOrder = 0;

  Workstation* findFirst(Workstation*) const;
public:
  LineManager(const std::string&, std::vector<Workstation*>&, std::vector<CustomerOrder>&);

  bool run(std::ostream& os);
  void displayCompletedOrders(std::ostream& os) const;
  void displayStations() const;
  void displayStationsSorted() const;
};

#endif