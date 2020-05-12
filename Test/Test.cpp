#include <iostream>
#include "SmartPtr.h"

using namespace Smart;

namespace Test
{
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

	public ref class TestWrapper
	{
	public:
		static int main()
		{
			SmartPointer<TestObj> p = SmartPointer<TestObj>(new TestObj("HI"));

			return 0;
		}
	};
}