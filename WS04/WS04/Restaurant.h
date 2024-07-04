#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H
#include <iostream>
#include <string>
#include "Reservation.h"

namespace seneca {
  class Restaurant {
    const Reservation** m_reserve;
    size_t m_cnt;
    static size_t m_numReserve;
    void setEmpty();
  public:
    Restaurant();
    Restaurant(const Reservation* reservations[], size_t cnt);
    Restaurant(const Restaurant& uneAutre);
    Restaurant& operator=(const Restaurant& uneAutre);

    Restaurant(Restaurant&& uneAutre) noexcept;
    Restaurant& operator=(Restaurant&& uneAutre) noexcept;
    ~Restaurant();
    
    size_t size() const;
    
    std::ostream& display(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Restaurant& rhs);
  };
}
#endif  // !SENECA_RESTAURANT_H
