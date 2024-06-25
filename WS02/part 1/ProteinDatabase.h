#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

namespace seneca {
  class ProteinDatabase {
    size_t m_numOfString{};
    std::string* m_dbString{};
  public:
    ProteinDatabase();
    ProteinDatabase(const char* filename);
    // Rule of Three
    ~ProteinDatabase();
    ProteinDatabase(const ProteinDatabase& uneAutre);
    ProteinDatabase& operator=(const ProteinDatabase& uneAutre);
    // Rule of Five
    ProteinDatabase(ProteinDatabase&& uneAutre);
    ProteinDatabase& operator=(ProteinDatabase&& uneAutre);
    size_t size();
    std::string operator[](size_t idx);
  };
}

#endif  //  !SENECA_PROTEINDATABASE_H