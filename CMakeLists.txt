cmake_minimum_required(VERSION 3.23)

project(hsrl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /sdl /MP /O2")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /INCREMENTAL:NO")

include_directories(
  "${CMAKE_SOURCE_DIR}/inc/"
  "${CMAKE_SOURCE_DIR}/lib/"
)

link_directories(
  "${CMAKE_SOURCE_DIR}/lib/"
)

file(GLOB_RECURSE SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/lib/*.c"
  "${CMAKE_SOURCE_DIR}/lib/*.cpp"
  "${CMAKE_SOURCE_DIR}/inc/*.hpp"
)

add_library(library SHARED ${SOURCES})

target_link_libraries(library "minhook/minhook.x64")