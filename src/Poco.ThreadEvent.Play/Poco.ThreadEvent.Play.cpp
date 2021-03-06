// Poco.ThreadEvent.Play.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

class Worker : public Poco::Runnable
{
	Poco::Event _shutDown;
public:
	Worker()
	{

	}
	void run()
	{
		thread::id this_id = this_thread::get_id();
		cout << "run. [Worker: tid:" << this_id << "]" << endl;
		for (;;)
		{
			_shutDown.wait();
			cout << "_shutDown signaled. [Worker: tid:" << this_id << "]" << endl;
			break;
		}
	}
	void SignalShutDown()
	{
		_shutDown.set();
	}
};

class WorkerManager
{
private:
	Worker worker;
	Poco::Thread thread;
public:
	~WorkerManager()
	{
		worker.SignalShutDown();
		thread.join();
	}
	void Start()
	{
		thread.start(worker);
	}
};
int main()
{
    std::cout << "Hello World!\n";

	WorkerManager workerManager;

	workerManager.Start();
	system("pause");
}
