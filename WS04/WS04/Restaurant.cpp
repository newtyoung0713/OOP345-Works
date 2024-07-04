//*****************************************************************************
//  <assessment name example : Workshop - #4 (Part - 2>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//    Email       : syang153@myseneca.ca
//    Section     : OOP345 NDD
//    Date        : June 02nd, 2024
//    Authenticity Declaration :
//  I have done all the coding by myself and only copied the code
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#include "Restaurant.h"

namespace seneca {
  size_t Restaurant::m_numReserve{0};

  void Restaurant::setEmpty() {
    if (m_cnt > 0) {
      for (size_t i = 0; i < m_cnt; i++) {
        if (m_reserve[i] != nullptr) {
          delete m_reserve[i];
          m_reserve[i] = nullptr;
        }
      }
    }
    m_cnt = 0;
    if (m_reserve != nullptr) {
      delete[] m_reserve;
      m_reserve = nullptr;
    }
  }

  Restaurant::Restaurant() : m_reserve(nullptr), m_cnt(0) {}

  Restaurant::Restaurant(const Reservation* reservations[], size_t cnt) : m_cnt(cnt) {
    m_reserve = new const Reservation*[m_cnt];
    for (size_t i = 0; i < m_cnt; ++i) m_reserve[i] = new const Reservation(*reservations[i]);
  }

  Restaurant::Restaurant(const Restaurant& uneAutre) : m_cnt(uneAutre.m_cnt) {
    m_reserve = new const Reservation*[m_cnt];
    for (size_t i = 0; i < m_cnt; ++i) m_reserve[i] = new const Reservation(*uneAutre.m_reserve[i]);
  }

  Restaurant& Restaurant::operator=(const Restaurant& uneAutre) {
    if (this != &uneAutre) {
      setEmpty();

      m_cnt = uneAutre.m_cnt;
      m_reserve = new const Reservation*[m_cnt];
      for (size_t i = 0; i < m_cnt; ++i) m_reserve[i] = new const Reservation(*uneAutre.m_reserve[i]);
    }
    return *this;
  }

  Restaurant::Restaurant(Restaurant&& uneAutre) noexcept : m_reserve(nullptr), m_cnt(0) {
    *this = std::move(uneAutre);
  }

  Restaurant& Restaurant::operator=(Restaurant&& uneAutre) noexcept {
    if (this != &uneAutre) {
      setEmpty();
      m_reserve = uneAutre.m_reserve;
      uneAutre.m_reserve = nullptr;
      m_cnt = uneAutre.m_cnt;
      uneAutre.m_cnt = 0;
    }
    return *this;
  }

  Restaurant::~Restaurant() {
    setEmpty();
  }
  
  size_t Restaurant::size() const {
    return m_numReserve;
  }
  
  std::ostream& Restaurant::display(std::ostream& os) const {
    m_numReserve++;
    os << std::string(26, '-') << std::endl
       << "Fancy Restaurant (" << size() << ")\n"
       << std::string(26, '-') << std::endl;

    if (m_cnt == 0) {
      os << "This restaurant is empty!" << std::endl;
    } else {
      for (size_t i = 0; i < m_cnt; ++i) os << *m_reserve[i];
    }
    os << std::string(26, '-') << std::endl;
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const Restaurant& rhs) {
    return rhs.display(os);
  }
}
