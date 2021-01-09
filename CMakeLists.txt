cmake_minimum_required(VERSION 3.15)
project(SimpleDB VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(SRC SHARED
        src/bmgr.cpp
        src/common.cpp
        src/dsmgr.cpp
        src/bcb.cpp
        src/lru.cpp
)

add_executable(SimpleDB main.cpp)
target_link_libraries(SimpleDB SRC)