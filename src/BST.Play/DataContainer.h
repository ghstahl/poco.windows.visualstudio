#pragma once
#include "DataContainerBase.h"
template <typename TData>
class DataContainer :
	public DataContainerBase<
	TData, 
	DataContainer<TData>>
{
public:
	std::shared_ptr<TData> DataPtr;
	int Count;

	DataContainer()
	{
		Count = 0;
	}
	DataContainer(std::shared_ptr<TData> dataPtr)
	{
		DataPtr = dataPtr;
		Count = 1;
	}

	virtual void InitialSetData(std::shared_ptr<TData> dataPtr)
	{
		DataPtr = dataPtr;
		Count = 1;
	}
	virtual void InjestDuplicate(std::shared_ptr<TData> dataPtr)
	{
		if (*dataPtr != *DataPtr)
		{
			throw "DataPtr's do not match!";
		}
		++Count;
	}


	bool operator== (const DataContainer &c2)
	{
		return (*(DataPtr) == *(c2.DataPtr));
	}
	bool operator!= (const DataContainer &c2)
	{
		return (*(DataPtr) != *(c2.DataPtr));
	}
	bool operator> (const DataContainer &c2)
	{
		return (*(DataPtr) > *(c2.DataPtr));
	}
	bool operator< (const DataContainer &c2)
	{
		return (*(DataPtr) < *(c2.DataPtr));
	}
};
