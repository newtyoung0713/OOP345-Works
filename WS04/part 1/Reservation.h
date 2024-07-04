#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H
#include <iostream>
#include <iomanip>
#include <string.h>

namespace seneca {
  class Reservation {
    std::string m_id;
    std::string m_name;
    std::string m_email;
    size_t m_numOfPpl;
    int m_day;
    int m_hours;
    void printFormat(std::ostream& os) const;
  public:
    Reservation();
    Reservation(const std::string& res);
    void update(int day, int time);
    std::ostream& display(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Reservation& rhs);
  };
}
#endif  // !SENECA_RESERVATION_H