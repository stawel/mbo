cmake_minimum_required (VERSION 2.8.12)

project (code)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(benchmark)
add_subdirectory(no_stl)
add_subdirectory(stl)


include_directories(benchmark/include)

add_executable(csort csort.cpp)
target_link_libraries(csort benchmark)

add_executable(csort_stable csort_stable.cpp)
target_link_libraries(csort_stable benchmark)

add_executable(simple_sort simple_sort.cpp)
target_link_libraries(simple_sort benchmark)

add_executable(heap heap.cpp)
target_link_libraries(heap benchmark)

add_executable(hash_map hash_map.cpp)
target_link_libraries(hash_map benchmark)

add_executable(merge_sort merge_sort.cpp)
target_link_libraries(merge_sort benchmark)

add_executable(mul mul.cpp)
target_link_libraries(mul benchmark)

add_executable(cache_matrix_mul cache_matrix_mul.cpp)
target_link_libraries(cache_matrix_mul benchmark)

add_executable(map_vs_vector map_vs_vector.cpp)
target_link_libraries(map_vs_vector benchmark)

add_executable(binary_search binary_search.cpp)
target_link_libraries(binary_search benchmark)

