//*****************************************************************************
//  <assessment name example : Workshop - #3 (Part - 1)>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//	Email       : syang153@myseneca.ca
//	Section     : OOP345 NDD
//	Date        : May 27th, 2024
//	Authenticity Declaration :
//  I have done all the coding by myself and only copied the code 
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#include <iostream>
#include <iomanip>
#include "Book.h"

namespace seneca {
  Book::Book() : m_title(""), m_numChapters(0), m_numPages(0) {}
  Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
   : m_title(title), m_numChapters(nChapters), m_numPages(nPages) {}
  Book::operator bool() const {
    return !m_title.empty() && m_numChapters > 0 && m_numPages > 0;
  }
  std::ostream& Book::print(std::ostream& os) const {
    if (*this) {
      os << std::right << std::setw(56)
         << m_title + "," + std::to_string(m_numChapters) + "," + std::to_string(m_numPages)
         << " | " << std::left << std::setw(15)
         << "(" + std::to_string((double)m_numPages / (double)m_numChapters) + ")";
    } else {
      os << "| Invalid book data";
    }
    return os;
  }
  std::ostream& operator<<(std::ostream& os, const Book& bk) {
    return bk.print(os);
  }
}