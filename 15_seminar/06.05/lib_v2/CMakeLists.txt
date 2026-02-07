cmake_minimum_required(VERSION 3.16)
project(lib_v2)

add_library(library_v2 SHARED lib_v2.cpp)
set_target_properties(library_v2 PROPERTIES PREFIX "")
