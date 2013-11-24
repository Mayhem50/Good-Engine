#pragma once

//For dll lib
#ifdef DLL_EXPORT
#define GOOD_DLL __declspec(dllexport)

//For client lib
#else
#ifdef DLL_IMPORT
#define GOOD_DLL __declspec(dllimport)

#else
#define GOOD_DLL

#endif
#endif