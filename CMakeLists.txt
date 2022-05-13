cmake_minimum_required(VERSION 3.0.0)
project(wurst VERSION 0.1.0)

include(CTest)
enable_testing()


include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(wxWidgets-3.1.6)
add_executable(wurst cApp.cpp cMain.cpp)
target_link_libraries(wurst wx::net wx::core wx::base)

target_precompile_headers(wurst PRIVATE "pch.h")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
