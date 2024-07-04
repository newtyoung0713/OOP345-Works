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
#include "ConfirmationSender.h"

namespace seneca {
  void ConfirmationSender::setEmpty() {
    if (m_reserve != nullptr) {
      delete[] m_reserve;
      m_reserve = nullptr;
    }
  }

  ConfirmationSender::ConfirmationSender() : m_reserve(nullptr), m_cnt(0) {}

  ConfirmationSender::ConfirmationSender(const ConfirmationSender& uneAutre)
   : m_reserve(nullptr), m_cnt(0) {
    *this = uneAutre;
   }

  ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& uneAutre) {
    if (this != &uneAutre) {
      setEmpty();

      m_cnt = uneAutre.m_cnt;
      m_reserve = new const Reservation*[m_cnt];
      for (size_t i = 0; i < m_cnt; ++i) m_reserve[i] = uneAutre.m_reserve[i];
    }
    return *this;
  }

  ConfirmationSender::ConfirmationSender(ConfirmationSender&& uneAutre) noexcept {
    *this = std::move(uneAutre);
  }

  ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& uneAutre) noexcept {
    if (this != &uneAutre) {
      setEmpty();

      m_reserve = uneAutre.m_reserve;
      m_cnt = uneAutre.m_cnt;
      uneAutre.m_reserve = nullptr;
      uneAutre.m_cnt = 0;
    }
    return *this;
  }

  ConfirmationSender::~ConfirmationSender() {
    setEmpty();
  }

  ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res) {
    for (size_t i = 0; i < m_cnt; ++i) if (m_reserve[i] == &res) return *this;

    const Reservation** temp = new const Reservation*[m_cnt + 1];
    for (size_t i = 0; i < m_cnt; ++i) temp[i] = m_reserve[i];
    temp[m_cnt] = &res;
    setEmpty();
    m_reserve = temp;
    ++m_cnt;
    return *this;
  }

  ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res) {
    bool flag = false;
    for (size_t i = 0; i < m_cnt; ++i) {
      if (m_reserve[i] == &res) flag = true;
      if (flag && i < m_cnt - 1) {
        // for (size_t j = i; j < m_cnt - 1; ++j) m_reserve[j] = m_reserve[j + 1];
        m_reserve[i] = m_reserve[i + 1];
      }
      // const Reservation** temp = new const Reservation*[m_cnt];
      // for (size_t i = 0; i < m_cnt; ++i) temp[i] = m_reserve[i];
      // setEmpty();
      // m_reserve = temp;
    }
    if (flag) {
      m_reserve[m_cnt - 1] = nullptr;
      --m_cnt;
    }
    return *this;
  }

  std::ostream& ConfirmationSender::display(std::ostream& os) const {
    os << std::string(26, '-') << std::endl
       << "Confirmations to Send\n"
       << std::string(26, '-') << std::endl;
    
    if (m_cnt == 0) {
      os << "There are no confirmations to send!" << std::endl;
    } else {
      for (size_t i = 0; i < m_cnt; ++i) os << *m_reserve[i];
    }
    os << std::string(26, '-') << std::endl;
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const ConfirmationSender& rhs) {
    return rhs.display(os);
  }
}
