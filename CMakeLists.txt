project(SDLUtils CXX)

set(CXX_STANDARD_REQUIRED 23)

add_library(
  sdl_utils

  sdl_utils.hpp
  sdl_utils.cc
)

find_package(SDL3)

target_link_libraries(sdl_utils PRIVATE SDL3::SDL3)
target_include_directories(sdl_utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
