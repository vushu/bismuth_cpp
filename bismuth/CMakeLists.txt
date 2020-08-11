cmake_minimum_required(VERSION 3.15)

set(PROJECT_VERSION "1.0.0")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(ENTT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/externals/entt")
set(STB_IMAGE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/externals/stb")
set(GLM_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/externals/glm")
#set(CATCH2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/externals/catch2")
set(EMSCRIPTEN_INCLUDE_DIRS "/home/vushu/coding/repos/emsdk/upstream/emscripten/system/include")

include(GNUInstallDirs)

project(bismuth VERSION ${PROJECT_VERSION} DESCRIPTION "Small gamelib")

file(GLOB_RECURSE source_list
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

file(GLOB_RECURSE header_list
    "${CMAKE_CURRENT_LIST_DIR}/include/*h")

add_library(${PROJECT_NAME} SHARED ${header_list} ${source_list})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION})

#GLAD
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/externals/glad)

#message(STATUS "GLM included at ${GLM_INCLUDE_DIRS}")
if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${GLM_INCLUDE_DIRS}
        ${STB_IMAGE_INCLUDE_DIR}
        ${ENTT_INCLUDE_DIR}
        #${CATCH2_INCLUDE_DIRS}
        #${EMSCRIPTEN_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        src)
else()
    target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${GLM_INCLUDE_DIRS}
        ${STB_IMAGE_INCLUDE_DIR}
        ${ENTT_INCLUDE_DIR}
        #${CATCH2_INCLUDE_DIRS}
        ${EMSCRIPTEN_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        src)
endif()

#window compatibility
set(CMAKE_WINDOW_EXPORT_ALL_SYMBOLS ON)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    message("Compiling to WASM")
    target_link_libraries(${PROJECT_NAME} "-s USE_GLFW=3")
    #target_link_libraries(${PROJECT_NAME} "-s STB_IMAGE=1")
    target_link_libraries(${PROJECT_NAME} glad)

else()
    find_package(glfw3 3.3 REQUIRED)
    #find_package(glm REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)
endif()

add_subdirectory(tests)
add_test(NAME tests COMMAND bismuth_test)



#export(TARGETS ${PROJECT_NAME} FILE bismuthConfig.cmake)
