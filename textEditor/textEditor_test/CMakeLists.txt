cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runTest editClass_test_f.cpp ../textEditor/editClass.cpp ../textEditor/opObj.cpp)
target_link_libraries(runTest ${GTEST_LIBRARIES} pthread)

