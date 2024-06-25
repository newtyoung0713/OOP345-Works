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
#include <iomanip>
#include "TimedTask.h"

namespace seneca {
  TimedTask::TimedTask() : m_numOfRecord(0) {}
  void TimedTask::startClock() {
    m_startTime = std::chrono::steady_clock::now();
  }
  void TimedTask::stopClock() {
    m_endTime = std::chrono::steady_clock::now();
  }
  void TimedTask::addTask(const char* taskName) {
    if (m_numOfRecord < MAX_RECORD) {
      Task[m_numOfRecord].m_taskName = taskName;
      Task[m_numOfRecord].m_unit = "nanoseconds";
      Task[m_numOfRecord].m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime);
      ++m_numOfRecord;
    }
  }
  std::ostream& operator<<(std::ostream& os, TimedTask& uneAutre) {
    os << "--------------------------\n"
       << "Execution Times:\n"
       << "--------------------------" << std::endl;
    for (int i = 0; i < uneAutre.m_numOfRecord; ++i) {
      os << std::setw(21) << std::left << uneAutre.Task[i].m_taskName
         << std::setw(13) << std::right << uneAutre.Task[i].m_duration.count()
         << " " << uneAutre.Task[i].m_unit << std::endl;
    }
    os << "--------------------------" << std::endl;
    return os;
  }
}