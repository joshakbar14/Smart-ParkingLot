cmake_minimum_required(VERSION 3.7.0)

project (SMART_PARKINGLOT VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets)

add_subdirectory (src)

set(CMAKE_PREFIX_PATH "usr/lib/")

#add_subdirectory (test)

#enable_testing ()
#add_test (NAME ultrasonicTest COMMAND Test)

set(CMAKE_PREFIX_PATH "/usr/lib/")
