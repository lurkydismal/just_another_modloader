#pragma once

///////////////
/// @file stdfunc.hpp
/// @brief Declarations of many useful functions and lambdas related to replace standard if needed.
///////////////
#pragma once

#ifdef _WIN32

#include <windows.h>
// #pragma comment( lib, "user32" )
// #pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
// #pragma comment (lib, "AdvApi32.lib")
#include <tlhelp32.h>

// Copyright (c) Microsoft Corporation. All rights reserved.

// Licensed under the MIT License.
#include <detours.h>

#else

#include <unistd.h>
#include <stdio.h>

#endif // _WIN32

#include <stdint.h>
#include <stdbool.h>

#ifndef INT8_MIN

#define INT8_MIN -128

#endif // INT8_MIN

///////////////
/// @brief Pass from Python, same as NULL.
///////////////
#define Pass (void*)0

///////////////
/// @brief How much memory to allocate.
///////////////
#define HEAP_MEMORY_SIZE 150

///////////////
/// @brief Hex length.
///////////////
#define HEX_LENGTH ( sizeof( int32_t ) << 1 )

///////////////
/// @brief Detouring macro simplified.
///////////////
#define RegisterHook( _originalFunctionAddress, _hookFunctionAddress, _functionName )\
    DetourTransactionBegin();\
    DetourUpdateThread( GetCurrentThread() );\
    DetourAttach(\
        &_originalFunctionAddress,\
        &_hookFunctionAddress\
    );\
    ( (\
        DetourTransactionCommit() != NO_ERROR\
    ) ? (\
        printf( "\nError %s\n", _functionName )\
    ) : (\
        printf( "\nHooked: %s\n", _functionName )\
    ) );

///////////////
/// @brief Un-detouring macro simplified.
///////////////
#define RemoveHook( _originalFunctionAddress, _hookFunctionAddress, _functionName )\
    RegisterHook( _originalFunctionAddress, _hookFunctionAddress, _functionName )

#if defined( __cplusplus )

extern "C" {

#endif // __cplusplus

const char* const boolToString( bool _boolean );

char* numberToHexString( int32_t _number );

uint_fast32_t lengthOfInt( long _number );

uint_fast32_t lengthOfCString( char* _string );

void print( const char* _text, const uint32_t _lengthOfText );

unsigned long Rand( void );

void SRand( unsigned long _seed );

void clearConsole( void );

void Memcpy( void* _destination, const void* _source, size_t _numberOfBytes );

char* Ltoa( unsigned long _number, char* _cString );

uintptr_t getModule( const char* _moduleName );

#if defined( _WIN32 )

///////////////
/// @brief Read value from address.
/// @param[in] _address Address to read.
/// @param[in] _memoryCheck Segmentation fault checks flag.
/// @return Address value or \c NULL on error.
///////////////
template < typename T >
T read(
    const uintptr_t _address,
    const bool _memoryCheck
) {
    if ( _memoryCheck ) {
        //! <b>[declare]</b>
        /// @code{.cpp}
        MEMORY_BASIC_INFORMATION l_MBI;
        /// @endcode
        //! <b>[declare]</b>

        VirtualQuery(
            (LPCVOID)_address, // A pointer to the base address of the region of pages to be queried. This value is rounded down to the next page boundary.
            &l_MBI,            // A pointer to a MEMORY_BASIC_INFORMATION structure in which information about the specified page range is returned.
            sizeof( l_MBI )    // The size of the buffer pointed to by the lpBuffer parameter, in bytes.
        );

        if ( !( l_MBI.State & MEM_COMMIT ) ) {
            print( "\nMEM_COMMIT\n", 13 );

            //! <b>[return]</b>
            /// End of function.
            /// @code{.cpp}
            return ( NULL );
            /// @endcode
            //! <b>[return]</b>
        }

        if ( l_MBI.Protect & ( PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS ) ) {
            print( "\nPAGE_GUARD\n", 13 );

            if (
                !VirtualProtect(
                    l_MBI.BaseAddress, // The address of the starting page of the region of pages whose access protection attributes are to be changed.
                    l_MBI.RegionSize,  // The size of the region whose access protection attributes are to be changed, in bytes.
                    PAGE_READWRITE,    // The memory protection option.
                    &l_MBI.Protect     // A pointer to a variable that receives the previous access protection value of the first page in the specified region of pages.
                )
            ) {
                print( "\nVirtualProtect\n", 17 );

                //! <b>[return]</b>
                /// End of function.
                /// @code{.cpp}
                return ( NULL );
                /// @endcode
                //! <b>[return]</b>
            }

            T l_returnValue = *( reinterpret_cast< T* >( _address ) );
            DWORD l_dwOldProtect;

            VirtualProtect(
                l_MBI.BaseAddress, // The address of the starting page of the region of pages whose access protection attributes are to be changed.
                l_MBI.RegionSize,  // The size of the region whose access protection attributes are to be changed, in bytes.
                l_MBI.Protect,     // The memory protection option.
                &l_dwOldProtect    // A pointer to a variable that receives the previous access protection value of the first page in the specified region of pages.
            );

            //! <b>[return]</b>
            /// End of function.
            /// @code{.cpp}
            return ( l_returnValue );
            /// @endcode
            //! <b>[return]</b>
        }
    }

    //! <b>[return]</b>
    /// End of function.
    /// @code{.cpp}
    return ( *( reinterpret_cast< T* >( _address ) ) );
    /// @endcode
    //! <b>[return]</b>
}

#else // _WIN32

#warning Not all functions are implemented.

///////////////
/// @brief Read value from address.
/// @param[in] _address Address to read.
/// @param[in] _memoryCheck Segmentation fault checks flag.
/// @return Address value or \c NULL on error.
///////////////
template< typename T >
T read(
    const uintptr_t _address,
    const bool _memoryCheck
) {
    return ( static_cast< T >( NULL ) );
}

#endif

uintptr_t getAddress(
    uintptr_t _moduleAddress,
    const uint32_t* _offsets,
    uint32_t _offsetsCount,
    const bool _memoryCheck
);

#if defined( __cplusplus )

}

#endif // __cplusplus
