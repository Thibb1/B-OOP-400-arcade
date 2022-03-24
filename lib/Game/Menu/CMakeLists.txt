cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS ON)
add_compile_options(-fno-gnu-unique)
add_library(Menu SHARED src/Menu.cpp)
target_include_directories(Menu PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/lib/Game/Menu/includes)
target_link_libraries(Menu PRIVATE SDL2 SDL2_image SDL2_ttf)
add_compile_options(-Wall -Wextra)
set_target_properties(Menu PROPERTIES PREFIX "arcade_")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_SOURCE_DIR}/lib/arcade_Menu.so)
add_custom_command(TARGET Menu POST_BUILD COMMAND cp arcade_Menu.so ${PROJECT_SOURCE_DIR}/lib)
