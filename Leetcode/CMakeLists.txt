cmake_minimum_required(VERSION 3.10)

set(LEETCODE_SRC
    2502.DesignMemoryAllocator.cpp
    2502.DesignMemoryAllocatorTest.cpp)

include_directories(${PROJECT_SOURCE_DIR}/Leetcode)
add_library(Leetcode SHARED ${LEETCODE_SRC} "743.NetworkDelay Time.cpp" "743.NetworkDelayTime.hpp")
