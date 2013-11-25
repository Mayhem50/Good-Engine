#pragma once

//For dll lib
#ifdef DLL_EXPORT
#define GOOD_DLL __declspec(dllexport)
//For client lib
#else
#define GOOD_DLL __declspec(dllimport)
#endif

#define MAX_CHAR 256
#include <ostream>
#include <string>
#include <typeinfo>

