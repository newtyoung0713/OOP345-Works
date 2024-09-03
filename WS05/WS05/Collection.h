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
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <iostream>
#include <iomanip>
#include <string>

namespace seneca {
  template<typename T>
  class Collection {
    std::string m_name{};
    T* m_items{nullptr};
    size_t m_size{0};
    void (*m_observer)(const Collection<T>&, const T&){};
    void setEmpty();
  public:
    Collection(const std::string& name);
    Collection(const Collection& rhs) = delete;
    Collection& operator=(const Collection& rhs) = delete;
    Collection(const Collection&& rhs) = delete;
    Collection& operator=(const Collection&& rhs) = delete;
    ~Collection();
    const std::string& name() const;
    size_t size() const;
    void setObserver(void (*observer)(const Collection<T>&, const T&));
    Collection<T>& operator+=(const T& item);
    T& operator[](size_t idx) const;
    T* operator[](const std::string& title) const;
    
    std::ostream& display(std::ostream& os) const;
  };
  template<typename T>
  std::ostream& operator<<(std::ostream& os, const Collection<T>& rhs);

  template<typename T>
  Collection<T>::Collection(const std::string& name)
   : m_name(name), m_items(nullptr), m_size(0), m_observer(nullptr) {}
  
  template<typename T>
  Collection<T>::~Collection() {
    setEmpty();
  }

  template<typename T>
  void Collection<T>::setEmpty() {
    if (m_items != nullptr) {
      delete[] m_items;
      m_items = nullptr;
    }
  }

  template<typename T>
  const std::string& Collection<T>::name() const { return m_name; }
  
  template<typename T>
  size_t Collection<T>::size() const { return m_size; }
  
  template<typename T>
  void Collection<T>::setObserver(void (*observer)(const Collection<T>&, const T&)) {
    m_observer = observer;
  }
  
  template<typename T>
  Collection<T>& Collection<T>::operator+=(const T& item) {
    for (auto i = 0u; i < m_size; ++i)
      if (m_items[i].title() == item.title()) return *this;

    T* temp = new T[m_size + 1];
    for (auto i = 0u; i < m_size; ++i) temp[i] = m_items[i];
    temp[m_size++] = item;
    setEmpty();
    m_items = temp;
    temp = nullptr;
    if (m_observer) m_observer(*this, item);
    return *this;
  }
  
  template<typename T>
  T& Collection<T>::operator[](size_t idx) const {
    if (idx >= m_size)
      throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has ["
                               + std::to_string(m_size) + "] items.");
    return m_items[idx];
  }
  
  template<typename T>
  T* Collection<T>::operator[](const std::string& title) const {
    for (auto i = 0u; i < m_size; ++i)
      if (m_items[i].title() == title) return &m_items[i];
    return nullptr;
  }
  
  template<typename T>
  std::ostream& Collection<T>::display(std::ostream& os) const {
    for (auto i = 0u; i < size(); ++i) os << m_items[i];
    return os;
  }
  
  template<typename T>
  std::ostream& operator<<(std::ostream& os, const Collection<T>& rhs) {
    return rhs.display(os);
  }
}
#endif  // !SENECA_COLLECTION_H
