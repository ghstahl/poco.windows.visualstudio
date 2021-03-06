// PocoThreadPlay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "Poco/Runnable.h"
#include "Poco/Thread.h"

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
		cout << "Start. [Worker: tid:" << this_id << "]" << endl;

		while (!_shutDown)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			cout << "Working. [Worker: tid:" << this_id << "]" << endl;

		}
		cout << "Leaving. [Worker: tid:" << this_id << "]" << endl;
	}
	static void Initialize() {
		_shutDown = false;
	}
	static void Shutdown() {
		_shutDown = true;
	}
};
bool Worker::_shutDown = false;
int main()
{
	Worker::Initialize();
    std::cout << "Hello World!\n"; 

	Worker worker1; // create worker threads
	Worker worker2;
	Worker::Shutdown();  // workers will come up, and then immediatly be told to go away

	Poco::Thread thread1;
	thread1.start(worker1);
	Poco::Thread thread2;
	thread2.start(worker2);

	thread1.join();	thread2.join();
	system("pause");
}

 