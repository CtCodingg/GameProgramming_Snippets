cmake_minimum_required(VERSION 3.10)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(HEADERS
 Game.hpp
 Vector.hpp
)
set(SOURCES 
 Game.cpp
 main.cpp
)

set(ALL
  ${HEADERS}
  ${SOURCES}
)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../External/SDL/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../External/SDL/include)

add_executable(1_Basic2D WIN32 ${ALL})

target_link_libraries(1_Basic2D PRIVATE SDL2 SDL2_image SDL2main SDL2_ttf SDL2_mixer)

install(TARGETS 1_Basic2D DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../External/SDL/lib/ DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)