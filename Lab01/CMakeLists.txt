cmake_minimum_required(VERSION 3.16)
project(Lab01_OpenGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.9
)
FetchContent_MakeAvailable(glfw)

# GLEW (через glew-cmake)
FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG glew-cmake-2.2.0
)
FetchContent_MakeAvailable(glew)

# GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

add_executable(Lab01
  src/main.cpp
  src/core/Shader.cpp
  src/modes/CurveMode.cpp
)

target_include_directories(Lab01 PRIVATE
  src
  src/core
  src/modes
  src/geometry
)

target_link_libraries(Lab01 PRIVATE
  OpenGL::GL
  glfw
  libglew_static
  glm
)

# копіюємо шейдери поруч з exe в build/…/shaders
file(GLOB SHADERS "shaders/*")
add_custom_command(TARGET Lab01 POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Lab01>/shaders
)
foreach(shader ${SHADERS})
  add_custom_command(TARGET Lab01 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${shader} $<TARGET_FILE_DIR:Lab01>/shaders
  )
endforeach()