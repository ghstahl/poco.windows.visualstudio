#pragma once
#include <type_traits>
#include <vector>

#include "DataContainerBase.h"

template<class T, class TDataContainter>
class BSTNode
{
 
public:
	BSTNode *pParentNode;
	std::shared_ptr<BSTNode> LeftNodePtr;
	std::shared_ptr<BSTNode> RightNodePtr;
	std::shared_ptr<TDataContainter> DataContainerPtr;
	BSTNode()
	{
		static_assert(std::is_base_of<DataContainerBase<T, TDataContainter>, TDataContainter>::value, "type parameter of this class must derive from BaseClass");
		pParentNode = nullptr;
	}
	BSTNode(std::shared_ptr<T> data):
		BSTNode()
	{
		DataContainerPtr =
			std::make_shared<TDataContainter>(data);

	}
	void RecursiveInsert(std::shared_ptr<T> data)
	{
		std::shared_ptr<TDataContainter> incommingContainerPtr =
			std::make_shared<TDataContainter>(data);

		TDataContainter incomming = *(incommingContainerPtr);
		TDataContainter current = *(DataContainerPtr);
		if (incomming == current)
		{
			DataContainerPtr->InjestDuplicate(data);
		}
		else
		{
			if (incomming < current)
			{
				// go left
				if (LeftNodePtr.get() == nullptr)
				{
					LeftNodePtr = std::make_shared<BSTNode<T, TDataContainter>>(data);
					LeftNodePtr->pParentNode = this;
				}
				else
				{
					LeftNodePtr->RecursiveInsert(data);
				}
			}
			else
			{
				// go right
				if (RightNodePtr.get() == nullptr)
				{
					RightNodePtr = std::make_shared<BSTNode<T, TDataContainter>>(data);
					RightNodePtr->pParentNode = this;
				}
				else
				{
					RightNodePtr->RecursiveInsert(data);
				}
			}
		}
	}
	template<class _Fn>
	void SortMostLeft(std::vector<TDataContainter> &sorted, _Fn _Func)
	{
		if (LeftNodePtr.get() == nullptr)
		{
			_Func(sorted, *DataContainerPtr);
		 
		}
		else
		{
			LeftNodePtr->SortMostLeft(sorted, _Func);
			_Func(sorted, *DataContainerPtr);
	 
		}
		if (RightNodePtr.get() != nullptr)
		{
			RightNodePtr->SortMostLeft(sorted, _Func);
		}
	}

	void SortMostRight(std::vector<TDataContainter> &sorted)
	{
		if (RightNodePtr.get() == nullptr)
		{
			
			_Func(sorted, *DataContainerPtr);
		}
		else
		{
			RightNodePtr->SortMostRight(sorted);
			_Func(sorted, *DataContainerPtr);
		}
		if (LeftNodePtr.get() != nullptr)
		{
			LeftNodePtr->SortMostRight(sorted);
		}
	}

	 

}; // primary template

 