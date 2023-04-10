#include "ExcelHandler.h"


ExcelHandler::ExcelHandler(const wchar_t* resName) : book(xlCreateXMLBook())
{
    book->load(resName);
    /*
    try {
        book->load(resName);
    }
    catch (...) {
        if (book) {
            book->release();
        }
        throw;
    }*/
}

ExcelHandler::~ExcelHandler()
{
    if (book) {
        book->release();
    }
}
