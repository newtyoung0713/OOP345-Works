#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

namespace seneca {
  class SpellChecker {
    std::string m_badWords[6]{};
    std::string m_goodWords[6]{};
    size_t m_cnt[6]{0};
  public:
    SpellChecker(const char* filename);
    void operator()(std::string& text);
    void showStatistics(std::ostream& out) const;
  };
}
#endif  // !SENECA_SPELLCHECKER_H
