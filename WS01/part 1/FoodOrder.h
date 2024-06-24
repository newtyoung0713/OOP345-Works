#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include <iostream>

extern double g_taxrate;
extern double g_dailydiscount;
namespace seneca {
  class FoodOrder {
    static constexpr int MAX_NAME_LEN = 10;
    char m_cusName[MAX_NAME_LEN + 1];
    char m_foodDesc[26];
    double m_foodPrice;
    bool m_isSpecial;
    void setEmpty();
  public:
    FoodOrder();
    std::istream& read(std::istream& is);
    void display() const;
  };
}

#endif  // !SENECA_FOODORDER_H