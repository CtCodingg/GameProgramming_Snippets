cmake_minimum_required(VERSION 3.10)

set(PROJECT 2_GameObjects)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(HEADERS
 Game.hpp
 Vector.hpp
 AnimSpriteComponent.hpp
 BGSpriteComponent.hpp
 SpriteComponent.hpp
 Actor.hpp
 Component.hpp
 Math.hpp
 Ship.hpp
)
set(SOURCES 
 Game.cpp
 main.cpp
 Actor.cpp
 Component.cpp
 AnimSpriteComponent.cpp
 BGSpriteComponent.cpp
 SpriteComponent.cpp
 Math.cpp
 Ship.cpp
)

set(ALL
  ${HEADERS}
  ${SOURCES}
)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../External/SDL/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../External/SDL/include)

add_executable(${PROJECT} WIN32 ${ALL})

target_link_libraries(${PROJECT} PRIVATE SDL2 SDL2_image SDL2main SDL2_ttf SDL2_mixer)

install(TARGETS ${PROJECT} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../External/SDL/lib/ DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/ DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/Assets)