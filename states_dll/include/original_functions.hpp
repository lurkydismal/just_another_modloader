#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#error Only Windows is supported
#endif

#include <string>

#include <main.hpp>

namespace original {

extern void ( __cdecl* portFunction )( struct struct0* _argument );

}