#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H
#include <chrono>

namespace seneca {
  class TimedTask {
    static const int MAX_RECORD = 10;
    int m_numOfRecord{};
    std::chrono::steady_clock::time_point m_startTime{};
    std::chrono::steady_clock::time_point m_endTime{};
    struct {
      std::string m_taskName{};
      std::string m_unit{};
      std::chrono::steady_clock::duration m_duration{};
    } Task[MAX_RECORD]{};
  public:
    TimedTask();
    void startClock();
    void stopClock();
    void addTask(const char* taskName);
    friend std::ostream& operator<<(std::ostream& os, TimedTask& uneAutre);
  };
}

#endif  //  !SENECA_TIMEDTASK_H