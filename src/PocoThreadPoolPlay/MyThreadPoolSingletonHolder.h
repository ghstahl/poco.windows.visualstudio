#pragma once
#include "Poco/ThreadPool.h"
class MyThreadPoolSingletonHolder
{
public:
	MyThreadPoolSingletonHolder()
	{
		_pPool = 0;
	}

	~MyThreadPoolSingletonHolder()
	{
		delete _pPool;
	}

	Poco::ThreadPool* pool(Poco::ThreadPool::ThreadAffinityPolicy affinityPolicy = Poco::ThreadPool::TAP_DEFAULT)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		if (!_pPool)
		{
			_pPool = new Poco::ThreadPool("default");
			_pPool->setAffinityPolicy(affinityPolicy);
#if (POCO_THREAD_STACK_SIZE > 0)
			_pPool->setStackSize(POCO_THREAD_STACK_SIZE);
#endif
		}
		return _pPool;
	}

private:
	Poco::ThreadPool* _pPool;
	Poco::FastMutex   _mutex;
};
