cmake_minimum_required(VERSION 3.20)
project(states)

file(GLOB STATES_SRCS "src/*.cpp")

add_library(${PROJECT_NAME} SHARED
    ${STATES_SRCS}
)
set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 14
)
target_include_directories(${PROJECT_NAME} PRIVATE "include")