#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H
#include <iostream>
#include <string>
#include <fstream>
#include "File.h"
#include "Directory.h"

namespace seneca {
  class Filesystem {
    // a pointer to the root directory of the filesystem.
    Directory* m_root;
    // a pointer to the current working directory in the filesystem from where operations are performed.
    Directory* m_current;
    void addSrc(const std::string& path, const std::string& content = "");
  public:
    Filesystem();
    /* a custom constructor that receives the name of a file as its first argument, 
    and an optional string containing the name of the root directory (defaults to an empty string). */
    Filesystem(const std::string filename, const std::string rootname = "");
    // Rule of Three
    Filesystem(const Filesystem& rhs) = delete;
    Filesystem& operator=(const Filesystem& rhs) = delete;
    // Rule of Five
    Filesystem(Filesystem&& rhs) noexcept;
    Filesystem& operator=(Filesystem&& rhs) noexcept;

    // adds a resource to the current directory.
    Filesystem& operator+=(Resource* rhs);
    /* the parameter is optional (defaults to an empty string).
    if an empty string is passed, change the current directory to the root directory.
    if no directory with the specified name exists (useDirectory::find() to locate the directory), 
    report an std::invalid_argument exception with the message Cannot change directory! DIR_NAME not found!".
    changes the current directory to the directory (located in the current directory) 
    whose name matches argument. */
    Directory* change_directory(const std::string& chg = "");
    // a query that returns the current directory.
    Directory* get_current_directory() const;

    virtual ~Filesystem();
  };
}
#endif  // !SENECA_FILESYSTEM_H
