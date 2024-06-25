//*****************************************************************************
//  <assessment name example : Workshop - #2 (Part - 1)>
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
#include <sstream>
#include <fstream>
#include "ProteinDatabase.h"

namespace seneca {
  ProteinDatabase::ProteinDatabase() : m_numOfString(0), m_dbString(nullptr) {}
  ProteinDatabase::ProteinDatabase(const char* filename) : ProteinDatabase() {
    // std::ifstream import(filename);
    // if (import.is_open()) {
    //   std::string temp{};
    //   while (std::getline(import, temp)) {
    //     if (temp[0] == '>') m_numOfString++;
    //   }
    // }

    // import.close();
    // import.seekg(0, std::ios::beg);
    // m_dbString = new std::string[m_numOfString];

    // size_t index = 0;
    // std::string tempStr{};
    // while (import.peek() != EOF && tempStr[0] == '>') {
    //   std::string temp{};
    //   while (import) {
    //     std::getline(import, temp, '\n');
    //     if (temp[0] != '>') {
    //       tempStr += temp;
    //     } else {
    //       tempStr = temp;
    //     }
    //   }
    //   m_dbString[index] = tempStr;
    //   ++index;
    // }
    std::ifstream file(filename);
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
      if (line[0] == '>') m_numOfString++;
    }

    m_dbString = new std::string[m_numOfString];
    file.clear();
    file.seekg(0, std::ios::beg);

    size_t index = 0;
    std::stringstream sequenceStream;
    while (std::getline(file, line)) {
      if (line[0] == '>') {
        if (index > 0) {
          m_dbString[index - 1] = sequenceStream.str();
          sequenceStream.str(std::string());
        }
        index++;
      } else {
        sequenceStream << line;
      }
    }
    if (index > 0) m_dbString[index - 1] = sequenceStream.str();
  }
  // Rule of Three
  ProteinDatabase::~ProteinDatabase() {
    delete[] m_dbString;
    m_dbString = nullptr;
  }
  ProteinDatabase::ProteinDatabase(const ProteinDatabase& uneAutre) : ProteinDatabase() {
    *this = uneAutre;
  }
  ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& uneAutre) {
    if (this != &uneAutre) {
      delete[] m_dbString;
      m_dbString = nullptr;

      if (uneAutre.m_numOfString != 0) {
        m_numOfString = uneAutre.m_numOfString;
        m_dbString = new std::string[m_numOfString];
        for (auto i = 0u; i < m_numOfString; ++i) {
          m_dbString[i] = uneAutre.m_dbString[i];
        }
      }
    }
    return *this;
  }
  // Rule of Five
  ProteinDatabase::ProteinDatabase(ProteinDatabase&& uneAutre) : ProteinDatabase() {
    *this = std::move(uneAutre);
  }
  ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& uneAutre) {
    if (this != &uneAutre) {
      delete[] m_dbString;
      m_dbString = nullptr;
      m_numOfString = uneAutre.m_numOfString;
      m_dbString = uneAutre.m_dbString;
      uneAutre.m_dbString = nullptr;
    }
    return *this;
  }
  size_t ProteinDatabase::size() {
    return m_numOfString;
  }
  std::string ProteinDatabase::operator[](size_t idx) {
    std::string temp{};
    if (!m_numOfString || idx < 0 || idx > m_numOfString - 1) {
      temp = "";
    } else {
      if (m_dbString) temp = m_dbString[idx];
    }
    return temp;
  }
}