cmake_minimum_required(VERSION 2.8)
include(${CMAKE_CURRENT_LIST_DIR}/env/env.cmake)

project(Sample)

set(RPATH "${PROJECT_SOURCE_DIR}/lib/3dcamera/${os}/${plat_form}")
set(HANDEYE_LIB "${PROJECT_SOURCE_DIR}/lib/handEye/${os}/${plat_form}")

MESSAGE(STATUS "RPATH ${RPATH}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_CURRENT_LIST_DIR}/inc/3dcamera)
include_directories(${CMAKE_CURRENT_LIST_DIR}/inc/handEye)
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib/3dcamera/${os}/${plat_form})
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib/handEye/${os}/${plat_form})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(src)

