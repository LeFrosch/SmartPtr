#pragma once

#include <Windows.h>

class RefCounter
{
public:
	volatile unsigned long long references;

	RefCounter()
	{
		references = 1;
	}

	void Increment()
	{
		InterlockedIncrement(&references);
	}

	bool Decrement()
	{
		InterlockedDecrement(&references);
		return references <= 0;
	}
};

template <class T>
struct SmartPointer
{
private:
	RefCounter* counter;
	T* ptr;

	void Copy(const SmartPointer& smartPointer)
	{
		counter = smartPointer.counter;
		ptr = smartPointer.ptr;

		smartPointer.counter->Increment();
	}

public:
	SmartPointer()
	{
		this->ptr = NULL;
		this->counter = NULL;
	}

	SmartPointer(T* ptr)
	{
		this->ptr = ptr;
		this->counter = new RefCounter();
	}

	SmartPointer(RefCounter* counter, T* ptr)
	{
		this->counter = counter;
		this->counter->Increment();

		this->ptr = ptr;
	}

	SmartPointer(const SmartPointer<T>& smartPointer)
	{
		Copy(smartPointer);
	}

	SmartPointer(const SmartPointer<T>&& smartPointer)
	{
		Copy(smartPointer);
	}

	SmartPointer<T>& operator=(const SmartPointer<T>& smartPointer) noexcept
	{
		Copy(smartPointer);
		return *this;
	}

	SmartPointer<T>& operator=(const SmartPointer<T>&& smartPointer) noexcept
	{
		Copy(smartPointer);
		return *this;
	}

	~SmartPointer()
	{
		Clear();
	}

	T* operator->() const noexcept
	{
		return ptr;
	}

	T& operator*() const noexcept
	{
		return *ptr;
	}

	T* Get() const noexcept
	{
		return ptr;
	}

	template <class C>
	SmartPointer<C> Cast()
	{
		return SmartPointer<C>(this->counter, (C*)this->ptr);
	}

	void Clear()
	{
		if (IsNull()) return;

		if (counter->Decrement())
		{
			delete ptr;
			delete counter;
		}

		ptr = NULL;
		counter = NULL;
	}

	bool IsNull()
	{
		return !this->operator bool();
	}

	explicit operator bool() const noexcept
	{
		return ptr != NULL && counter != NULL;
	}
};

template <class T1, class T2>
bool operator==(const SmartPointer<T1>& left, const SmartPointer<T2>& right) noexcept
{
	return left.Get() == right.Get();
}

template <class T1, class T2>
bool operator!=(const SmartPointer<T1>& left, const SmartPointer<T2>& right) noexcept
{
	return left.Get() != right.Get();
}

template <class T1, class T2>
bool operator<(const SmartPointer<T1>& left, const SmartPointer<T2>& right) noexcept
{
	return left.Get() < right.Get();
}

template <class T1, class T2>
bool operator>=(const SmartPointer<T1>& left, const SmartPointer<T2>& right) noexcept
{
	return left.Get() >= right.Get();
}

template <class T1, class T2>
bool operator>(const SmartPointer<T1>& left, const SmartPointer<T2>& right) noexcept
{
	return left.Get() > right.Get();
}

template <class T1, class T2>
bool operator<=(const SmartPointer<T1>& left, const SmartPointer<T2>& right) noexcept
{
	return left.Get() <= right.Get();
}