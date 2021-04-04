project(GoogleTests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TestScope *.cpp)
add_executable(GoogleTests_run ${TestScope})
#add_executable(GoogleTests_run SetTests.cpp)
#add_executable(GoogleTests_run MultisetTests.cpp)

target_link_libraries(GoogleTests_run DeltaLibrary)
target_link_libraries(GoogleTests_run gtest gtest_main)