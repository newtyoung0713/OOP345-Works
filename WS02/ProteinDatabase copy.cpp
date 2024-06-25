//*****************************************************************************
//  <assessment name example : Workshop - #2 (Part - 2)>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//	Email       : syang153@myseneca.ca
//	Section     : OOP345 NDD
//	Date        : May 22nd, 2024
//	Authenticity Declaration :
//  I have done all the coding by myself and only copied the code 
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include "ProteinDatabase.h"

namespace seneca {
  ProteinDatabase::ProteinDatabase() : m_numOfString(0), m_dbString(nullptr) {}
  ProteinDatabase::ProteinDatabase(const char* filename) {
    if (!filename) setEmpty();
    else {
      std::ifstream import(filename);
      std::string line{}, temp{};
      char ch{};
      size_t index{};

      while (import) {
        import.get(ch);
        if (ch == '>') ++index;
      }

      m_dbString = new std::string[index];
      import.clear();
      import.seekg(0, std::ios::beg);

      for (auto i = 0u; i < index; ++i) {
        std::getline(import, temp, '\n');
        while (temp.length() == 60) {
          line.append(temp);
          std::getline(import, temp, '\n');
        }
        line.append(temp);
        m_dbString[i] = line;
        ++m_numOfString;
      }
    }
  }
  // Rule of Three
  ProteinDatabase::~ProteinDatabase() {
    setEmpty();
  }
  ProteinDatabase::ProteinDatabase(const ProteinDatabase& uneAutre) {
    *this = uneAutre;
  }
  ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& uneAutre) {
    if (this != &uneAutre) {
      setEmpty();
      if (uneAutre.m_numOfString != 0) {
        m_numOfString = uneAutre.m_numOfString;
        m_dbString = new std::string[m_numOfString];
        for (auto i = 0u; i < m_numOfString; ++i)
          m_dbString[i] = uneAutre.m_dbString[i];
      }
    }
    return *this;
  }
  // Rule of Five
  ProteinDatabase::ProteinDatabase(ProteinDatabase&& uneAutre) noexcept {
    *this = std::move(uneAutre);
  }
  ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& uneAutre) noexcept {
    if (this != &uneAutre) {
      setEmpty();
      m_numOfString = uneAutre.m_numOfString;
      m_dbString = uneAutre.m_dbString;
      uneAutre.m_dbString = nullptr;
      uneAutre.m_numOfString = 0;
    }
    return *this;
  }
  size_t ProteinDatabase::size() {
    return m_numOfString;
  }
  std::string ProteinDatabase::operator[](size_t idx) {
    std::string temp{'\0'};
    if (idx < m_numOfString) temp = m_dbString[idx];
    return temp;
  }
  void ProteinDatabase::setEmpty() {
    delete[] m_dbString;
    m_dbString = nullptr;
  }
}