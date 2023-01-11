#pragma once
#include "libxl.h"
#include <sstream>
#include <vector>
#include <codecvt>
#include <functional>
#include "Role.h"

class RoleParser
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
    inline const int& getResourceError() { return resourceError; }
    inline std::vector<Role>& getParsedRoles() { return parsedRoles; }

private:
    // Private constructor to prevent direct instantiation
    RoleParser();
    ~RoleParser();

    int resourceError = 0;

    // String converter object
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

    void parseRoles();

    std::vector<Role> parsedRoles;
};

