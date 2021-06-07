#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {}

CustomerOrder::CustomerOrder(const std::string& str) {
  size_t next_pos = 0;
  bool more = false;
  Utilities u;
  m_name = u.extractToken(str, next_pos, more);
  m_product = u.extractToken(str, next_pos, more);

  do {
    Item** temp = nullptr;
    if (m_lstItem)
      temp = m_lstItem;
    m_lstItem = new Item * [++m_cntItem];
    try {
      m_lstItem[m_cntItem - 1] = new Item(u.extractToken(str, next_pos, more));
      for (size_t i = 0; i < m_cntItem - 1; i++)
        m_lstItem[i] = temp[i];
      delete[] temp;
    }
    catch (const std::invalid_argument&) {
      delete[] m_lstItem;
      m_lstItem = temp;
      temp = nullptr;
      m_cntItem--;
    }
  } while (more);

  if (u.getFieldWidth() > m_widthField)
    m_widthField = u.getFieldWidth();
}

CustomerOrder::CustomerOrder(const CustomerOrder&) {
  throw "Copy constructor is not available for CustomerOrder!";
}

CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept
  : m_name(co.m_name),
  m_product(co.m_product),
  m_cntItem(co.m_cntItem),
  m_lstItem(co.m_lstItem)
{
  m_widthField = co.m_widthField;
  co.m_cntItem = 0;
  co.m_lstItem = nullptr;
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept {
  if (this != &co) {
    m_name = co.m_name;
    m_product = co.m_product;
    if (m_lstItem) {
      for (size_t i = 0; i < m_cntItem; i++)
        delete m_lstItem[i];
      delete[] m_lstItem;
    }
    m_cntItem = co.m_cntItem;
    m_lstItem = co.m_lstItem;
    m_widthField = co.m_widthField;

    co.m_cntItem = 0;
    co.m_lstItem = nullptr;
  }
  return *this;
}

CustomerOrder::~CustomerOrder() {
  for (size_t i = 0; i < m_cntItem; i++)
    delete m_lstItem[i];
  if (m_lstItem)
    delete[] m_lstItem;
}

bool CustomerOrder::isOrderFilled() const {
  bool result = true;
  for (size_t i = 0; i < m_cntItem && result; i++)
    result = m_lstItem[i]->m_isFilled;
  return result;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const {
  int result = -1;
  for (size_t i = 0; i < m_cntItem && result == -1; i++)
    if (m_lstItem[i]->m_itemName == itemName)
      result = m_lstItem[i]->m_isFilled;
  return result;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os) {
  for (size_t i = 0; i < m_cntItem; i++) {
    if (m_lstItem[i]->m_itemName == station.getItemName()) {
        m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
      if (station.getQuantity() > 0) {
        m_lstItem[i]->m_isFilled = true;
        station.updateQuantity();
        os << "    Filled ";
      }
      else {
        m_lstItem[i]->m_isFilled = false;
        os << "    Unable to fill ";
      }
      os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
    }
  }
}

void CustomerOrder::display(std::ostream& os) const {
  os << m_name << " - " << m_product << std::endl;
  for (size_t i = 0; i < m_cntItem; i++) {
    std::string status = m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING";
    os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber
      << "] " << std::left << std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName
      << " - " << status << std::endl;

  }
}
