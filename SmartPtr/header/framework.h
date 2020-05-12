#pragma once

#define WIN32_LEAN_AND_MEAN          
#define NOMINMAX
// Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#undef NOMINMAX

#ifdef SMARTPTR_EXPORTS
#define SMARTPTR_API __declspec(dllexport)
#else
#define SMARTPTR_API __declspec(dllimport)
#endif

