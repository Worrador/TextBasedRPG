#include "Item.h"
#include "libxl.h"

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

    // Method to access the parsedItems vector
    std::vector<Item>& getParsedItems() { return parsedItems; }

private:
    // Private constructor to prevent direct instantiation
    ResourceParser();
    ~ResourceParser();

    std::vector<Item> parsedItems;
};