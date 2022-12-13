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

class Roles
{
public:
    // Delete copy and move constructor and assignment operator to prevent copying
    Roles(const Roles&) = delete;
    Roles(Roles&&) = delete;
    Roles& operator=(const Roles&) = delete;
    Roles& operator=(Roles&&) = delete;

    // Static method to return a reference to the single instance
    static Roles& getInstance()
    {
        //The change in C++11 has forced compilers to implement the construction of local 
        // static variables (like instance) in a thread-safe manner.
        static Roles instance;
        return instance;
    }

    // Method to access the roles map
    std::map<Role, std::vector<int>>& getRoles() { return roles; }
    
private:
    // Private constructor to prevent direct instantiation
    Roles();

    // Map of roles to vectors of ints with the role specific stats
    std::map<Role, std::vector<int>> roles;


};