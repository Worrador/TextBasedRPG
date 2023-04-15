#pragma once
#include <codecvt>

class IResourceParser
{
public:
    // Method to access the parsedItems vector
    int getResourceError() { return resourceError; }

protected:
    int resourceError{};

    // String converter object
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
};

