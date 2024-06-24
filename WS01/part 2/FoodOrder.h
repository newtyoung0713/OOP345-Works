#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include <iostream>

extern double g_taxrate;
extern double g_dailydiscount;
namespace seneca {
  static constexpr int MAX_NAME_LEN = 9;
  class FoodOrder {
    char m_cusName[MAX_NAME_LEN + 1];
    char* m_foodDesc;
    double m_foodPrice;
    bool m_isSpecial;
    void setEmpty();
  public:
    FoodOrder();
    ~FoodOrder();
    FoodOrder(const FoodOrder& uneAutre);
    FoodOrder& operator=(const FoodOrder& uneAutre);
    std::istream& read(std::istream& is);
    void display() const;
  };
}

#endif  // !SENECA_FOODORDER_H