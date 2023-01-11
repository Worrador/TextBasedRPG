#pragma once
#include "libxl.h"
#include <sstream>
#include <vector>
#include <codecvt>
#include <functional>
#include "Settlement.h"

class SettlementParser
{
public:
    // Delete copy and move constructor and assignment operator to prevent copying
    SettlementParser(const SettlementParser&) = delete;
    SettlementParser(SettlementParser&&) = delete;
    SettlementParser& operator=(const SettlementParser&) = delete;
    SettlementParser& operator=(SettlementParser&&) = delete;

    // Static method to return a reference to the single instance
    static SettlementParser& getInstance()
    {
        // The change in C++11 has forced compilers to implement the construction of local 
        // static variables (like instance) in a thread-safe manner.
        static SettlementParser instance;
        return instance;
    }

    // Method to access the parsedItems vector
    inline const int& getResourceError() { return resourceError; }
    inline std::vector<Settlement>& getParsedSettlements() { return parsedSettlements; }
private:
    // Private constructor to prevent direct instantiation
    SettlementParser();
    ~SettlementParser();

    int resourceError = 0;

    // String converter object
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    void parseSettlements();
    std::vector<Settlement> parsedSettlements;
};

