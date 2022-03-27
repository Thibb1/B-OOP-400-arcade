cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS ON)
add_library(nibbler SHARED src/Nibbler.cpp)
add_compile_options(-fno-gnu-unique -Wall -Wextra)
target_include_directories(nibbler PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/lib/Game/Nibbler/includes)
set_target_properties(nibbler PROPERTIES PREFIX "arcade_")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_SOURCE_DIR}/lib/arcade_nibbler.so)
add_custom_command(TARGET nibbler POST_BUILD COMMAND cp arcade_nibbler.so ${PROJECT_SOURCE_DIR}/lib)