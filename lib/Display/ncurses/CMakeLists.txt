cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS ON)
add_library(ncurses SHARED src/ncurses.cpp)
add_compile_options(-fno-gnu-unique)
target_link_libraries(ncurses PRIVATE ncursesw png)
target_include_directories(ncurses PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/lib/Display/ncurses/includes)
set_target_properties(ncurses PROPERTIES PREFIX "arcade_")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_SOURCE_DIR}/lib/arcade_ncurses.so)
add_custom_command(TARGET ncurses POST_BUILD COMMAND cp arcade_ncurses.so ${PROJECT_SOURCE_DIR}/lib)
