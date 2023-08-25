///////////////
/// @file stdfunc.cpp
/// @brief Definition of many useful functions related to replace standard if needed.
///////////////
#ifndef _WIN32

#include <stdio.h>

#endif // _WIN32

#include <stdfunc.hpp>

///////////////
/// @brief Inline function that converts \c bool to string.
/// @param[in] _boolean Boolean value to convert to string.
/// @return Char pointer to text. <b>( OK || Failed )</b>
///////////////
const char* const boolToString( bool _boolean ) {
    //! <b>[return]</b>
    /// End of function.
    /// @code{.c}
    return ( _boolean ? "OK" : "Failed" );
    /// @endcode
    //! <b>[return]</b>
}

///////////////
/// @brief Converts \c double to hex string.
/// @param[in] _number Integer value to convert to hex string.
/// @return Converted hex string.
///////////////
char* numberToHexString( int32_t _number ) {
    //! <b>[declare]</b>
    /// @code{.cpp}
    const char l_hex[]           = "0123456789ABCDEF";
    char*      l_convertedString = (char*)Malloc( HEX_LENGTH );
    /// @endcode
    //! <b>[declare]</b>

    //! <b>[fill_with_zeros]</b>
    /// Filling \c l_convertedString with zeros.
    /// @code{.cpp}
    for (
        uint32_t _symbolIndex = 0;
        _symbolIndex < HEX_LENGTH;
        _symbolIndex++
    ) {
        l_convertedString[ _symbolIndex ] = '0';
    }
    /// @endcode
    //! <b>[fill_with_zeros]</b>

    //! <b>[convertion]</b>
    /// @code{.cpp}
    for (
        size_t _symbolIndex = 0,
            _j = ( HEX_LENGTH - 1 ) * 4;
        _symbolIndex < HEX_LENGTH;
        ++_symbolIndex, _j -= 4
    ) {
        l_convertedString[ _symbolIndex ] = l_hex[ ( _number >> _j ) & 0x0f ];
    }
    /// @endcode
    //! <b>[convertion]</b>

    //! <b>[return]</b>
    /// End of function.
    /// @code{.cpp}
    return ( l_convertedString );
    /// @endcode
    //! <b>[return]</b>
}

///////////////
/// @brief Function that find length of an integer number.
/// @details Can get length of negative and positive number.
/// @param[in] _number Number to get length from.
/// @return Number length.
///////////////
uint_fast32_t lengthOfInt( long _number ) {
    //! <b>[declare]</b>
    /// Length of _number.
    /// @code{.c}
    uint_fast32_t l_length = 0;
    /// @endcode
    //! <b>[declare]</b>

    //! <b>[count_length]</b>
    /// Divide by 10 while value not equal to 0.
    /// @code{.c}
    do {
        l_length++;
        _number /= 10;
    } while ( _number != 0 );
    /// @endcode
    //! <b>[count_length]</b>

    //! <b>[return]</b>
    /// End of function.
    /// @code{.c}
    return ( l_length );
    /// @endcode
    //! <b>[return]</b>
}

///////////////
/// @brief Function that find length of an string.
/// @param[in] _string String pointer to get length from.
/// @return String length.
///////////////
uint_fast32_t lengthOfCString( char* _string ) {
    //! <b>[declare]</b>
    /// Last symbol from _string.
    /// @code{.c}
    char* l_temp_string = _string;
    /// @endcode
    //! <b>[declare]</b>

    //! <b>[count_length]</b>
    /// Go through _string upon null-terminator.
    /// @code{.c}
    while ( *l_temp_string != '\0' ) {
        l_temp_string++;
    }
    /// @endcode
    //! <b>[count_length]</b>

    //! <b>[return]</b>
    /// End of function.
    /// @code{.c}
    return ( l_temp_string - _string + 1 );
    /// @endcode
    //! <b>[return]</b>
}

//! <b>[declare]</b>
/// \c seed that is in use by \c Rand and \c SRand functions.
/// @code{.c}
static unsigned long g_seed = 1;
/// @endcode
//! <b>[declare]</b>

///////////////
/// @brief Function that print out char pointer text to console.
/// @details Uses \c WriteConsoleA from \c Windows.h
/// @param[in] _text Pointer to text.
/// @param[in] _lengthOfText Length of text.
///////////////
void print( const char* _text, const uint32_t _lengthOfText ) {
    //! <b>[print]</b>
    /// Write text to console
    /// @code{.c}

#ifdef _WIN32

    WriteConsoleA(
        GetStdHandle( STD_OUTPUT_HANDLE ), // Console handle
        _text,                             // Pointer to text
        _lengthOfText,                     // Length of text
        NULL,                              // Buffer to write value of characters written
        NULL                               // Reserved. Must be NULL
    );

#else // _WIN32

    for ( uint32_t _symbolIndex = 0; _symbolIndex < _lengthOfText; _symbolIndex++ ) {
        putchar( _text[ _symbolIndex ] );
    }

#endif // _WIN32

    /// @endcode
    //! <b>[print]</b>
}

///////////////
/// @brief Function that generate random number from the \c seed.
/// @details Use \c SRand() to set the seed.
/// @return Generated random number.
///////////////
unsigned long Rand( void ) {
    //! <b>[random]</b>
    /// Generating random number from the \c seed.
    /// @code{.c}
    g_seed = ( g_seed * (unsigned long)16807 % (unsigned long)0x7fffffff );
    /// @endcode
    //! <b>[random]</b>

    //! <b>[return]</b>
    /// End of function.
    return ( g_seed );
    //! <b>[return]</b>
}

///////////////
/// @brief Function that set the \c seed.
/// @details Use \c Rand() to generate random number from the \c seed.
/// @param[in] l_seed Seed to set.
///////////////
void SRand( unsigned long l_seed ) {
    //! <b>[change]</b>
    /// Setting the \c seed.
    /// @code{.c}
    g_seed = l_seed;
    /// @endcode
    //! <b>[change]</b>
}

///////////////
/// @brief Function that clear the console out screen.
/// @details Filling console length with empty text.
///////////////
void clearConsole( void ) {

#ifdef _WIN32

    //! <b>[declare]</b>
    /// Getting and declaring coordinates and console handle where to write.
    /// @code{.c}
    COORD l_topLeft = {
        0,              // X
        0               // Y
    };
    CONSOLE_SCREEN_BUFFER_INFO l_consoleScreenInfo;
    HANDLE l_consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );
    /// @endcode
    //! <b>[declare]</b>

    //! <b>[length]</b>
    /// Getting length of console.
    /// @code{.c}
    GetConsoleScreenBufferInfo( l_consoleHandle, &l_consoleScreenInfo );
    DWORD l_numberOfWrittenCharacters, l_lengthOfText = l_consoleScreenInfo.dwSize.X * l_consoleScreenInfo.dwSize.Y;
    /// @endcode
    //! <b>[length]</b>

    //! <b>[print]</b>
    /// Write empty text to console.
    /// @code{.c}
    FillConsoleOutputCharacter( l_consoleHandle, ' ', l_lengthOfText, l_topLeft, &l_numberOfWrittenCharacters );
    FillConsoleOutputAttribute( l_consoleHandle, l_consoleScreenInfo.wAttributes, l_lengthOfText, l_topLeft, &l_numberOfWrittenCharacters );
    /// @endcode
    //! <b>[print]</b>

    //! <b>[reset]</b>
    /// Reset cursor position in console.
    /// @code{.c}
    SetConsoleCursorPosition( l_consoleHandle, l_topLeft );
    /// @endcode
    //! <b>[reset]</b>

#else // _WIN32

    const char l_magicText[] = "\033[1;1H\033[2J";

    for ( uint32_t _symbolIndex = 0; _symbolIndex < sizeof( l_magicText ); _symbolIndex++ ) {
        putchar( l_magicText[ _symbolIndex ] );
    }

#endif // _WIN32

}

#if defined( _WIN32 )

///////////////
/// @brief Find module address.
/// @param[in] _moduleName Module name.
/// @return Module address. \c 0 on error.
///////////////
uintptr_t getModule( const char* _moduleName ) {
    //! <b>[declare]</b>
    /// @code{.cpp}
    MODULEENTRY32 l_moduleEntry{ sizeof( MODULEENTRY32 ) };

    const HANDLE l_snapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE |
        TH32CS_SNAPMODULE32,
        0
    );
    /// @endcode
    //! <b>[declare]</b>

    //! <b>[search]</b>
    if ( Module32First( l_snapshot, &l_moduleEntry ) ) {
        do {
            if ( strcmp( _moduleName, (char*)l_moduleEntry.szModule ) != 0 ) {
                CloseHandle( l_snapshot );

                //! <b>[return]</b>
                /// End of function.
                /// @code{.cpp}
                return ( (uintptr_t)l_moduleEntry.hModule );
                /// @endcode
                //! <b>[return]</b>
            }

        } while ( Module32Next( l_snapshot, &l_moduleEntry ) );
    }
    //! <b>[search]</b>

    //! <b>[return]</b>
    /// End of function.
    /// @code{.cpp}
    return ( 0 );
    /// @endcode
    //! <b>[return]</b>
}

#else // _WIN32

#warning Not all functions are implemented.

///////////////
/// @brief Find module address.
/// @param[in] _moduleName Module name.
/// @return Module address. \c 0 on error.
///////////////
uintptr_t getModule( const char* _moduleName ) {
    return ( 0 );
}

#endif // _WIN32

///////////////
/// @brief Find health address from module address and offsets.
/// @param[in] _moduleAddress Module address.
/// @param[in] _offsets Offsets.
/// @param[in] _offsetsCount Offsets count.
/// @param[in] _memoryCheck Segmentation fault checks flag.
/// @return Health address.
///////////////
uintptr_t getAddress(
    uintptr_t _moduleAddress,
    const uint32_t* _offsets,
    uint32_t _offsetsCount,
    const bool _memoryCheck
) {
    //! <b>[search]</b>
    /// @code{.cpp}
    for (
        size_t _offsetIndex = 0;
        _offsetIndex < _offsetsCount;
        _offsetIndex++
    ) {
        _moduleAddress = (uintptr_t)read( _moduleAddress, _memoryCheck );
        _moduleAddress += (char)_offsets[ _offsetIndex ];
    }
    /// @endcode
    //! <b>[search]</b>

    //! <b>[return]</b>
    /// End of function.
    /// @code{.cpp}
    return ( _moduleAddress );
    /// @endcode
    //! <b>[return]</b>
}
