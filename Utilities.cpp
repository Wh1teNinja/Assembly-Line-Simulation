#include <sstream>
#include "Utilities.h"

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t newWidth) {
  m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const {
  return m_widthField;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
  std::string token;

  std::stringstream str_strm(str);
  str_strm.seekg(next_pos);
  std::getline(str_strm, token, m_delimiter);

  if (token == "") {
    more = false;
    throw std::invalid_argument("Empty token!");
  }
  else {
    next_pos += token.length() + 1;
    more = true;
  }

  if (token.length() > m_widthField)
    m_widthField = token.length();

  return token;
}

void Utilities::setDelimiter(char newDelimiter) {
  m_delimiter = newDelimiter;
}

char Utilities::getDelimiter() {
  return m_delimiter;
}
