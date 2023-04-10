#pragma once
#include "libxl.h"


// LESSON: RAII wrapper for handling lixl file
class ExcelHandler
{
public:
	ExcelHandler(const wchar_t* resName);
	~ExcelHandler();
	inline libxl::Book* getBook() { return book; };
private:
	libxl::Book* book;
};

