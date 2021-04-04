cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project(DeltaLibrary)


#include_directories(${PROJECT_SOURCE_DIR}/../../include ${PROJECT_SOURCE_DIR})

#file(GLOB SRC_LIB_FILES *.cpp)

#add_library(${PROJECT_NAME} ${SRC_LIB_FILES})

add_library(DeltaLibrary library.cpp library.h)
target_include_directories (DeltaLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#include_directories(../GoogleTests)