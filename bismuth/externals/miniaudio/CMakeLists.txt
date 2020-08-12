cmake_minimum_required(VERSION 3.15)
project(miniaudio)

file(GLOB_RECURSE header_list
    "${CMAKE_CURRENT_LIST_DIR}/include/*h")

add_library(${PROJECT_NAME} ${header_list} src/miniaudio.c)
#target_compile_definitions(glad PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)
target_include_directories(miniaudio PUBLIC include/)
# adding -fPIC for shared
set_property(TARGET miniaudio PROPERTY POSITION_INDEPENDENT_CODE ON)
