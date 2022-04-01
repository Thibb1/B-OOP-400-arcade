cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS ON)
add_library(pacman SHARED src/Ghost.cpp src/Pacman.cpp)
add_compile_options(-fno-gnu-unique -Wall -Wextra)
target_include_directories(pacman PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/lib/Game/Pacman/includes)
set_target_properties(pacman PROPERTIES PREFIX "arcade_")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_SOURCE_DIR}/lib/arcade_pacman.so)
add_custom_command(TARGET pacman POST_BUILD COMMAND cp arcade_pacman.so ${PROJECT_SOURCE_DIR}/lib)