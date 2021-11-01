project(test_libcurl)
cmake_minimum_required(VERSION "3.16")

add_subdirectory(curl)
include_directories(curl/include)

add_executable(mainxx main.cpp)

target_link_libraries(mainxx PRIVATE libcurl)

add_executable(getinmemory getinmemory.c)

target_link_libraries(getinmemory PRIVATE libcurl)
