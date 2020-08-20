cmake_minimum_required(VERSION 3.15)
project(imgui CXX)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} -std=c++11 -fPIC")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp" )
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_LIST_DIR}/src/include/*.h" )
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
include_directories("${CMAKE_CURRENT_LIST_DIR}/include/imgui")


#target_compile_definitions(glad PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
# adding -fPIC for shared
set_property(TARGET imgui PROPERTY POSITION_INDEPENDENT_CODE ON)
