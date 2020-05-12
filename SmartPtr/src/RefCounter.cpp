#include "RefCounter.h"

using namespace OpenVG::Utils;

RefCounter::RefCounter()
{
	references = 1;
}

void RefCounter::Increment()
{
	InterlockedIncrement(&references);
}

bool RefCounter::Decrement()
{
	InterlockedDecrement(&references);
	return references <= 0;
}
