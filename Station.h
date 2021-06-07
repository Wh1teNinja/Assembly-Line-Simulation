#pragma once
#ifndef SDDS_STATION_H__
#define SDDS_STATION_H__
#include <string>

class Station {
  size_t m_id;
  std::string m_name;
  std::string m_desc;
  size_t m_serialNumber;
  size_t m_quantity;
  static size_t m_widthField;
  static size_t id_generator;
public:
  Station(const std::string& str);

  const std::string& getItemName() const;
  unsigned int getNextSerialNumber();
  unsigned int getQuantity() const;
  void updateQuantity();
  void display(std::ostream& os, bool full) const;
};

#endif