cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)


set(REPO /Users/pavel/Desktop/formal-prac)

project(Test)

project(Example)

include(CTest)
enable_testing()

#set(gtest_disable_pthreads on) #needed in MinGW
include(${REPO}/DownloadProject/DownloadProject.cmake)
download_project(
        PROJ                googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             main
        UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

#set(test_SRCS ADD ALL TEST SOURCE FILES HERE)
add_executable(runUnitTests gtest.cpp parse_test.cpp)
target_link_libraries(runUnitTests gtest gtest_main)
#add_test(runUnitTests runUnitTests) #included in all tutorials but I don't know what it actually does.
