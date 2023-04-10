#pragma once
#include <codecvt>

class IResourceParser
{
public:
    // Method to access the parsedItems vector
    inline const int& getResourceError() { return resourceError; }

protected:
    int resourceError = 0;

    // String converter object
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
};

