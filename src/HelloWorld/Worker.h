#pragma once
#include "WorkNotification.h"
#include "Poco/Runnable.h"
#include "Poco/NotificationQueue.h"
#include "ThreadEventSource.h"
#include "RunnableLifecycleNotification.h"

class Worker : public Poco::Runnable,
	public ThreadEventSource
{
public:
	Worker(Poco::NotificationCenter& notification_center, Poco::NotificationQueue& queue) :
		_notification_center(notification_center),
		_queue(queue)
	{

	}
	void run()
	{
		g_NotificationCenter.postNotification(new RunnableLifecycleNotification(RunnableLifecycleNotification::State::Start));
		g_NotificationCenter.postNotification(new RunnableLifecycleNotification(RunnableLifecycleNotification::State::Ready));
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
				scopedCout << "Worker: tid:" << this_id << " Item:" << pWorkNf->data() << endl;
				// do some work
			}
			pNf = _queue.waitDequeueNotification();
		}
		FireOnThreadEnd();
		g_NotificationCenter.postNotification(new RunnableLifecycleNotification(RunnableLifecycleNotification::State::End));
	}
private:
	Poco::NotificationCenter& _notification_center;
	Poco::NotificationQueue& _queue;
};
