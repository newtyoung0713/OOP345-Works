//*****************************************************************************
//  <assessment name example : Workshop - #3 (Part - 2>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//	Email       : syang153@myseneca.ca
//	Section     : OOP345 NDD
//	Date        : May 28th, 2024
//	Authenticity Declaration :
//  I have done all the coding by myself and only copied the code 
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <iostream>

namespace seneca {
  template<typename T, unsigned C>
  class Collection {
    T m_items[C]{};
    size_t m_size{};
    static T m_smallestItem;
    static T m_largestItem;
  protected:
    void setSmallestItem(const T& item);
    void setLargestItem(const T& item) {
      if (item > m_largestItem) m_largestItem = item;
    }
    T& operator[](unsigned int idx) {
      return m_items[idx];
    }
    void incrSize() {
      if (m_size < C) ++m_size;
    }
  public:
    static T getSmallestItem() const {
      return m_smallestItem;
    }
    static T getLargestItem() const {
      return m_largestItem;
    }
    size_t size() {
      return m_size;
    }
    size_t capacity() {
      return C;
    }
    bool operator+=(const T& rhs) {
      if (m_size >= C) return false;
      setSmallestItem(rhs);
      setLargestItem(rhs);
      m_items[m_size++] = rhs;
      return true;
    }
    void print(std::ostream& os) const {
      os << "[";
      for (size_t i = 0; i < m_size; ++i) {
        os << m_items[i];
        if (i < m_size - 1) os << ',';
      }
      os << "]" << std::endl;
    }
    void printBookList(std::ostream& os) const {
      os << "| " << std::string(75, '-') << "|" << std::endl;
      for (size_t i = 0; i < m_size; i++) os << "| " << m_items[i] << " |" << std::endl;
      os << "| " << std::string(75, '-') << "|" << std::endl;
    }
  };

  template <typename T, unsigned C>
  T Collection<T, C>::m_smallestItem = 9999;
  template <typename T, unsigned C>
  T Collection<T, C>::m_largestItem = -9999;

  template <>
  Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);
  template <>
  Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

  template <>
  Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);
  template <>
  Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);
  
  template<>
  void Collection<Book, 10>::print(std::ostream& os) const {
    printBookList(os);
  }
  template<>
  void Collection<Book, 72>::print(std::ostream& os) const {
    printBookList(os);
  }
}

#endif    // ! SENECA_COLLECTION_H