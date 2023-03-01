add_library (Helloworld helloworld.cpp helloworld.h)
add_executable (demo main.cpp)
set_target_properties(
    demo
    PROPERTIES 
        SUFFIX ".o"
)
target_link_libraries (demo Helloworld)