//*****************************************************************************
//  <assessment name example : Workshop - #4 (Part - 1>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//    Email       : syang153@myseneca.ca
//    Section     : OOP345 NDD
//    Date        : June 02nd, 2024
//    Authenticity Declaration :
//  I have done all the coding by myself and only copied the code
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#include "Reservation.h"

namespace seneca {
  Reservation::Reservation()
   : m_id(""), m_name(""), m_email(""), m_numOfPpl(0), m_day(0), m_hours(0) {}

  Reservation::Reservation(const std::string& res) {
    std::string temp = res;
    m_id = temp.substr(0, temp.find(':'));
    m_id.erase(0, m_id.find_first_not_of(' '));
    m_id.erase(m_id.find_last_not_of(' ') + 1);
    temp.erase(0, temp.find(':') + 1);
    
    m_name = temp.substr(0, temp.find(','));
    m_name.erase(0, m_name.find_first_not_of(' '));
    m_name.erase(m_name.find_last_not_of(' ') + 1);
    temp.erase(0, temp.find(',') + 1);
    
    m_email = temp.substr(0, temp.find(','));
    m_email.erase(0, m_email.find_first_not_of(' '));
    m_email.erase(m_email.find_last_not_of(' ') + 1);
    temp.erase(0, temp.find(',') + 1);

    m_numOfPpl = std::stoi(temp.substr(0, temp.find(',')));
    temp.erase(0, temp.find(',') + 1);

    m_day = std::stoi(temp.substr(0, temp.find(',')));
    temp.erase(0, temp.find(',') + 1);

    m_hours = std::stoi(temp);
  }

  void Reservation::update(int day, int time) {
    m_day = day;
    m_hours = time;
  }

  void Reservation::printFormat(std::ostream& os) const {
    os << " on day " << m_day << " @ " << m_hours << ":00 for " << m_numOfPpl
       << (m_numOfPpl > 1 ? " people." : " person.");
  }

  std::ostream& Reservation::display(std::ostream& os) const {
    os << "Reservation " << std::right << std::setw(10) << m_id << ": "
       << std::right << std::setw(20) << m_name << "  "
       << std::left << std::setw(20) << ("<" + m_email + ">") << "    ";
    if (m_hours >= 6 && m_hours <= 9) {
      os << "Breakfast";
    } else if (m_hours >= 11 && m_hours <= 15) {
      os << "Lunch";
    } else if (m_hours >= 17 && m_hours <= 21) {
      os << "Dinner";
    } else {
      os << "Drinks";
    }
    printFormat(os);
    os << std::endl;
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const Reservation& rhs) {
    return rhs.display(os);
  }
}
