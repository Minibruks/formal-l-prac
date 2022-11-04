# Distributed under the OSI-approved MIT License.  See accompanying
# file LICENSE or https://github.com/Crascit/DownloadProject for details.

cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest-download
                    GIT_REPOSITORY;https://github.com/google/googletest.git;GIT_TAG;main;UPDATE_DISCONNECTED;1
                    SOURCE_DIR          "/Users/pavel/Desktop/formal-prac/cmake-build-debug-coverage/googletest-src"
                    BINARY_DIR          "/Users/pavel/Desktop/formal-prac/cmake-build-debug-coverage/googletest-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)
