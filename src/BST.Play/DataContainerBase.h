#pragma once
template<class TData, class TDerived>
class DataContainerBase
{

public:
	virtual void InitialSetData(std::shared_ptr<TData> dataPtr) = 0;
	virtual void InjestDuplicate(std::shared_ptr<TData> dataPtr) = 0;
};
