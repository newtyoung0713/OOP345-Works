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
    void setSmallestItem(const T& item) {
      if (item < m_smallestItem) m_smallestItem = item;
    }
    void setLargestItem(const T& item) {
      if (item > m_largestItem) m_largestItem = item;
    }
  public:
    static T getSmallestItem() {
      return m_smallestItem;
    }
    static T getLargestItem() {
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
  };

  template <typename T, unsigned C>
  T Collection<T, C>::m_smallestItem = 9999;
  template <typename T, unsigned C>
  T Collection<T, C>::m_largestItem = -9999;

  template <>
  Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);
  template <>
  Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);
}

#endif    // ! SENECA_COLLECTION_H