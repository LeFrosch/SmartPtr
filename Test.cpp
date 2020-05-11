#include "SmartPtr.h"
#include <stdio.h>

class ITestObj
{
public:
	virtual void Test() = 0;
	virtual ~ITestObj() = default;
};

class TestObj : public ITestObj
{
private:
	const char* info;

public:
	TestObj(const char* info)
	{
		this->info = info;
		printf("Object created, info: %s\n", this->info);
	}
	 
	~TestObj()
	{
		printf("Object destructed\n");
	}

	void Test() override
	{
		printf("Object accsessd, info: %s\n", info);
	}
};

SmartPointer<ITestObj> test()
{
	SmartPointer<TestObj> p = SmartPointer<TestObj>(new TestObj("Testi"));
	return p.Cast<ITestObj>();
}

int main()
{
	ITestObj* ptr;

	{
		SmartPointer<ITestObj> p;
		p = test();

		ptr = p.Get();
		ptr->Test();
	}

	ptr->Test();
}