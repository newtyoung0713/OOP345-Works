//*****************************************************************************
//  <assessment name example : Workshop - #6 (Part - 2>
//  Full Name   : Sheng-Lin Yang
//  Student ID# : 160443222
//    Email       : syang153@myseneca.ca
//    Section     : OOP345 NDD
//    Date        : June 02nd, 2024
//    Authenticity Declaration :
//  I have done all the coding by myself and only copied the code
//  that my professor provided to complete my workshops and assignments.
//*****************************************************************************
#include "Directory.h"

namespace seneca {
  /* Note: assume all directory names end with a /.
  a custom constructor that receives the name of the directory 
  as a string and uses it to initialize the Directory object. */
  Directory::Directory(const std::string rhs) {
    m_name = rhs;
  }
  /* sets the parent path to the parameter. For each resource that this directory holds, 
  this member should also set their absolute path locations to the full absolute path of this directory.*/
  void Directory::update_parent_path(const std::string& path) {
    m_parent_path = path;
  }
  // a query that returns Flags::DIR.
  NodeType Directory::type() const {
    return NodeType::DIR;
  }
  /* a query that returns the full absolute path of the directory 
  (a concatenation of the absolute path location and the directory name).*/ 
  std::string Directory::path() const {
    return m_parent_path + m_name;
  }
  // a query that returns the name of the directory.
  std::string Directory::name() const {
    return m_name;
  }
  // a query that returns the number of resources that this directory holds.
  int Directory::count() const {
    return static_cast<int>(m_contents.size());
  }
  /* a query that returns the size of the directory in bytes. 
  The size of the directory is the sum of the individual sizes of each resource that this directory holds. 
  This member returns 0u if the directory is empty.*/
  size_t Directory::size() const {
    size_t sum{0};
    for (const auto& src : m_contents) sum += src->size();
    return sum;
  }
  /* adds a resource to the directory and returns a reference to the current directory. 
  This member should check for existing resources in the directory with the same name:
  if a match is found, throw and exception and do nothing else;
  if no match is found, add the resource 
  and update the absolute path location of the added resource 
  with the directory's full absolute path. */
  Directory& Directory::operator+=(Resource* rhs) {
    for (const auto& src : m_contents)
      if (src->name() == rhs->name())
        throw std::runtime_error("Error");
    m_contents.push_back(rhs);
    rhs->update_parent_path(this->path());
    return *this;
  }
  /* finds and returns the address of a resource in the directory 
  whose name matches the given string or nullptr if a match is not found. 
  This member also takes an optional vector of flags 
  that determine how the find is performed (defaults to an empty collection).
  if the RECURSIVE flag is in the second parameter, 
  this member will also attempt to recursively find a match in each directory 
  that is in the m_contents vector. 
  HINT: If an element in m_contents is a directory, use its find() member function to find a match.
  NOTE: If the current directory holds another directory named src which contains a file named sample.txt 
  and we want to find sample.txt, this member will only return the sample.txt resource 
  if the RECURSIVE flag is set, nullptr otherwise. */
  Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag) {
    // finds and returns the address of a resource in the directory whose name matches the given string
    for (const auto& src : m_contents) {
      if (src->name() == name) return src;
      // HINT: If an element in m_contents is a directory, use its find() member function to find a match.
      if ((std::find(flag.begin(), flag.end(), OpFlags::RECURSIVE) != flag.end()) && 
          // if the RECURSIVE flag is set, nullptr otherwise.
          (src->type() == NodeType::DIR)) {
        Resource* unAutre = static_cast<Directory*>(src)->find(name, flag);
        if (unAutre) return unAutre;
      }
    }
    return nullptr; // if a match is not found.
  }
  // a destructor that deallocates memory for each resource that this directory holds.
  Directory::~Directory() {
    for (auto& src : m_contents) delete src;
  }
}