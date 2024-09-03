#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <iostream>
#include <iomanip>
#include <string>
#include "SpellChecker.h"

namespace seneca {
  class Book {
    std::string m_author{};
    std::string m_title{};
    std::string m_country{};
    double m_price{0};
    size_t m_year{0};
    std::string m_desc{};
    std::string trim(std::string& d, const char sb);
  public:
    Book();
    const std::string& title() const;
    const std::string& country() const;
    const size_t& year() const;
    double& price();
    Book(const std::string& strBook);
    std::ostream& display(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Book& rhs);
    template<typename T>
    void fixSpelling(T& spellChecker) {
      spellChecker(m_desc);
    }
  };
}
#endif  // !SENECA_BOOK_H
