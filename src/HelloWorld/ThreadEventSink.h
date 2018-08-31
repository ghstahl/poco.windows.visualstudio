#pragma once
#include <thread>
#include "ThreadEventSinkBase.h"
#include "ScopedCout.h"

class ThreadEventSink : public ThreadEventSinkBase
{
public:
	void OnThreadStart()
	{
		std::thread::id this_id = std::this_thread::get_id();
		ScopedCout scopedCout;
		scopedCout << "OnTreadStart: tid:" << this_id << std::endl;

	};
	void OnThreadReady()
	{
		std::thread::id this_id = std::this_thread::get_id();
		ScopedCout scopedCout;
		scopedCout << "OnTreadReady: tid:" << this_id << std::endl;
	};
	void OnThreadEnd()
	{
		std::thread::id this_id = std::this_thread::get_id();
		ScopedCout scopedCout;
		scopedCout << "OnTreadEnd: tid:" << this_id << std::endl;
	};
};
