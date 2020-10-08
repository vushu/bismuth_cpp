cmake_minimum_required(VERSION 3.15)
project(nanovg)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} -std=c++11 -fPIC")
add_library(${PROJECT_NAME}
  include/nanovg/fontstash.h
  include/nanovg/nanovg_gl.h
  include/nanovg/nanovg.h
  include/nanovg/stb_truetype.h
  include/nanovg/nanovg.c
  include/nanovg/nanovg_gl_utils.h
  include/nanovg/stb_image.h
  )
#target_compile_definitions(glad PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
# adding -fPIC for shared
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
