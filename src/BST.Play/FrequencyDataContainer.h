#pragma once
#include "DataContainer.h"
#include "BSTNode.h"

template <typename TData>
class FrequencyDataPrimitive
{
public:
	FrequencyDataPrimitive() 
	{
		Count = 0;
	}
	FrequencyDataPrimitive(std::shared_ptr<TData> dataPtr, int count)
	{
		this->Count = count;
		DataPtr = dataPtr;
	}
	int Count;
	std::shared_ptr<TData> DataPtr; // this is the frequency

};

template <typename TData>
class FrequencyDataContainer :
	public DataContainerBase<
	FrequencyDataPrimitive<TData>,
	FrequencyDataContainer<TData>>
{
public:
	int Count;
	std::shared_ptr<BSTNode<TData, DataContainer<TData>>> RootNode;
	std::shared_ptr<int> DataPtr; // this is the frequency

	FrequencyDataContainer()
	{
		Count = 0;
	}
	FrequencyDataContainer(std::shared_ptr<FrequencyDataPrimitive<TData>> dataPtr)
	{
		InitialSetData(dataPtr);
	}

	virtual void InitialSetData(std::shared_ptr<FrequencyDataPrimitive<TData>> dataPtr)
	{
		Count = 1;
		DataPtr = std::make_shared<int>(dataPtr->Count);
		RootNode = std::make_shared<BSTNode<TData, DataContainer<TData>>>(dataPtr->DataPtr);
	}
	virtual void InjestDuplicate(std::shared_ptr<FrequencyDataPrimitive<TData>> dataPtr)
	{
		if ((*dataPtr).Count != *DataPtr)
		{
			throw "Count's do not match!";
		}
		RootNode->RecursiveInsert(dataPtr->DataPtr);
		++Count;
	}


	bool operator== (const FrequencyDataContainer &c2)
	{
		return (*(DataPtr) == *(c2.DataPtr));
	}
	bool operator!= (const FrequencyDataContainer &c2)
	{
		return (*(DataPtr) != *(c2.DataPtr));
	}
	bool operator> (const FrequencyDataContainer &c2)
	{
		return (*(DataPtr) > *(c2.DataPtr));
	}
	bool operator< (const FrequencyDataContainer &c2)
	{
		return (*(DataPtr) < *(c2.DataPtr));
	}
};
