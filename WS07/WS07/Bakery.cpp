//*****************************************************************************
//  <assessment name example : Workshop - #7 (Part - 2>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//    Email       : syang153@myseneca.ca
//    Section     : OOP345 NDD
//    Date        : July 11th, 2024
//    Authenticity Declaration :
//  I have done all the coding by myself and only copied the code
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#include "Bakery.h"

namespace seneca {
  /* a custom constructor that receives as a parameter the name of the file containing the information 
  about the BakedGoods to be added to the collection.
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
  Bakery::Bakery(const std::string src) {
    std::ifstream import(src);
    std::string temp{};
    if (!import) throw std::runtime_error("Cannot open file: " + src);
    while (std::getline(import, temp)) {
      BakedGood bg{};
      bg.m_type = (trim(temp.substr(0, 8), ' ') == "Bread") ? BakedType::BREAD : BakedType::PASTERY;
      bg.m_desc = trim(temp.substr(8, 20), ' ');
      bg.m_shelfLife = std::stoi(trim(temp.substr(28, 14), ' '));
      bg.m_stock = std::stoi(trim(temp.substr(42, 8), ' '));
      bg.m_price = std::stod(trim(temp.substr(50, 6), ' '));
      // After extraction, put data into BakedGood
      m_bkGood.push_back(bg);
    }
  }
  std::string Bakery::trim(std::string dup, const char sb) {
    auto before = dup.find_first_not_of(sb);  // Get first char which is not whitespace
    auto after = dup.find_last_not_of(sb);  // Get last char which is not whitespace
    return (before == std::string::npos) ? dup : dup.substr(before, after - before + 1);
  }
  /* update this function to display the total stock 
  and price of the goods in the collection. 
  See the sample output for the format. DO NOT USE MANUAL LOOPS! */
  void Bakery::showGoods(std::ostream& os) const {
    int totalStock = std::accumulate(m_bkGood.begin(), m_bkGood.end(), 0, 
                      [](int totalStock, const BakedGood& bg) { return totalStock += bg.m_stock; });
    double totalPrice = std::accumulate(m_bkGood.begin(), m_bkGood.end(), 0.0, 
                        [](double totalPrice, const BakedGood& bg) { return totalPrice += bg.m_price; });
    std::for_each(m_bkGood.begin(), m_bkGood.end(), [&](const BakedGood& bg) { os << bg << std::endl; });
    os << "Total Stock: " << totalStock << "\nTotal Price: " << totalPrice << std::endl;
  }
  /* receives a parameter the name of the field used to sort the collection in ascending order. 
  The parameter can have one of the values: 
  Description, Shelf, Stock, Price. DO NOT USE MANUAL LOOPS! */
  void Bakery::sortBakery(const std::string& field) {
    std::sort(m_bkGood.begin(), m_bkGood.end(), [field](const BakedGood& rhs, const BakedGood& lhs) {
      if (field == "Description") return rhs.m_desc < lhs.m_desc;
      else if (field == "Shelf") return rhs.m_shelfLife < lhs.m_shelfLife;
      else if (field == "Stock") return rhs.m_stock < lhs.m_stock;
      else if (field == "Price") return rhs.m_price < lhs.m_price;
      else throw std::invalid_argument("Invalid sort field");
    });
  }
  /* receives a parameter of another Bakery object reference 
  and combines the collection of BakedGoods from the current object 
  and the parameter and returns the combined collection. 
  The combined collection should be ordered by price. DO NOT USE MANUAL LOOPS! */
  std::vector<BakedGood> Bakery::combine(Bakery& src) {
    // Assign the size to COMBINED variable from both size of the origin object + the src object
    std::vector<BakedGood> combined(m_bkGood.size() + src.m_bkGood.size());
    sortBakery("Price");
    src.sortBakery("Price");
    std::merge(m_bkGood.begin(), m_bkGood.end(), src.m_bkGood.begin(), src.m_bkGood.end(), 
               combined.begin(), [](const BakedGood& rhs, const BakedGood& lhs) {
      return rhs.m_price < lhs.m_price;
    });
    return combined;
  }
  /* receives the Description of a BakedGood and a BakedType as parameters, 
  and returns true if the collection contains Stock of that BakedGood. DO NOT USE MANUAL LOOPS! */
  bool Bakery::inStock(const std::string desc, const BakedType type) const {
    return std::any_of(m_bkGood.begin(), m_bkGood.end(), [desc, type](const BakedGood& bg) {
      return bg.m_desc == desc && bg.m_type == type && bg.m_stock > 0;
    });
  }
  /* receives a BakedType as a parameter, 
  and returns the list of all the out of stock items in the collection. DO NOT USE MANUAL LOOPS! */
  std::list<BakedGood> Bakery::outOfStock(BakedType type) const {
    std::list<BakedGood> nonStock;
    std::copy_if(m_bkGood.begin(), m_bkGood.end(), 
                 std::back_inserter(nonStock), [type](const BakedGood& bg) {
      return bg.m_type == type && bg.m_stock == 0;
    });
    return nonStock;
  }
  /* inserts one BakedGood into the first parameter, using the following format (the width of each field is specified in brackets):
      * BakedType(10) * Description(20) * ShelfLife(5) * Stock(5) * Price(8) * 
  The price should be printed with two decimal place precision.
  Look in the sample output to see how the numbers should be formatted and the alignment of each field. */
  std::ostream& operator<<(std::ostream& out, const BakedGood& b) {
    std::string bg_type = (b.m_type == BakedType::BREAD) ? "Bread" : "Pastry";
    out << "* " << std::setw(10) << std::left << bg_type
        << " * " << std::setw(20) << b.m_desc
        << " * " << std::setw(5) << b.m_shelfLife
        << " * " << std::setw(5) << b.m_stock
        << " * " << std::setw(8) << std::right 
        << std::fixed << std::setprecision(2) << b.m_price << " * ";
    return out;
  }
}
