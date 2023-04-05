cmake_minimum_required(VERSION 3.7.0)

project (SMART_PARKINGLOT VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory (src)
#add_subdirectory (test)

#enable_testing ()
#add_test (NAME ultrasonicTest COMMAND Test)
