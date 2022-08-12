cmake_minimum_required(VERSION 3.20)
project(just_another_modloader)

include(cmake/build_requirements.cmake)

check_requirements()

import_detours()

add_subdirectory(states_dll)