#include "framework.h"

namespace Smart
{
	class SMARTPTR_API RefCounter
	{
	public:
		volatile unsigned long long references;

		RefCounter();

		void Increment();

		bool Decrement();
	};
}