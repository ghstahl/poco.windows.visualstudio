#pragma once

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include <sstream>

extern Poco::FastMutex g_fastMutexCriticalCout;
class ScopedCout
{
public:
	ScopedCout& operator<<(const char *_Val)
	{
		// write obj to stream
		_ss << _Val;
		return *this;
	}
	ScopedCout& operator<<(long long _Val)
	{
		// write obj to stream
		_ss << _Val;
		return *this;
	}
	template<class _Elem,
		class _Traits,
		class _Alloc>
	ScopedCout& operator<<(const std::basic_string<_Elem, _Traits, _Alloc>& _Str)
	{
		// write obj to stream
		_ss << _Str;
		return *this;
	}
	ScopedCout& operator<<(std::thread::id _Id)
	{
		// write obj to stream
		_ss << _Id;
		return *this;
	}

	
	ScopedCout& operator<<(std::ostream&(*_Pfn)(std::ostream&))
	{
		if (_Pfn == std::endl)
		{
			Poco::FastMutex::ScopedLock lock(g_fastMutexCriticalCout);
			std::cout << _ss.str() << std::endl;
			_ss.clear();
		}
		return *this;
	}
private:
	std::stringstream _ss;
	Poco::FastMutex _fastMutex;
};



