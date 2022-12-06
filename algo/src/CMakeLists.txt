#set(core_SRCS ADD ALL SOURCE FILES HERE)

#add_library(core ${core_SRCS})
set(CMAKE_CXX_STANDARD 17)

set(COMPILE_FLAGS "--coverage")
set(CMAKE_EXE_LINKER_FLAGS "--coverage")

add_executable(exe ../main.cpp)
#target_link_libraries(exe core)