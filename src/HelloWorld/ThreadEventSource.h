#pragma once
#include "EventSourceT.h"
#include "ThreadEventSink.h"

class ThreadEventSource : public EventSourceT<ThreadEventSink>
{
protected:
	void FireOnThreadStart()
	{
		for (size_t i = 0; i < _eventSinks.size(); ++i)
		{
			_eventSinks[i]->OnThreadStart();
		}
	}
	void FireOnThreadReady()
	{
		for (size_t i = 0; i < _eventSinks.size(); ++i)
		{
			_eventSinks[i]->OnThreadReady();
		}
	}
	void FireOnThreadEnd()
	{
		for (size_t i = 0; i < _eventSinks.size(); ++i)
		{
			_eventSinks[i]->OnThreadEnd();
		}
	}
};
