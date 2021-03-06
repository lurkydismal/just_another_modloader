///////////////
/// @file stdfunc.cpp
/// @brief Definition of many useful functions related to replace standart if needed.
///////////////

#ifndef _WIN32
#include <stdio.h>
#endif
#include <stdfunc.hpp>

///////////////
/// @brief Function that find length of an integer number.
/// @details Can get length of negative and positive number.
/// @param[in] _number Number to get length from.
/// @return Number length.
///////////////
uint_fast32_t lengthOfInt( long _number ) {
    //! <b>[declare]</b>
    /// Length of _number.
    /// @code{.cpp}
    uint_fast32_t l_length = 0;
    /// @endcode
    //! <b>[declare]</b>

    //! <b>[count_length]</b>
    /// Divide by 10 while value not equal to 0.
    /// @code{.cpp}
    do {
        l_length++;
        _number /= 10;
    } while ( _number != 0 );
    /// @endcode
    //! <b>[count_length]</b>

    //! <b>[return]</b>
    /// End of function.
    /// @code{.cpp}
    return ( l_length );
    /// @endcode
    //! <b>[return]</b>
}

///////////////
/// @brief Function that find length of an string.
/// @param[in] _string String pointer to get length from.
/// @return String length.
///////////////
uint_fast32_t stringLength( char* _string ) {
    //! <b>[declare]</b>
    /// Last symbol from _string.
    /// @code{.cpp}
    char* l_temp_string = _string;
    /// @endcode
    //! <b>[declare]</b>

    //! <b>[count_length]</b>
    /// Go through _string upon null-terminator.
    /// @code{.cpp}
    while ( *l_temp_string != '\0' ) {
        l_temp_string++;
    }
    /// @endcode
    //! <b>[count_length]</b>

    //! <b>[return]</b>
    /// End of function.
    /// @code{.cpp}
    return ( l_temp_string - _string + 1 );
    /// @endcode
    //! <b>[return]</b>
}

//! <b>[declare]</b>
/// \c seed that is in use by \c Rand and \c SRand functions.
/// @code{.cpp}
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
    /// @code{.cpp}
    #ifdef _WIN32
    WriteConsoleA(
        GetStdHandle( STD_OUTPUT_HANDLE ), // Console handle
        _text,                             // Pointer to text
        _lengthOfText,                     // Length of text
        NULL,                              // Buffer to write value of characters written
        NULL                               // Reserved. Must be NULL
    );
    #else
    for ( uint32_t _symbolIndex = 0; _symbolIndex < _lengthOfText; _symbolIndex++ ) {
        putc( _text[ _symbolIndex ], stdout );
    }
    #endif
    /// @endcode
    //! <b>[print]</b>
}

///////////////
/// @brief Function that exponentiation integer number.
/// @details Recursive function.
/// @param[in] _number Number to power.
/// @param[in] _exp Exponentiation value.
/// @return Exponentiation of number.
///////////////
int32_t Pow( int32_t _number, uint32_t _exp ) {
    if ( _exp == 1 ) {
        //! <b>[return]</b>
        /// End of function.
        /// @code{.cpp}
        return (1);
        /// @endcode
        //! <b>[return]</b>

    } else {
        //! <b>[return]</b>
        /// Recursive multiply.
        /// @code{.cpp}
        return ( _number * Pow( _number, _exp-- ) );
        /// @endcode
        //! <b>[return]</b>
    }
}

///////////////
/// @brief Function that generate random number from the \c seed.
/// @details Use \c SRand() to set the seed.
/// @return Generated random number.
///////////////
uint32_t Rand( void ) {
    //! <b>[random]</b>
    /// Generating random number from the \c seed.
    /// @code{.cpp}
    g_seed = g_seed * (int32_t)16807 % (uint32_t)0x7fffffff;
    /// @endcode
    //! <b>[random]</b>

    //! <b>[return]</b>
    /// End of function.
    /// @code{.cpp}
    return ( g_seed );
    /// @endcode
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
    /// @code{.cpp}
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
    /// @code{.cpp}
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
    /// @code{.cpp}
    GetConsoleScreenBufferInfo( l_consoleHandle, &l_consoleScreenInfo );
    DWORD l_numberOfWrittenCharacters, l_lengthOfText = l_consoleScreenInfo.dwSize.X * l_consoleScreenInfo.dwSize.Y;
    /// @endcode
    //! <b>[length]</b>

    //! <b>[print]</b>
    /// Write empty text to console.
    /// @code{.cpp}
    FillConsoleOutputCharacter( l_consoleHandle, ' ', l_lengthOfText, l_topLeft, &l_numberOfWrittenCharacters );
    FillConsoleOutputAttribute( l_consoleHandle, l_consoleScreenInfo.wAttributes, l_lengthOfText, l_topLeft, &l_numberOfWrittenCharacters );
    /// @endcode
    //! <b>[print]</b>

    //! <b>[reset]</b>
    /// Reset cursor position in console.
    /// @code{.cpp}
    SetConsoleCursorPosition( l_consoleHandle, l_topLeft );
    /// @endcode
    //! <b>[reset]</b>
    #else
    const char l_magicText[ 11 ] = "\e[1;1H\e[2J";
    for ( uint32_t _symbolIndex = 0; _symbolIndex < sizeof( l_magicText ); _symbolIndex++ ) {
        putc( l_magicText[ _symbolIndex ], stdout );
    }
    #endif
}

///////////////
/// @brief Find module address.
/// @param[in] _moduleName Module name.
/// @return Module address. \c nullptr on error.
///////////////
uintptr_t getModule( const char* _moduleName ) noexcept {
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
            if ( !strcmp( _moduleName, (char*)l_moduleEntry.szModule ) ) {
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
    return ( (uintptr_t)nullptr );
    /// @endcode
    //! <b>[return]</b>
}

///////////////
/// @brief Function that implements left mouse click.
/// @details Clicks by \b X and \b Y coordinates.
/// @param[in] _windowHandle Window handle.
///////////////
#ifdef _WIN32
bool LMC( HWND _windowHandle, const long _coordX, const long _coordY ) {
    POINT l_point = { _coordX, _coordY};
    // l_point.x = _coordX;
    // l_point.y = _coordY;

    //! <b>[]</b>
    /// The ClientToScreen function converts the client-area coordinates of a specified l_point to screen coordinates.
    /// @code{.cpp}
    if ( ClientToScreen(
        _windowHandle,              // A handle to the window whose client area is used for the conversion.
        &l_point                    // A l_pointer to a \c POINT structure that contains the client coordinates to be converted. The new screen coordinates are copied into this structure if the function succeeds.
        )
    ) {
    /// @endcode
    //! <b>[]</b>
        //! <b>[set_cursor_position]</b>
        /// Setting cursor position by X and Y.
        /// @code{.cpp}
        SetCursorPos(
            l_point.x,              // X
            l_point.y               // Y
        );
        /// @endcode
        //! <b>[set_cursor_position]</b>

        //! <b>[input]</b>
        /// Creating the \c INPUT structure with parameters to down left mouse button.
        /// @code{.cpp}
        INPUT l_mouseInput = { 0 }; // Empty

        l_mouseInput.type       = INPUT_MOUSE;
        l_mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        /// @endcode
        //! <b>[input]</b>

        //! <b>[click]</b>
        /// Sendind input with \c INPUT structure to \c winuser.
        /// @code{.cpp}
        SendInput(
            1,                      // The number of structures in the \c pInputs array.
            &l_mouseInput,          // An array of \c INPUT structures. Each structure represents an event to be inserted into the keyboard or mouse input stream.
            sizeof( l_mouseInput )  // The size, in bytes, of an \c INPUT structure. If cbSize is not the size of an \c INPUT structure, the function fails.
        );
        /// @endcode
        //! <b>[click]</b>

        //! <b>[sleep]</b>
        /// Pause between mouse down and mouse up.
        /// @code{.cpp}
        Sleep( 200 );               // 200 ms
        /// @endcode
        //! <b>[sleep]</b>

        //! <b>[input]</b>
        /// Editing the \c INPUT structure with parameters to up left mouse button.
        /// @code{.cpp}
        l_mouseInput.type       = INPUT_MOUSE;
        l_mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        /// @endcode
        //! <b>[input]</b>

        //! <b>[click]</b>
        /// Sendind input with \c INPUT structure to \c winuser.
        /// @code{.cpp}
        SendInput(
            1,                      // The number of structures in the pInputs array.
            &l_mouseInput,            // An array of INPUT structures. Each structure represents an event to be inserted into the keyboard or mouse input stream.
            sizeof( l_mouseInput )    // The size, in bytes, of an INPUT structure. If cbSize is not the size of an INPUT structure, the function fails.
        );
        /// @endcode
        //! <b>[click]</b>

        //! <b>[return]</b>
        /// Good end of function.
        /// @code{.cpp}
        return (true);
        /// @endcode
        //! <b>[return]</b>
    }

    //! <b>[return]</b>
    /// Bad end of function.
    /// @code{.cpp}
    return (false);
    /// @endcode
    //! <b>[return]</b>
}
#endif