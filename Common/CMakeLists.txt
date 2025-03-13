cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_compile_definitions(COMMON_EXPORTS)

set(HEADERS
 Vector.hpp
 iGame.hpp
 iActor.hpp
 Actor.hpp
)
set(SOURCES 
 Actor.cpp
)

set(ALL
  ${HEADERS}
  ${SOURCES}
)

add_library(Common STATIC ${ALL})
target_include_directories(Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS Common DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/Common)