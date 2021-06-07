#include <iostream>
#include "Workstation.h"

Workstation::Workstation(const std::string& str) : Station(str) {
  m_pNextStation = nullptr;
}

void Workstation::runProcess(std::ostream& os) {
  if (!m_orders.empty())
    m_orders.front().fillItem(*this, os);
}

bool Workstation::moveOrder() {
  bool result = false;
  if (!m_orders.empty() && m_pNextStation && m_orders.front().isItemFilled(getItemName())) {
    *m_pNextStation += std::move(m_orders.front());
    m_orders.pop_front();
    result = true;
  }
  return result;
}

void Workstation::setNextStation(Workstation& station) {
  m_pNextStation = &station;
}

const Workstation* Workstation::getNextStation() const {
  return m_pNextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order) {
  bool result = false;
  if (!m_orders.empty() && m_orders.front().isOrderFilled()) {
    order = std::move(m_orders.front());
    m_orders.pop_front();
    result = true;
  }
  return result;
}

void Workstation::display(std::ostream& os) {
  if (m_pNextStation)
    os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
  else
    os << getItemName() << " --> END OF LINE" << std::endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& co) {
  m_orders.push_back(std::move(co));
  return *this;
}
