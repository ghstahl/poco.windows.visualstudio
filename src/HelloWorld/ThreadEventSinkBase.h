#pragma once
class ThreadEventSinkBase
{
public:
public:
	ThreadEventSinkBase() {}
	virtual ~ThreadEventSinkBase() {}

public:
	virtual void OnThreadStart() = 0;
	virtual void OnThreadReady() = 0;
	virtual void OnThreadEnd() = 0;
};


