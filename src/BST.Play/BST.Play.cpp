// BST.Play.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "BSTNode.h"
#include <functional>
#include <random>
#include "DataContainer.h"
#include "FrequencyDataContainer.h"


void myFequencyDataPrimitivePrintfunction(FrequencyDataPrimitive<int> dc)
{ // function:
	std::cout << " [" << *(dc.DataPtr) << ".." << dc.Count << "]";
}
void myfunction(DataContainer<int> dc)
{ // function:
	std::cout << " [" << *(dc.DataPtr) << ".." << dc.Count << "]";
}
void myVectorInsert(std::vector<DataContainer<int>> &sorted,DataContainer<int> dc)
{ // function:
	DataContainer<int> myDC(dc.DataPtr);
	for (int i = 0; i < dc.Count; ++i)
	{
		sorted.push_back(myDC);
	}
}
void myDuplicateAwareVectorInsert(std::vector<DataContainer<int>> &sorted, DataContainer<int> dc)
{ // function:
	sorted.push_back(dc);
}
void myFrequencyVectorInsert(std::vector<FrequencyDataContainer<int>> &sorted, FrequencyDataContainer<int> dc)
{ // function:
	sorted.push_back(dc);
	/*
	std::vector<DataContainer<int>> sortedInternal;
	dc.RootNode->SortMostLeft(sortedInternal, myDuplicateAwareVectorInsert);
	int frequency = *dc.DataPtr;
	for(int i = 0; i<sortedInternal.size();++i)
	{
	std::shared_ptr<FrequencyDataPrimitive<int>> freqPtr
	= std::make_shared < FrequencyDataPrimitive<int>>(sortedInternal[i].DataPtr, frequency);
	sorted.push_back(freqPtr);
	}

	 */

}
 
int main()
{
	std::cout << "Hello World!\n";

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 10);
	auto dice = std::bind(distribution, generator);

	std::shared_ptr<int> rand =
		std::make_shared<int>(dice());

	std::shared_ptr<BSTNode<int, DataContainer<int>>> rootNode =
		std::make_shared<BSTNode<int, DataContainer<int>>>(rand);

	for (int i = 0; i < 100; ++i)
	{
		int roll = dice();

		std::shared_ptr<int> rand =
			std::make_shared<int>(dice());
		rootNode->RecursiveInsert(rand);

		if (roll != 5)
		{
			std::shared_ptr<int> dup =
				std::make_shared<int>(5);
			rootNode->RecursiveInsert(dup);
		}
	}
	std::vector<DataContainer<int>> sorted;


	sorted.clear();
	rootNode->SortMostLeft(sorted, myVectorInsert);
	std::for_each(sorted.begin(), sorted.end(), myfunction);
	std::cout << std::endl;

	sorted.clear();
	rootNode->SortMostLeft(sorted, myDuplicateAwareVectorInsert);
	std::for_each(sorted.begin(), sorted.end(), myfunction);
	std::cout << std::endl;

	DataContainer<int> currentSorted = sorted[0];
	std::shared_ptr<FrequencyDataPrimitive<int>> freqPtr
		= std::make_shared < FrequencyDataPrimitive<int>>(
			currentSorted.DataPtr,
			currentSorted.Count);

	std::shared_ptr
		<
			BSTNode <
						FrequencyDataPrimitive<int>,
						FrequencyDataContainer<int>
					>
		>
		rootNodeFreq
		= std::make_shared<
		BSTNode<FrequencyDataPrimitive<int>,
		FrequencyDataContainer<int>>>(freqPtr);

	for (int i = 1; i < sorted.size(); ++i)
	{
		currentSorted = sorted[i];
		std::shared_ptr<FrequencyDataPrimitive<int>> freqPtr
			= std::make_shared < FrequencyDataPrimitive<int>>(
				currentSorted.DataPtr,
				currentSorted.Count);
		rootNodeFreq->RecursiveInsert(freqPtr);
	}

	std::vector<FrequencyDataContainer<int>> frequencySorted;
	frequencySorted.clear();
	rootNodeFreq->SortMostLeft(frequencySorted, myFrequencyVectorInsert);
	std::vector<FrequencyDataPrimitive<int>> vecFrequencyDataPrimitives;
	for (int i = 0; i < frequencySorted.size(); ++i)
	{
		std::vector<DataContainer<int>> sortedInternal;
		frequencySorted[i].RootNode->SortMostLeft(sortedInternal, myDuplicateAwareVectorInsert);
		int frequency = *frequencySorted[i].DataPtr;
		for(int j = 0; j<sortedInternal.size();++j)
		{
			FrequencyDataPrimitive<int> fdp(sortedInternal[j].DataPtr, frequency);
			vecFrequencyDataPrimitives.push_back(fdp);
		}
	}
	std::for_each(vecFrequencyDataPrimitives.begin(), vecFrequencyDataPrimitives.end(), myFequencyDataPrimitivePrintfunction);
	std::cout << std::endl;

	system("pause");
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
