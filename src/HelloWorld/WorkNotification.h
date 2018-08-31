#pragma once
#include "Poco/Notification.h"
class WorkNotification : public Poco::Notification
{
public:
	WorkNotification(int data) : _data(data) {}
	int data() const
	{
		return _data;
	}
private:
	int _data;
};