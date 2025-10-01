project(SDLUtils CXX)

set(CXX_STANDARD_REQUIRED 20)

add_library(
  sdl_utils

  sdl_utils.hpp
  sdl_utils.cc
)

find_package(SDL3)

if(SDL_STATIC)
  message("sdl3-utils using STATIC SDL3")
  target_link_libraries(sdl_utils PRIVATE SDL3::SDL3-static)
else()
  message("sdl3-utils using SHARED SDL3")
  target_link_libraries(sdl_utils PRIVATE SDL3::SDL3)
endif(SDL_STATIC)

target_include_directories(sdl_utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
