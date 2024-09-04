#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Flags.h"
#include "Resource.h"

namespace seneca {
  class Directory : public Resource{
    /* m_contents: an object of type std::vector that holds pointers to Resource objects. 
    Each element of the vector can either be a Directory or a File. */
    std::vector<Resource*> m_contents{};
  public:
    Directory() = default;
    /* Note: assume all directory names end with a /.
    a custom constructor that receives the name of the directory 
    as a string and uses it to initialize the Directory object. */
    Directory(const std::string rhs = "/");
    /* sets the parent path to the parameter. For each resource that this directory holds, 
    this member should also set their absolute path locations to the full absolute path of this directory.*/
    void update_parent_path(const std::string& path) override;
    // a query that returns Flags::DIR.
    NodeType type() const override;
    /* a query that returns the full absolute path of the directory 
    (a concatenation of the absolute path location and the directory name).*/ 
    std::string path() const override;
    // a query that returns the name of the directory.
    std::string name() const override;
    // a query that returns the number of resources that this directory holds.
    int count() const override;
    /* a query that returns the size of the directory in bytes. 
    The size of the directory is the sum of the individual sizes of each resource that this directory holds. 
    This member returns 0u if the directory is empty.*/
    size_t size() const override;
    /* adds a resource to the directory and returns a reference to the current directory. 
    This member should check for existing resources in the directory with the same name:
    if a match is found, throw and exception and do nothing else;
    if no match is found, add the resource 
    and update the absolute path location of the added resource 
    with the directory's full absolute path. */
    Directory& operator+=(Resource* rhs);
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
    Resource* find(const std::string& name, const std::vector<OpFlags>& flag = {});
    // this class should not allow copy/move operations.
    // Rule of Three
    Directory(const Directory& rhs) = delete;
    Directory& operator=(const Directory& rhs) = delete;
    // Rule of Five
    Directory(Directory&& rhs) noexcept = delete;
    Directory& operator=(Directory&& rhs) noexcept = delete;

    // Part-2
    /* deletes a resource from the directory 
    whose name matches the first argument 
    (removing it from its contents and deallocating memory for it). */
    void remove(const std::string& rm, const std::vector<OpFlags>& flag = {});
    /* First inserts Total size: XX bytes 
    and a newline into the output stream where XX is the size of the directory.
    For each resource in the directory, 
    first add F or D to the output stream based on the resource type, 
    then add the resource information to the output stream in the following format: */
    void display(std::ostream& os = std::cout, const std::vector<FormatFlags>& flag = {}) const;

    // a destructor that deallocates memory for each resource that this directory holds.
    ~Directory() override;
  };
}
#endif  // !SENECA_DIRECTORY_H
