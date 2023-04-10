#pragma once
#include <sstream>
#include <vector>
#include <functional>
#include "Role.h"
#include "IResourceParser.h"
#include "ExcelHandler.h"

class RoleParser : public IResourceParser
{
public:
    // Delete copy and move constructor and assignment operator to prevent copying
    RoleParser(const RoleParser&) = delete;
    RoleParser(RoleParser&&) = delete;
    RoleParser& operator=(const RoleParser&) = delete;
    RoleParser& operator=(RoleParser&&) = delete;

    // Static method to return a reference to the single instance
    static RoleParser& getInstance()
    {
        // The change in C++11 has forced compilers to implement the construction of local 
        // static variables (like instance) in a thread-safe manner.
        static RoleParser instance;
        return instance;
    }

    // Method to access the parsedItems vector
    inline std::vector<Role>& getParsedRoles() { return parsedRoles; }

private:
    // Private constructor to prevent direct instantiation
    RoleParser();
    ~RoleParser();

    void parseRoles();

    std::vector<Role> parsedRoles;
};

