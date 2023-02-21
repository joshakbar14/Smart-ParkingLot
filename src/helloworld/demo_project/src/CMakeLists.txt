add_library (Helloworld helloworld.cpp helloworld.h)
add_executable (demo main.cpp)
target_link_libraries (demo Helloworld)