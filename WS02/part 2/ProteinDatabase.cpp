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
#include <fstream>
#include "ProteinDatabase.h"

namespace seneca {
  ProteinDatabase::ProteinDatabase() : m_numOfString(0), m_dbString(nullptr) {}
  ProteinDatabase::ProteinDatabase(const char* filename)
   : m_numOfString(0), m_dbString(nullptr) {
    std::ifstream import(filename);
    std::string line{}, sequence{};
    size_t index{};
    if (!import) setEmpty();
    else {
      // Reading each line and increment 1 for number of string if got a '>'
      while (std::getline(import, line)) {
        if (line[0] == '>') ++m_numOfString;
      }

      m_dbString = new std::string[m_numOfString];
      import.clear();
      import.seekg(0, std::ios::beg);   // Re-point to the beginning of the file

      // Re-reading the file, and assign the string into string array
      while (std::getline(import, line)) {
        // If got a '>', then starts a new string array
        if (line[0] == '>') {
          if (index > 0) {
            m_dbString[index - 1] = sequence; // Storing a string into array
            sequence.clear(); // clean the string for new one
          }
          index++;
        } else {
          sequence += line; // appending the current data into sequence string
        }
      }
      // Storing the last string into the array
      if (index > 0) m_dbString[index - 1] = sequence;
    }
  }
  // Rule of Three
  ProteinDatabase::~ProteinDatabase() {
    setEmpty();
  }
  ProteinDatabase::ProteinDatabase(const ProteinDatabase& uneAutre)
   : m_numOfString(0), m_dbString(nullptr) {
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
  ProteinDatabase::ProteinDatabase(ProteinDatabase&& uneAutre)
   noexcept : m_numOfString(0), m_dbString(nullptr) {
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
    // Making sure all the situation are wrong and setting to an empty string
    return (!m_numOfString || idx < 0 || idx > m_numOfString - 1) ? "" : m_dbString[idx];
  }
  void ProteinDatabase::setEmpty() {
    delete[] m_dbString;
    m_dbString = nullptr;
  }
}