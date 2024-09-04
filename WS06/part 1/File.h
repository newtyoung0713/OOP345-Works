#ifndef SENECA_FILE_H
#define SENECA_FILE_H
#include <iostream>
#include <string>
#include "Flags.h"
#include "Resource.h"

namespace seneca {
  class File : public Resource {
    std::string m_contents{};
  public:
    File() = default;
    /* a custom constructor that receives two strings as parameters:
    the name of the file
    a text representation of the contents of a file (optional, with empty string as a default value). */
    File(const std::string filename, const std::string content = "");

    // Rule of Three
    File(const File& rhs) = delete;
    File& operator=(const File& rhs) = delete;
    // Rule of Five
    File(File&& rhs) noexcept = delete;
    File& operator=(File&& rhs) noexcept = delete;

    virtual ~File() = default;
    
    // sets the parent path to the parameter.
    void update_parent_path(const std::string& path) override;
    // a query that returns Flags::FILE.
    NodeType type() const override;
    /* a query that returns the full absolute path of the file 
    (concatenates the absolute path location and the file name).*/
    std::string path() const override;
    // a query that returns the name of the file.
    std::string name() const override;
    // a query that returns -1.
    int count() const override;
    /* a query that returns the size of the file in bytes. 
    For simplicity, this is the number of characters in m_contents attribute.*/
    size_t size() const override;
  };
}
#endif  // !SENECA_FILE_H
