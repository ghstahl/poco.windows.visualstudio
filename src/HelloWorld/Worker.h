#pragma once
#include "WorkNotification.h"
#include "Poco/Runnable.h"
#include "Poco/NotificationQueue.h"
#include "ThreadEventSource.h"

class Worker : public Poco::Runnable,
	public ThreadEventSource
{
public:
	Worker(Poco::NotificationQueue& queue) : _queue(queue) {}
	void run()
	{
		FireOnThreadStart();
		FireOnThreadReady();
		thread::id this_id = this_thread::get_id();
		ScopedCout scopedCout;
		scopedCout << "Worker: tid:" << this_id << endl;

		Poco::AutoPtr<Poco::Notification> pNf(_queue.waitDequeueNotification());
		while (pNf)
		{
			WorkNotification* pWorkNf =
				dynamic_cast<WorkNotification*>(pNf.get());
			if (pWorkNf)
			{
				ScopedCout scopedCout;
				scopedCout << "Worker: tid:" << this_id <<" Item:"<<pWorkNf->data() << endl;
				// do some work
			}
			pNf = _queue.waitDequeueNotification();
		}
		FireOnThreadEnd();
	}
private:
	Poco::NotificationQueue& _queue;
};
