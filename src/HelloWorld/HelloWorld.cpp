// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"


#include <iostream>
#include <sstream>
#include <thread>
#include "EventSourceT.h"
#include "MyErrorHandler.h"
#include "ScopedCout.h"
#include "Worker.h"
#include "ThreadEventSink.h"
#include "ThreadEventSource.h"
#include "RunnableLifecycleNotification.h"
using namespace std;

using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;
using Poco::Stopwatch;



class TimerExample {
public:
	TimerExample() { _sw.start(); }
	void onTimer(Timer& timer) {
		std::thread::id this_id = std::this_thread::get_id();
		ScopedCout scopedCout;
		scopedCout << "Callback called after " << _sw.elapsed() / 1000 << " milliseconds." << std::endl;
	}
private:
	Stopwatch _sw;
};






class HelloRunnable :
	public Poco::Runnable,
	public ThreadEventSource
{
	virtual void run()
	{
		FireOnThreadStart();
		FireOnThreadReady();
		ScopedCout scopedCout;
		scopedCout << "Hello, world!" << std::endl;
		FireOnThreadEnd();
	}
};
class Greeter
{
public:
	void greet()
	{
		ScopedCout scopedCout;
		scopedCout << "Welcome to my store!" << std::endl;
	}
};class Offender : public Poco::Runnable
{
	void run()
	{
		throw Poco::ApplicationException("got you");
	}
};


class RunnableLifecycleNotificationTarget
{
public:

	void HandleNotificationByReference(const Poco::AutoPtr<RunnableLifecycleNotification>& pNf)
	{
		ScopedCout scopedCout;
		std::thread::id this_id = std::this_thread::get_id();
		scopedCout << "OnTreadEnd: tid:" << this_id << "    :" << std::endl;
		scopedCout << "HandleNotificationByReference: " << pNf->name() <<" "<< pNf->data() <<std::endl;
	}
	
};

class BaseNotification : public Poco::Notification
{
};
class SubNotification : public BaseNotification
{
};
class Target
{
public:
	void handleBase(BaseNotification* pNf)
	{
		ScopedCout scopedCout;
		scopedCout << "handleBase: " << pNf->name() << std::endl;
		pNf->release(); // we got ownership, so we must release
	}
	void handleSub(const Poco::AutoPtr<SubNotification>& pNf)
	{
		ScopedCout scopedCout;
		scopedCout << "handleSub: " << pNf->name() << std::endl;
	}
};
Poco::FastMutex g_fastMutexCriticalCout;
Poco::NotificationCenter g_NotificationCenter;
int main()
{
	shared_ptr<ThreadEventSink> threadSinkPtr = make_shared<ThreadEventSink>();
	Poco::NotificationQueue queue;
	Worker worker1(g_NotificationCenter,queue); // create worker threads
	Worker worker2(g_NotificationCenter,queue);
	worker1.RegisterEventSink(threadSinkPtr);
	worker2.RegisterEventSink(threadSinkPtr);

	Target target;

	RunnableLifecycleNotificationTarget runnableLifecycleNotificationTarget;
	g_NotificationCenter.addObserver(
		Poco::NObserver<RunnableLifecycleNotificationTarget, RunnableLifecycleNotification>(runnableLifecycleNotificationTarget, &RunnableLifecycleNotificationTarget::HandleNotificationByReference)
	);


	g_NotificationCenter.addObserver(
		Poco::Observer<Target, BaseNotification>(target, &Target::handleBase)
	);
	g_NotificationCenter.addObserver(
		Poco::NObserver<Target, SubNotification>(target, &Target::handleSub)
	);
	g_NotificationCenter.postNotification(new BaseNotification);
	g_NotificationCenter.postNotification(new SubNotification);
	g_NotificationCenter.removeObserver(
		Poco::Observer<Target, BaseNotification>(target, &Target::handleBase)
	);
	g_NotificationCenter.removeObserver(
		Poco::NObserver<Target, SubNotification>(target, &Target::handleSub)
	);
	ScopedCout scopedCout;
	scopedCout << "Hi from Main!" << endl;

	MyErrorHandler eh;
	Poco::ErrorHandler* pOldEH = Poco::ErrorHandler::set(&eh);


	HelloRunnable runnableHello;
	runnableHello.RegisterEventSink(threadSinkPtr);

	Offender runnableOffender;
	Greeter greeter;
	Poco::RunnableAdapter<Greeter> runnableGreeter(greeter, &Greeter::greet);
	
	Poco::Thread standAloneThread;
	standAloneThread.start(runnableHello);
	standAloneThread.join();

	// create some work
	for (int i = 0; i < 10; ++i)
	{
		queue.enqueueNotification(new WorkNotification(i));
	}

	Poco::ThreadPool::defaultPool().start(runnableGreeter);
	Poco::ThreadPool::defaultPool().start(runnableHello);
	Poco::ThreadPool::defaultPool().start(runnableOffender);
	Poco::ThreadPool::defaultPool().start(worker1);
	Poco::ThreadPool::defaultPool().start(worker2);


	while (!queue.empty()) // wait until all work is done
		Poco::Thread::sleep(100);
	queue.wakeUpAll(); // tell workers they're done
	Poco::ThreadPool::defaultPool().joinAll();

	runnableHello.UnregisterAllSinks();
	TimerExample example;
	Timer timer(250, 500);
	timer.start(TimerCallback<TimerExample>(example, &TimerExample::onTimer));

	Thread::sleep(1000);
	timer.stop();

	std::string s = "correct@email.com", s2 = "bademail";


	///system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
