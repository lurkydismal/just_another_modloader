function(check_requirements)

    if(NOT DEFINED CACHE{RUSTUP})
        message(STATUS "Detecting Rustup executable")
        find_program(RUSTUP rustup REQUIRED)
        message(STATUS "Rustup found: ${RUSTUP}")
    endif()

endfunction()

function(import_detours)
    include(FetchContent)
    FetchContent_Declare(
        detours
        GIT_REPOSITORY https://github.com/microsoft/Detours.git
    )
    FetchContent_Populate(detours)

    add_library(detours STATIC
        ${detours_SOURCE_DIR}/src/detours.cpp
        ${detours_SOURCE_DIR}/src/disasm.cpp
        ${detours_SOURCE_DIR}/src/disolarm.cpp
        ${detours_SOURCE_DIR}/src/disolarm64.cpp
        ${detours_SOURCE_DIR}/src/disolia64.cpp
        ${detours_SOURCE_DIR}/src/disolx64.cpp
        ${detours_SOURCE_DIR}/src/disolx86.cpp
        ${detours_SOURCE_DIR}/src/image.cpp
        ${detours_SOURCE_DIR}/src/modules.cpp
    )
    target_include_directories(detours PUBLIC "${detours_SOURCE_DIR}/src")

endfunction()
