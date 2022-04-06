cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS ON)
add_compile_options(-fno-gnu-unique)
add_library(sfml SHARED src/sfml.cpp)
target_include_directories(sfml PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/lib/Display/sfml/includes)
target_link_libraries(sfml PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)
add_compile_options(-Wall -Wextra)
set_target_properties(sfml PROPERTIES PREFIX "arcade_")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_SOURCE_DIR}/lib/arcade_sfml.so)
add_custom_command(TARGET sfml  POST_BUILD COMMAND cp arcade_sfml.so ${PROJECT_SOURCE_DIR}/lib)