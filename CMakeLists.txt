cmake_minimum_required(VERSION 3.17)
project(arcade)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -fno-gnu-unique -fpermissive)
add_executable(arcade
        src/Main.cpp
        src/ArcadeBorne.cpp
        src/ArcadeParse.cpp)
target_include_directories(arcade PUBLIC includes)
target_link_libraries(arcade PUBLIC dl)
add_subdirectory(lib/Display/ncurses)
add_subdirectory(lib/Display/sdl2)
add_subdirectory(lib/Display/sfml)
add_subdirectory(lib/Game/Pacman)
add_subdirectory(lib/Game/Menu)
add_subdirectory(lib/Game/Nibbler)
add_dependencies(arcade pacman Menu nibbler ncurses sfml sdl2)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_SOURCE_DIR}/arcade)
add_custom_command(TARGET arcade POST_BUILD COMMAND cp arcade ${PROJECT_SOURCE_DIR})