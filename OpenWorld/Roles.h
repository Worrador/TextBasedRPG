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
private:
    // Private constructor to prevent direct instantiation
    Roles();

    // Map of roles to vectors of ints with the role specific stats
    std::map<Role, std::vector<int>> roles;

public:
    // Delete copy constructor and assignment operator to prevent copying
    Roles(const Roles&) = delete;
    Roles& operator=(const Roles&) = delete;

    // Static method to return a reference to the single instance
    static Roles& getInstance()
    {
        static Roles instance;
        return instance;
    }

    // Method to access the roles map
    std::map<Role, std::vector<int>>& getRoles() { return roles; }
};