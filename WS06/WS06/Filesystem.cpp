//*****************************************************************************
//  <assessment name example : Workshop - #6 (Part - 2>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//    Email       : syang153@myseneca.ca
//    Section     : OOP345 NDD
//    Date        : July 04th, 2024
//    Authenticity Declaration :
//  I have done all the coding by myself and only copied the code
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#include "Filesystem.h"

namespace seneca {
  Filesystem::Filesystem() : m_root(), m_current() {}
  /* a custom constructor that receives the name of a file as its first argument, 
  and an optional string containing the name of the root directory (defaults to an empty string). */
  Filesystem::Filesystem(const std::string filename, const std::string rootname) : Filesystem() {
    m_root = new Directory(rootname);
    m_current = m_root;
    std::ifstream import(filename);
    std::string temp, filePath, fileContent, dirPath;
    size_t idx = std::string::npos;
    if (import.is_open()) {
      do {
        std::getline(import, temp);
        if ((idx = temp.find('|')) != std::string::npos) {
          // For root
          filePath = temp.substr(0, idx);
          temp.erase(0, idx + 1); // Cleaning the TEMP and extracting for content, +1 for including '|'
          // For content
          fileContent = temp.substr(temp.find_first_not_of(' '), temp.find_last_not_of(' ')); // Takes off whitespaces automatically
          fileContent.erase(fileContent.find_last_not_of(' ') + 1);
          idx = std::string::npos;
          if ((idx = filePath.find_first_not_of(' ')))
            filePath = filePath.erase(0, idx);
          idx = std::string::npos;
          if ((idx = filePath.find_last_of(' ')) < filePath.length())
            filePath.erase(filePath.find_last_not_of(' ') + 1, idx); // +1 to last letter
          addSrc(filePath, fileContent);
        } else {
          dirPath = temp.substr(0, temp.find_last_of('/') + 1); // +1 to include '/'
          addSrc(dirPath);
        }
      } while (import);
    }
    else { throw std::runtime_error("Cannot open file: " + filename); }
  }
  void Filesystem::addSrc(const std::string& path, const std::string& content) {
    Directory* current = m_root;
    std::string remainingPath = path;
    std::size_t found = remainingPath.find("/");
    while (found != std::string::npos) {
      std::string dirName = remainingPath.substr(0, found + 1);
      remainingPath = remainingPath.substr(found + 1);
      Directory* newDir = dynamic_cast<Directory*>(current->find(dirName));
      if (!newDir) {
        newDir = new Directory(dirName);
        *current += newDir;
      }
      current = newDir;
      found = remainingPath.find("/");
    }
    if (!content.empty() && !current->find(remainingPath))
      *current += new File(remainingPath.c_str(), content.c_str());
  }
  // Rule of Five
  Filesystem::Filesystem(Filesystem&& rhs) noexcept {
    *this = std::move(rhs);
  }
  Filesystem& Filesystem::operator=(Filesystem&& rhs) noexcept {
    if (this != &rhs) {
      delete m_root;
      m_root = rhs.m_root;
      m_current = rhs.m_current;
      rhs.m_root = rhs.m_current = nullptr;
    }
    return *this;
  }
  // adds a resource to the current directory.
  Filesystem& Filesystem::operator+=(Resource* rhs) {
    *m_current += rhs;
    return *this;
  }
  /* the parameter is optional (defaults to an empty string).
  if an empty string is passed, change the current directory to the root directory.
  if no directory with the specified name exists (useDirectory::find() to locate the directory), 
  report an std::invalid_argument exception with the message Cannot change directory! DIR_NAME not found!".
  changes the current directory to the directory (located in the current directory) 
  whose name matches argument. */
  Directory* Filesystem::change_directory(const std::string& chg) {
    if (chg.empty()) m_current = m_root;
    else {
      Resource* src = m_root->find(chg, {});
      if (src && src->type() == NodeType::DIR) m_current = static_cast<Directory*>(src);
      else throw std::invalid_argument("Cannot change directory! " + chg + " not found!");
    }
    return m_current;
  }
  // a query that returns the current directory.
  Directory* Filesystem::get_current_directory() const {
    return m_current;
  }
  Filesystem::~Filesystem() {
    delete m_root;
    m_root = m_current = nullptr;
  }
}