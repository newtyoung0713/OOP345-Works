//*****************************************************************************
//  <assessment name example : Workshop - #3 (Part - 2>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//	Email       : syang153@myseneca.ca
//	Section     : OOP345 NDD
//	Date        : May 30th, 2024
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
    void setLargestItem(const T& item);
    T& operator[](unsigned int idx);
    void incrSize();
  public:
    static T getSmallestItem();
    static T getLargestItem();
    size_t size() const;
    size_t capacity() const;
    bool operator+=(const T& rhs);
    void print(std::ostream& os) const;
    void printBookList(std::ostream& os) const;
  };

  template <typename T, unsigned C>
  T Collection<T, C>::m_smallestItem = 9999;
  template <typename T, unsigned C>
  T Collection<T, C>::m_largestItem = -9999;

  template <typename T, unsigned C>
  void Collection<T, C>::setSmallestItem(const T& item) {
    if (item < m_smallestItem) m_smallestItem = item;
  }
  template <typename T, unsigned C>
  void Collection<T, C>::setLargestItem(const T& item) {
    if (item > m_largestItem) m_largestItem = item;
  }
  template <typename T, unsigned C>
  T& Collection<T, C>::operator[](unsigned int idx) {
    return m_items[idx];
  }
  template <typename T, unsigned C>
  void Collection<T, C>::incrSize() {
    if (m_size < C) ++m_size;
  }
  template <typename T, unsigned C>
  T Collection<T, C>::getSmallestItem() {
    return m_smallestItem;
  }
  template <typename T, unsigned C>
  T Collection<T, C>::getLargestItem() {
    return m_largestItem;
  }
  template <typename T, unsigned C>
  size_t Collection<T, C>::size() const {
    return m_size;
  }
  template <typename T, unsigned C>
  size_t Collection<T, C>::capacity() const {
    return C;
  }
  template <typename T, unsigned C>
  bool Collection<T, C>::operator+=(const T& rhs) {
    if (m_size >= C) return false;
    setSmallestItem(rhs);
    setLargestItem(rhs);
    m_items[m_size++] = rhs;
    return true;
  }
  template <typename T, unsigned C>
  void Collection<T, C>::print(std::ostream& os) const {
    os << "[";
    for (size_t i = 0; i < m_size; ++i) {
      os << m_items[i];
      if (i < m_size - 1) os << ',';
    }
    os << "]" << std::endl;
  }
  template <typename T, unsigned C>
  void Collection<T, C>::printBookList(std::ostream& os) const {
    os << "| " << std::string(75, '-') << "|" << std::endl;
    for (size_t i = 0; i < m_size; i++) os << "| " << m_items[i] << " |" << std::endl;
    os << "| " << std::string(75, '-') << "|" << std::endl;
  }

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