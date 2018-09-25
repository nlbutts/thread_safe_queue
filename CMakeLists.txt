cmake_minimum_required (VERSION 2.6)
project (tt)

add_compile_options("-std=gnu++17")

link_libraries(pthread)
add_executable(tt main.cpp)