//*****************************************************************************
//  <assessment name example : Workshop - #5 (Part - 2>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//    Email       : syang153@myseneca.ca
//    Section     : OOP345 NDD
//    Date        : June 13th, 2024
//    Authenticity Declaration :
//  I have done all the coding by myself and only copied the code
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#include "SpellChecker.h"

namespace seneca {
  SpellChecker::SpellChecker(const char* filename) {
    std::ifstream import(filename);
    if (!import) throw "Bad file name!";
    // int cnt{0};
    // while (import) {
    //   import >> m_badWords[cnt] >> m_goodWords[cnt];
    //   ++cnt;
    // }
    for (auto i = 0u; import; ++i)
      import >> m_badWords[i] >> m_goodWords[i];
  }
  void SpellChecker::operator()(std::string& text) {
    for (auto i = 0u; i < 6; ++i) {
      while (text.find(m_badWords[i]) != std::string::npos) {
        text.replace(text.find(m_badWords[i]), m_badWords[i].length(), m_goodWords[i]);
        ++m_cnt[i];
      }
    }
  }
  void SpellChecker::showStatistics(std::ostream& out) const {
    out << "Spellchecker Statistics" << std::endl;
    for (auto i = 0u; i < 6; ++i)
      out << std::setw(15) << std::right << m_badWords[i] << ": "
          << m_cnt[i] << " replacements" << std::endl;
  }
}