// PocoTaskManagerPlay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "MyThreadPoolSingletonHolder.h"
#include "ProgressHandler.h"
#include "SampleTask.h"

using Poco::Observer;




int main()
{
    std::cout << "Hello World!\n"; 
	try {
		MyThreadPoolSingletonHolder myThreadPoolSingletonHolder;
		Poco::ThreadPool* pool = myThreadPoolSingletonHolder.pool(Poco::ThreadPool::TAP_DEFAULT);

		Poco::TaskManager tm(*pool);
		ProgressHandler pm;
		tm.addObserver(
			Observer<ProgressHandler, Poco::TaskProgressNotification>
			(pm, &ProgressHandler::onProgress)
		);
		tm.addObserver(
			Observer<ProgressHandler, Poco::TaskFinishedNotification>
			(pm, &ProgressHandler::onFinished)
		);
		tm.start(new SampleTask("Task 1")); // tm takes ownership
		tm.start(new SampleTask("Task 2"));
		tm.joinAll();
	}
	catch (...) {

	}
	system("pause");
	return 0;
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
