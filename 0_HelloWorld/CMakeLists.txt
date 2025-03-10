cmake_minimum_required(VERSION 3.10)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(SDL3 REQUIRED)

set(HEADERS
 Game.hpp
)
set(SOURCES 
 Game.cpp
 main.cpp
)

set(ALL
  ${HEADERS}
  ${SOURCES}
)

add_executable(0_HelloWorld ${ALL})
include_directories(${CMAKE_INSTALL_PREFIX}/include)
target_link_libraries(0_HelloWorld PRIVATE Common SDL3::SDL3)

install(TARGETS 0_HelloWorld DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)