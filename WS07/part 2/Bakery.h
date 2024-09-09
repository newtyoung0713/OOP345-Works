#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <fstream>
#include <stdexcept>
#include <numeric>

namespace seneca {
  enum class BakedType {
    BREAD, PASTERY
  };
  struct BakedGood {
    // Baked Type (either BREAD or PASTERY from the above enum)
    BakedType m_type;
    // Description of the baked item
    std::string m_desc;
    // The shelf life of the item in days
    int m_shelfLife;
    // The amount of stock for the item
    int m_stock;
    // The price of the item
    double m_price;
  };
  class Bakery {
    std::vector<BakedGood> m_bkGood;
    std::string trim(std::string dup, const char sb);
  public:
    /* a custom constructor that receives as a parameter the name of the file containing the information about the BakedGoods to be added to the collection.
      If the filename is incorrect, this constructor should throw an exception.
      Each line from the file contains information about a single BakedGood in the following format:
          BakedType Description ShelfLife Stock Price 
      The fields are not separated by delimiters; each field has a fixed size:
          BakeType has a field size of 8
          Description has a field size of 20
          ShelfLife has a field size of 14
          Stock has a field size of 8
          Price has a field size of 6
      Any blank space at the begining/end of a token is not part of the token and should be removed.
      The read in BakedGood will populate the collection. */
    Bakery(const std::string src);
    /* update this function to display the total stock 
    and price of the goods in the collection. 
    See the sample output for the format. DO NOT USE MANUAL LOOPS! */
    void showGoods(std::ostream& os) const;
    /* receives a parameter the name of the field used to sort the collection in ascending order. 
    The parameter can have one of the values: 
    Description, Shelf, Stock, Price. DO NOT USE MANUAL LOOPS! */
    void sortBakery(const std::string& field);
    /* receives a parameter of another Bakery object reference 
    and combines the collection of BakedGoods from the current object 
    and the parameter and returns the combined collection. 
    The combined collection should be ordered by price. DO NOT USE MANUAL LOOPS! */
    std::vector<BakedGood> combine(Bakery& src);
    /* receives the Description of a BakedGood and a BakedType as parameters, 
    and returns true if the collection contains Stock of that BakedGood. DO NOT USE MANUAL LOOPS! */
    bool inStock(const std::string desc, const BakedType type) const;
    /* receives a BakedType as a parameter, 
    and returns the list of all the out of stock items in the collection. DO NOT USE MANUAL LOOPS! */
    std::list<BakedGood> outOfStock(BakedType type) const;
  };
  /* inserts one BakedGood into the first parameter, using the following format (the width of each field is specified in brackets):
      * BakedType(10) * Description(20) * ShelfLife(5) * Stock(5) * Price(8) * 
  The price should be printed with two decimal place precision.
  Look in the sample output to see how the numbers should be formatted and the alignment of each field. */
  std::ostream& operator<<(std::ostream& out, const BakedGood& b);
}
#endif  // !SENECA_BAKERY_H
