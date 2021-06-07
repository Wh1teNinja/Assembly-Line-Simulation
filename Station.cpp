#include <iomanip>
#include "Station.h"
#include "Utilities.h"

size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;

Station::Station(const std::string& str) {
  size_t next_pos = 0;
  bool more = false;
  Utilities u;
  m_name = u.extractToken(str, next_pos, more);
  m_serialNumber = std::stoi(u.extractToken(str, next_pos, more));
  m_quantity = std::stoi(u.extractToken(str, next_pos, more));

  if (u.getFieldWidth() > m_widthField)
    m_widthField = u.getFieldWidth();

  m_desc = u.extractToken(str, next_pos, more);

  m_id = ++id_generator;
}

const std::string& Station::getItemName() const {
  return m_name;
}

unsigned int Station::getNextSerialNumber() {
  return m_serialNumber++;
}

unsigned int Station::getQuantity() const {
  return m_quantity;
}

void Station::updateQuantity() {
  if (m_quantity)
    m_quantity--;
}

void Station::display(std::ostream& os, bool full) const {
  if (full) {
    os << "[" << std::setw(3) << std::right << std::setfill('0') << m_id << "]"
      << std::setfill(' ') << " Item: " << std::setw(m_widthField) << std::left << m_name
      << " [" << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << std::setfill(' ') << "]"
      << " Quantity: " << std::setw(m_widthField) << std::left << m_quantity
      << " Description: " << m_desc;
  }
  else {
    os << "[" << std::setw(3) << std::right << std::setfill('0') << m_id << "]"
      << std::setfill(' ') << " Item: " << std::setw(m_widthField) << std::left << m_name
      << " [" << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << std::setfill(' ') << "]";
  }
  os << std::endl;
}
