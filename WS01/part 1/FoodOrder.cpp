//*****************************************************************************
//  <assessment name example : Workshop - #1 (Part - 1)>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//	Email       : syang153@myseneca.ca
//	Section     : OOP345 NDD
//	Date        : May 10th, 2024
//	Authenticity Declaration :
//  I have done all the coding by myself and only copied the code 
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "FoodOrder.h"

double g_taxrate = 0;
double g_dailydiscount = 0;

namespace seneca {
  FoodOrder::FoodOrder() {
    setEmpty();
  }
  std::istream& FoodOrder::read(std::istream& is) {
    if (!is) return is;
    is.getline(m_cusName, MAX_NAME_LEN + 1, ',');
    is.getline(m_foodDesc, 26, ',');
    is >> m_foodPrice;
    is.ignore();
    m_isSpecial = (is.get() == 'Y');
    is.ignore();

    if (is.fail()) setEmpty();
    return is;
  }
  void FoodOrder::display() const {
    static int count = 1;
    std::cout << std::left << std::setw(2) << std::setfill(' ') << count << ". " << std::left;
    if (m_cusName[0] != '\0') {
      std::cout << std::setw(10) << std::setfill(' ') << m_cusName << "|"
                << std::setw(25) << std::setfill(' ') << m_foodDesc << "|"
                << std::setw(12) << std::setfill(' ')
                << std::fixed << std::setprecision(2) 
                << m_foodPrice + (m_foodPrice * g_taxrate) << "|";
      (m_isSpecial) ?
        std::cout << std::setw(13) << std::setfill(' ')
                  << std::fixed << std::setprecision(2) << std::right 
                  << (m_foodPrice + (m_foodPrice * g_taxrate) - g_dailydiscount) :
        std::cout << "";
    } else {std::cout << "No Order";}
    std::cout << std::endl;
    count++;
  }

  void FoodOrder::setEmpty() {
    m_cusName[0] = '\0';
    m_foodDesc[0] = '\0';
    m_foodPrice = 0.0;
    m_isSpecial = true;
  }
}