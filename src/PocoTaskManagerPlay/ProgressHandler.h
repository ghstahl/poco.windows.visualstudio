#pragma once
#include "Poco/TaskNotification.h"
class ProgressHandler
{
public:
	void onProgress(Poco::TaskProgressNotification* pNf)
	{
		std::cout << pNf->task()->name()
			<< " progress: " << pNf->progress() << std::endl;
		pNf->release();
	}
	void onFinished(Poco::TaskFinishedNotification* pNf)
	{
		std::cout << pNf->task()->name() << " finished." << std::endl;
		pNf->release();
	}
};

