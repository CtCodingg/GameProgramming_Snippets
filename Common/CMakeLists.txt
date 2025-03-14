cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SDL3_GIT_DIR "" CACHE STRING "")
set(SDL3_IMAGE_GIT_DIR "" CACHE STRING "")
set(SDL3_IMAGE_BIN_DIR "" CACHE STRING "")
find_package(SDL3 REQUIRED)

set(HEADERS
 Vector.hpp
 iGame.hpp
 iActor.hpp
 Actor.hpp
 iComponent.hpp
 Component.hpp
)
set(SOURCES 
 Actor.cpp
 Component.cpp
)

set(ALL
  ${HEADERS}
  ${SOURCES}
)

add_library(Common STATIC ${ALL})
target_include_directories(Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Common PUBLIC ${SDL3_GIT_DIR}/include)
target_include_directories(Common PUBLIC ${SDL3_IMAGE_GIT_DIR}/include)
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)

link_directories(${SDL3_IMAGE_BIN_DIR}/lib)

target_link_libraries(Common PRIVATE SDL3::SDL3)
target_link_libraries(Common PRIVATE SDL3_image)

install(TARGETS Common DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)