#include "Item.h"
#include <cel/celfile.h>
#include <cel/celdatabase.h>

class ResourceParser
{
public:
    // Delete copy and move constructor and assignment operator to prevent copying
    ResourceParser(const ResourceParser&) = delete;
    ResourceParser(ResourceParser&&) = delete;
    ResourceParser& operator=(const ResourceParser&) = delete;
    ResourceParser& operator=(ResourceParser&&) = delete;

    // Static method to return a reference to the single instance
    static ResourceParser& getInstance()
    {
        // The change in C++11 has forced compilers to implement the construction of local 
        // static variables (like instance) in a thread-safe manner.
        static ResourceParser instance;
        return instance;
    }

    // Method to access the roleStats map
    std::map<Role, std::vector<int>>& getItem() { return RoleStats; }

    // Method to access the roleNames map
    std::map<Role, std::string>& getRoleNames() { return RoleNames; }

private:
    // Private constructor to prevent direct instantiation
    ResourceParser();

    std::vector<Item> parsedItems;
};