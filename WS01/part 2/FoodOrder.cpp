//*****************************************************************************
//  <assessment name example : Workshop - #1 (Part - 2)>
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
#include <cstring>
#include <string>
#include "FoodOrder.h"

double g_taxrate = 0;
double g_dailydiscount = 0;

namespace seneca {
  FoodOrder::FoodOrder() : m_foodDesc(nullptr), m_foodPrice(0), m_isSpecial(false) {
    m_cusName[0] = '\0';
  }
  FoodOrder::~FoodOrder() {
    setEmpty();
  }
  FoodOrder::FoodOrder(const FoodOrder& uneAutre) : m_foodDesc(nullptr) {
    *this = uneAutre;
  }
  FoodOrder& FoodOrder::operator=(const FoodOrder& uneAutre) {
    if (this != &uneAutre) {
      delete[] m_foodDesc;
      m_foodDesc = nullptr;

      if (uneAutre.m_cusName[0] != '\0') {
        strcpy(m_cusName, uneAutre.m_cusName);
        m_foodDesc = new char[strlen(uneAutre.m_foodDesc) + 1];
        strcpy(m_foodDesc, uneAutre.m_foodDesc);
        m_foodPrice = uneAutre.m_foodPrice;
        m_isSpecial = uneAutre.m_isSpecial;
      }
    }
    return *this;
  }
  std::istream& FoodOrder::read(std::istream& is) {
    if (!is) return is;
    std::string tempStr;
    // is.getline is from a member function of std::istream
    is.getline(m_cusName, MAX_NAME_LEN + 1, ',');
    // std::getline is from non-member function of STL
    std::getline(is, tempStr, ',');
    is >> m_foodPrice;
    is.ignore();
    m_isSpecial = (is.get() == 'Y');
    is.ignore();

    if (is.fail()) setEmpty();
    else {
      delete[] m_foodDesc;
      m_foodDesc = nullptr;
      // std::string::length will return size_t
      // Therefore, we use it to get the length of string
      m_foodDesc = new char[tempStr.length() + 1];
      // std::string::c_str will return C-String
      // Therefore, we can use it to copy string to char*
      strcpy(m_foodDesc, tempStr.c_str());
    }
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
                  << std::fixed << std::setprecision(2) 
                  << std::right << (m_foodPrice + (m_foodPrice * g_taxrate) - g_dailydiscount) :
        std::cout << "";
    } else {std::cout << "No Order";}
    std::cout << std::endl;
    count++;
  }

  void FoodOrder::setEmpty() {
    if (m_foodDesc != nullptr) {
      delete[] m_foodDesc;
      m_foodDesc = nullptr;
    }
    m_cusName[0] = '\0';
    m_foodPrice = 0;
    m_isSpecial = false;
  }
}