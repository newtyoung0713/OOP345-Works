//*****************************************************************************
//  <assessment name example : Workshop - #5 (Part - 2>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//    Email       : syang153@myseneca.ca
//    Section     : OOP345 NDD
//    Date        : June 02nd, 2024
//    Authenticity Declaration :
//  I have done all the coding by myself and only copied the code
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#include "Movie.h"

namespace seneca {
  Movie::Movie() : m_title(""), m_year(0), m_desc("") {}
  const std::string& Movie::title() const { return m_title; }
  std::string Movie::trim(std::string& d, const char sb) {
    std::string temp{}, reStr{};
    temp = d.substr(0, d.find(sb)); // Extracting chars starts from first char to SB
    auto before = temp.find_first_not_of(' ');  // Get first char which is not whitespace
    auto after = temp.find_last_not_of(' ');  // Get last char which is not whitespace
    reStr = temp.substr(before, (after - before) + 1);  // Calculating where is the string
    d.erase(0, d.find(sb) + 1); // Cleaning the string D
    return reStr;
  }
  Movie::Movie(const std::string& strMovie) : m_title(""), m_year(0), m_desc("") {
    std::string temp{strMovie};
    m_title = trim(temp, ',');
    m_year = std::stoi(trim(temp, ','));
    m_desc = trim(temp, '\n');
  }
  std::ostream& Movie::display(std::ostream& os) const {
    os << std::setw(40) << m_title << " | "
       << std::setw(4) << m_year << " | "
       << m_desc << std::endl;
    return os;
  }
  std::ostream& operator<<(std::ostream& os, const Movie& rhs) {
    return rhs.display(os);
  }
}