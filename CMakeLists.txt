#set(CMAKE_LEGACY_CYGWIN_WIN32 0)

cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project(Deltas)

#include_directories(${PROJECT_SOURCE_DIR}/Sample)

include_directories(Sample)
add_executable(Deltas Sample/main.cpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/Library/)
target_link_libraries(Deltas PUBLIC DeltaLibrary)

add_subdirectory(GoogleTests)

#include_directories(${PROJECT_SOURCE_DIR}/Sample)

#target_link_libraries(Deltas PUBLIC DeltaLibrary)

#set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

# add_library(Deltas library.cpp library.h)

#add_subdirectory(Library)
#add_subdirectory(Sample)

#add_executable(Deltas Sample/main.cpp)