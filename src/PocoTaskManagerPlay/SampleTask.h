#pragma once
#include "Poco/Task.h"
class SampleTask : public Poco::Task
{
public:
	SampleTask(const std::string& name) : Task(name)
	{
	}
	void runTask()
	{
		for (int i = 0; i < 2; ++i)
		{
			setProgress(float(i) / 100); // report progress
			if (sleep(1000))
				break;
		}
	}
};
