cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS ON)
add_compile_options(-fno-gnu-unique)
add_library(sdl2 SHARED src/sdl2.cpp)
target_include_directories(sdl2 PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/lib/Display/sdl2/includes)
target_link_libraries(sdl2 PRIVATE SDL2 SDL2_image SDL2_mixer SDL2_ttf)
add_compile_options(-Wall -Wextra)
set_target_properties(sdl2 PROPERTIES PREFIX "arcade_")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_SOURCE_DIR}/lib/arcade_sdl2.so)
add_custom_command(TARGET sdl2 POST_BUILD COMMAND cp arcade_sdl2.so ${PROJECT_SOURCE_DIR}/lib)