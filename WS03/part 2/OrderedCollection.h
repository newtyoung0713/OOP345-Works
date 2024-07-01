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
#ifndef SENECA_ORDEREDCOLLECTION_H
#define SENECA_ORDEREDCOLLECTION_H
#include "Collection.h"

namespace seneca {
  template<typename T>
  class OrderedCollection : public Collection<T, 72> {
  public:
    bool operator+=(const T& rhs);
  };

  template<typename T>
  bool OrderedCollection<T>::operator+=(const T& rhs) {
    bool flag = Collection<T, 72>::operator+=(rhs);
    for (size_t i = 0; i < Collection<T, 72>::size(); ++i) {
      for (size_t j = 0; j < Collection<T, 72>::size() - i - 1; ++j) {
        if (Collection<T, 72>::operator[](j) > Collection<T, 72>::operator[](j + 1)) {
          auto temp = Collection<T, 72>::operator[](j);
          Collection<T, 72>::operator[](j) = Collection<T, 72>::operator[](j + 1);
          Collection<T, 72>::operator[](j + 1) = temp;
        }
      }
    }
    return flag;
  }
}

#endif    // ! SENECA_ORDEREDCOLLECTION_H