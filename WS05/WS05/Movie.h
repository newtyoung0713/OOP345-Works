#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include <iostream>
#include <iomanip>
#include <string>

namespace seneca {
  class Movie {
    std::string m_title{};
    size_t m_year{0};
    std::string m_desc{};
    std::string trim(std::string& d, const char sb);
  public:
    Movie();
    const std::string& title() const;
    Movie(const std::string& strMovie);
    std::ostream& display(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Movie& rhs);
    
    template<typename T>
    void fixSpelling(T& spellChecker) {
      spellChecker(m_title);
      spellChecker(m_desc);
    }
  };
}
#endif  // !SENECA_MOVIE_H
