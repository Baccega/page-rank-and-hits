cmake_minimum_required(VERSION 3.22)
project(pagerank-hits)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions" "-O3"
)


set(LIB_SOURCE_FILES src/hits.h src/pagerank.h src/csr.h src/inDegree.h src/utils.h)

add_executable(pagerank-hits src/main.cpp ${LIB_SOURCE_FILES})