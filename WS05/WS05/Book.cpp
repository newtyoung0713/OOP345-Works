//*****************************************************************************
//  <assessment name example : Workshop - #5 (Part - 2>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//    Email       : syang153@myseneca.ca
//    Section     : OOP345 NDD
//    Date        : June 13th, 2024
//    Authenticity Declaration :
//  I have done all the coding by myself and only copied the code
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#include "Book.h"

namespace seneca {
  Book::Book() : m_author(""), m_title(""), m_country(""), m_price(0), m_year(0), m_desc("") {}
  const std::string& Book::title() const { return m_title; }
  const std::string& Book::country() const { return m_country; }
  const size_t& Book::year() const { return m_year; }
  double& Book::price() { return m_price; }
  std::string Book::trim(std::string& d, const char sb) {
    std::string temp{}, reStr{};
    temp = d.substr(0, d.find(sb)); // Extracting chars starts from first char to SB
    auto before = temp.find_first_not_of(' ');  // Get first char which is not whitespace
    auto after = temp.find_last_not_of(' ');  // Get last char which is not whitespace
    reStr = temp.substr(before, (after - before) + 1);  // Calculating where is the string
    d.erase(0, d.find(sb) + 1); // Cleaning the string D
    return reStr;
  }
  Book::Book(const std::string& strBook) {
    std::string temp = strBook;
    m_author = trim(temp, ',');
    m_title = trim(temp, ',');
    m_country = trim(temp, ',');
    m_price = std::stod(trim(temp, ','));
    m_year = std::stoi(trim(temp, ','));
    m_desc = trim(temp, '\n');
  }
  std::ostream& Book::display(std::ostream& os) const {
    os << std::setw(20) << m_author << " | " << std::setw(22) << m_title << " | "
        << std::setw(5) << m_country << " | " << std::setw(4) << m_year << " | "
        << std::setw(6) << std::fixed << std::setprecision(2) << m_price << " | " << m_desc << std::endl;
    return os;
  }
  std::ostream& operator<<(std::ostream& os, const Book& rhs) {
    return rhs.display(os);
  }
}
