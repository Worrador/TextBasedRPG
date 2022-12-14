#pragma once
#include <map>
#include <vector>

enum class Role {
    Warrior = 0,
    Mage,
    Rouge,
    Ranger,
    Acolyte
};

class RoleStats
{
public:
    // Delete copy and move constructor and assignment operator to prevent copying
    RoleStats(const RoleStats&) = delete;
    RoleStats(RoleStats&&) = delete;
    RoleStats& operator=(const RoleStats&) = delete;
    RoleStats& operator=(RoleStats&&) = delete;

    // Static method to return a reference to the single instance
    static RoleStats& getInstance()
    {
        //The change in C++11 has forced compilers to implement the construction of local 
        // static variables (like instance) in a thread-safe manner.
        static RoleStats instance;
        return instance;
    }

    // Method to access the roles map
    std::map<Role, std::vector<int>>& getRoleStats() { return roles; }
    
private:
    // Private constructor to prevent direct instantiation
    RoleStats();

    // Map of roles to vectors of ints with the role specific stats
    std::map<Role, std::vector<int>> roles;


};