cmake_minimum_required (VERSION 2.8.12)

project (code)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(benchmark)


include_directories(benchmark/include)

add_executable(csort csort.cpp)
target_link_libraries(csort benchmark)