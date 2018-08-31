#pragma once
#include "Poco/Notification.h"
class RunnableLifecycleNotification : public Poco::Notification
{

public:
	enum State
	{
		Unknown, Start, Ready, End
	};

	RunnableLifecycleNotification(State state)
	{
		m_data = state;
	}
	State data() const
	{
		return m_data;
	}

private:
	State	m_data;
};