cmake_minimum_required(VERSION 3.10)
project(GameProgramming_Snippets)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Common)
add_subdirectory(0_HelloWorld)
add_subdirectory(1_Basic2D)
add_subdirectory(2_GameObjects)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
include(CPack)