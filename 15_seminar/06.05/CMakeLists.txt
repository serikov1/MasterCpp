cmake_minimum_required(VERSION 3.28)

project(06.05 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(Boost_USE_STATIC_LIBS    ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost 1.85 REQUIRED COMPONENTS system filesystem)

include_directories(${Boost_INCLUDE_DIRS})

# -------------------------------------------------------------------
add_library(lib_v1 SHARED
    lib_v1/lib_v1.cpp
)
target_compile_options(lib_v1 PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(lib_v1 PRIVATE ${Boost_LIBRARIES})

# -------------------------------------------------------------------
add_library(lib_v2 SHARED
    lib_v2/lib_v2.cpp
)
target_compile_options(lib_v2 PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(lib_v2 PRIVATE ${Boost_LIBRARIES})

# -------------------------------------------------------------------
add_executable(main main.cpp)
target_include_directories(main PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${Boost_LIBRARIES})
add_dependencies(main lib_v1 lib_v2)
