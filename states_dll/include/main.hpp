#pragma once

#if defined( _WIN32 )

#include <windows.h>

#else // _WIN32

#error Only Windows is supported

#endif // _WIN32

typedef void modFunction_t( void );

extern size_t     g_onHostedFunctionCount;
extern uintptr_t* g_onHostedfunctionAddresses;
extern size_t     g_onConnectionFunctionCount;
extern uintptr_t* g_onConnectionfunctionAddresses;
