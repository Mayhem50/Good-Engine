#pragma once

//For dll lib
#ifdef DLL_EXPORT
#define GOOD_DLL __declspec(dllexport)
//For client lib
#elif DLL_IMPORT
#define GOOD_DLL __declspec(dllimport)
#else
#define GOOD_DLL
#endif

#define MAX_CHAR 256

#include <ostream>
#include <string>
#include <typeinfo>
