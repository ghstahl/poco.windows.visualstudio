// Poco.ThreadPool.Hang.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"
using namespace std;

class Worker : public Poco::Runnable
{
	static bool _shutDown;
public:
	Worker()
	{

	}
	void run()
	{
		thread::id this_id = this_thread::get_id();
		cout << "run. [Worker: tid:" << this_id << "]" << endl;
	}
};
int main()
{
	cout << "Hello World!\n";
	Worker worker1; // create worker threads
	Poco::ThreadPool::defaultPool().start(worker1);
	Poco::ThreadPool::defaultPool().joinAll();
	system("pause");
}

