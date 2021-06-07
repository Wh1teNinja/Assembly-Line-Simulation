#pragma once
#ifndef CUSTOMERORDER_H__
#define CUSTOMERORDER_H__
#include <string>
#include "Station.h"

struct Item
{
  std::string m_itemName;
  unsigned int m_serialNumber = 0;
  bool m_isFilled = false;

  Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
  std::string m_name{ "" };
  std::string m_product{ "" };
  unsigned int m_cntItem = 0;
  Item** m_lstItem = nullptr;
  static size_t m_widthField;
public:
  CustomerOrder();
  CustomerOrder(const std::string& str);
  CustomerOrder(const CustomerOrder&);
  CustomerOrder& operator=(const CustomerOrder&) = delete;
  CustomerOrder(CustomerOrder&&) noexcept;
  CustomerOrder& operator=(CustomerOrder&&) noexcept;
  ~CustomerOrder();

  bool isOrderFilled() const;
  bool isItemFilled(const std::string& itemName) const;
  void fillItem(Station& station, std::ostream& os);
  void display(std::ostream& os) const;
};

#endif