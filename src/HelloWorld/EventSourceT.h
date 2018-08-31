#pragma once
#include <vector>
using namespace std;
template <class T>
class EventSourceT
{
protected:
	vector<shared_ptr<T>> _eventSinks;

public:
	EventSourceT()
	{
		// Compile-time check
		//static_assert(std::is_base_of<BaseClass, T>::value, "type parameter of this class must derive from BaseClass");
	}
	virtual ~EventSourceT(){}
	void RegisterEventSink(shared_ptr<T> sink)
	{
		for (size_t i = 0; i < _eventSinks.size(); ++i)
		{
			shared_ptr<T> sinkPtr = _eventSinks[i];
			if (sinkPtr.get() == sink.get())
			{
				return;
				// already registered
			}
		}
		_eventSinks.push_back(sink);
	}
	void UnregisterAllSinks()
	{
		_eventSinks.clear();
	}
	void UnregisterEventSink(shared_ptr<T> sink)
	{
		typename vector<shared_ptr<T>>::iterator sinkIterator = _eventSinks.begin();
		while (sinkIterator != _eventSinks.end())
		{
			shared_ptr<T> sinkPtr = *sinkIterator;
			if (sinkPtr.get() == sink.get())
			{
				_eventSinks.erase(sinkIterator);
				break;
			}
			++sinkIterator;
		}
	}
};
