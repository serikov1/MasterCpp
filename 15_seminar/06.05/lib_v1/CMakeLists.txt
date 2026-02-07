cmake_minimum_required(VERSION 3.16)
project(lib_v1)

add_library(library_v1 SHARED lib_v1.cpp)
set_target_properties(library_v1 PROPERTIES PREFIX "")
