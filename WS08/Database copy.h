//*****************************************************************************
//  <assessment name example : Workshop - #8 (Part - 2>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//    Email       : syang153@myseneca.ca
//    Section     : OOP345 NDD
//    Date        : July 18th, 2024
//    Authenticity Declaration :
//  I have done all the coding by myself and only copied the code
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>  // For std::replace
#include <string>
#include <memory>

namespace seneca {
  const int MAX_ARRAY = 20;
  enum class Err_Status {
    Err_Success,
    Err_NotFound,
    Err_OutOfMemory,
  };
  template <typename T>
  class Database {
    // A variable representing the number of entries in the database.
    size_t m_number{0};
    /* A statically-allocated array of strings representing the keys. 
    The size of this array is 20. */
    std::string m_key[MAX_ARRAY]{};
    /* A statically-allocated array of strings representing the values. 
    The size of this array is 20. */
    T m_value[MAX_ARRAY]{};
    // A string representing the database file name.
    std::string m_filename;
    // A static attribute representing the instance (see above).
    inline static std::shared_ptr<Database> m_instance;
    /* a private constructor to prevent client from instantiating this class. 
    This constructor:
      - prints to the screen the address of the current instance 
        and the prototype of the constructor (see sample output for details)
      - opens the file and read the key/value pairs into the attributes. 
        Assume that the file is correct and exists (no need to check for errors).
      - replaces any underscore character (_) 
        that appears in the keys with a single space ( ) 
        before storing it into attributes.
    update the constructor; 
    after loading a value from the database file, call the encryptDecrypt() function, 
    passing the value as a parameter (the value in the file is encrypted, 
    and this function will decrypt it). */
    Database(const std::string& filename);
    // an empty body function (does nothing, we will specialize it later).
    void encryptDecrypt(T& value); 
  public:
    /* Create a public class function (static member function) named getInstance(const std::string& filename). 
    This function:
      - receives as a parameter a string representing the filename of the database file
      - if the class Database has already been instantiated (the static attribute is not null), 
        then this function returns the static attribute and does nothing else.
      - if the class Database has not been instantiated (the static attribute is null), 
        then this function creates an instance of type Database (using the private constructor) 
        and stores it in the static attribute. Return the static attribute to the client. */
    static std::shared_ptr<Database> getInstance(const std::string& filename);
    /* a query that searches in the array of keys for a the first parameter:
      - if the key is found, store in the second parameter the corresponding value 
        from the array of values and return Err_Status::Err_Success.
      - if the key is not found, return Err_Status::Err_NotFound. */
    Err_Status GetValue(const std::string& key, T& value);
    /* a modifier that receives as parameters a key and a value. 
    If there is space in the database (the capacity of the array not been reached), 
    the key/value pair is added and the function returns Err_Success. 
    Otherwise, it returns Err_OutOfMemory. */
    Err_Status SetValue(const std::string& key, const T& value);
    /* a destructor that
      - prints to the screen the address of the current instance 
        and the prototype of the destructor (see sample output for details)
      - iterates over the database content and creates a database backup in a separate file. 
        The backup file name will be the input file name with the string .bkp.txt appended to it. 
        For example if the input file is data.txt the backup file should be data.txt.bkp.txt.
      - the format of this file is (see sample_data.txt.bkp.txt): 
          KEY -> VALUE
          KEY -> VALUE
          KEY -> VALUE
          ...
      where KEY should be printed on a field of size 25 characters, aligned to the left.
    update the destructor: before saving a value into the backup database file, 
    call the encryptDecrypt() function, passing the value as a parameter
    (the value stored in memory is decrypted, this function will encrypt it). */
    ~Database();
  };

  template<typename T>
  Database<T>::Database(const std::string& filename) : m_filename(filename) {
    std::cout << "[" << this << "] Database(const std::string&)" << std::endl;
    std::ifstream import(filename);
    std::string key{};
    T value{};
    while ((import >> key >> value) && m_number < MAX_ARRAY) {
      std::replace(key.begin(), key.end(), '_', ' ');
      encryptDecrypt(value);
      if (m_number < MAX_ARRAY) {
        m_key[m_number] = key;
        m_value[m_number] = value;
        ++m_number;
      }
    }
  }

  template<typename T>
  std::shared_ptr<Database<T>> Database<T>::getInstance(const std::string& filename) {
    return (m_instance ? m_instance : m_instance = std::shared_ptr<Database<T>>(new Database<T>(filename)));
  }

  template<typename T>
  Err_Status Database<T>::GetValue(const std::string& key, T& value) {
    for (size_t i = 0; i < m_number; ++i) {
      if (m_key[i] == key) {
        value = m_value[i];
        return Err_Status::Err_Success;
      }
    }
    return Err_Status::Err_NotFound;
  }

  template<typename T>
  Err_Status Database<T>::SetValue(const std::string& key, const T& value) {
    if (m_number < MAX_ARRAY) {
      m_key[m_number] = key;
      m_value[m_number] = value;
      ++m_number;
      return Err_Status::Err_Success;
    }
    return Err_Status::Err_OutOfMemory;
  }

  template<typename T>
  Database<T>::~Database() {
    std::cout << "[" << this << "] ~Database()" << std::endl;
    std::ofstream backUp(m_filename + ".bkp.txt");
    for (size_t i = 0; i < m_number; ++i) {
      encryptDecrypt(m_value[i]);
      backUp << std::left << std::setw(25) << m_key[i] << " -> " << m_value[i] << std::endl;
    }
  }

  template<>
  void Database<std::string>::encryptDecrypt(std::string& value) {
    const char secret[]{ "secret encryption key" };
    for (auto& c : value)
      for (auto& k : secret)
        c ^= k;
  }

  template<>
  void Database<long long>::encryptDecrypt(long long& value) {
    const char secret[]{ "super secret encryption key" };
    for (size_t i = 0; i < sizeof(value); ++i)
      for (auto& k : secret)
        reinterpret_cast<char*>(&value)[i] ^= k;
  }
}
#endif  // !SENECA_DATABASE_H
