#ifndef SENECA_CONFIRMATIONSENDER_H
#define SENECA_CONFIRMATIONSENDER_H
#include <iostream>
#include <string>
#include "Reservation.h"

namespace seneca {
  class ConfirmationSender {
    const Reservation** m_reserve;
    size_t m_cnt;
    void setEmpty();
  public:
    ConfirmationSender();
    ConfirmationSender(const ConfirmationSender& uneAutre);
    ConfirmationSender& operator=(const ConfirmationSender& uneAutre);
    ConfirmationSender(ConfirmationSender&& uneAutre) noexcept;
    ConfirmationSender& operator=(ConfirmationSender&& uneAutre) noexcept;
    ~ConfirmationSender();

    ConfirmationSender& operator+=(const Reservation& res);
    ConfirmationSender& operator-=(const Reservation& res);
    
    std::ostream& display(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const ConfirmationSender& rhs);
  };
}
#endif  // !SENECA_CONFIRMATIONSENDER_H
