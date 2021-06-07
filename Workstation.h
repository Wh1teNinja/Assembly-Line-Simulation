#pragma once
#ifndef WORKSTATION_H__
#define WORKSTATION_H__
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

class Workstation : public Station {
  std::deque<CustomerOrder> m_orders;
  Workstation* m_pNextStation;
public:
  Workstation(const std::string&);
  Workstation(Workstation&) = delete;
  Workstation& operator=(Workstation&) = delete;
  Workstation(Workstation&&) = delete;
  Workstation& operator=(Workstation&&) = delete;

  void runProcess(std::ostream&);
  bool moveOrder();
  void setNextStation(Workstation& station);
  const Workstation* getNextStation() const;
  bool getIfCompleted(CustomerOrder& order);
  void display(std::ostream&);
  Workstation& operator+=(CustomerOrder&&);
};

#endif 