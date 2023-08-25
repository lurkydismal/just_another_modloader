#!/bin/bash
mkdir build || \
rm build/*

i686-w64-mingw32-g++-win32 -static-libgcc -static-libstdc++ -shared \
-I "states_dll/include" \
-I "states_dll/stdfunc/include" \
-I "states_dll/include/mingw-std-threads" \
-I "states_dll/Detours/src" \
states_dll/src/* \
states_dll/stdfunc/src/* \
-o build/states.dll

cargo build --target=i686-pc-windows-gnu --release

cp target/i686-pc-windows-gnu/release/*.dll build/Netplay.dll
