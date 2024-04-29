#pragma once
#include <codecvt>


// LESSON: Interface classes are pure abstract classes, that need at least one pure virtual function ( =0)
// Also, a virtual destructor should be defined:This allows you to pass pointer ownership to another party without exposing the concrete derived class. The destructor doesn't have to do anything, because the interface doesn't have any concrete members. 
// It might seem contradictory to define a function as both virtual and inline, but trust me - it isn't.
// https://stackoverflow.com/questions/318064/how-do-you-declare-an-interface-in-c
class IResourceParser
{
public:
    // Method to access the parsedItems vector
    [[nodiscard]] int getResourceError() { return resourceError; }
    virtual ~IResourceParser() {}

protected:
    int resourceError{};

    // String converter object
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
};

