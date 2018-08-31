#pragma once
#include <ostream>
#include "Poco/ErrorHandler.h"
class MyErrorHandler : public Poco::ErrorHandler
{
public:
	void exception(const Poco::Exception& exc)
	{
		ScopedCout scopedCout;
		scopedCout << exc.displayText() << std::endl;
	}
	void exception(const std::exception& exc)
	{
		ScopedCout scopedCout;
		scopedCout << exc.what() << std::endl;

	}
	void exception()
	{
		ScopedCout scopedCout;
		scopedCout << "unknown exception" << std::endl;
	}
};
