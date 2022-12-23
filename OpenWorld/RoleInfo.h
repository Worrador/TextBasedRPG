#pragma once
#include <map>
#include <vector>
#include <string>
#include <cmath>

using Role = std::string;

class RoleInfo
{
public:
    // Delete copy and move constructor and assignment operator to prevent copying
    RoleInfo(const RoleInfo&) = delete;
    RoleInfo(RoleInfo&&) = delete;
    RoleInfo& operator=(const RoleInfo&) = delete;
    RoleInfo& operator=(RoleInfo&&) = delete;

    // Static method to return a reference to the single instance
    static RoleInfo& getInstance()
    {
        // The change in C++11 has forced compilers to implement the construction of local 
        // static variables (like instance) in a thread-safe manner.
        static RoleInfo instance;
        return instance;
    }

    // Method to access the roleStats map
    std::map<Role, std::vector<int>>& getRoleStats() { return RoleStats; }

    // Method to access the roleNames map
    std::map<Role, std::string>& getRoleNames() { return RoleNames; }
    
private:
    // Private constructor to prevent direct instantiation
    RoleInfo();

    // Map of roles to vectors of ints with the role specific stats
    std::map<Role, std::vector<int>> RoleStats;
    std::map<Role, std::string> RoleNames;
};