cmake_minimum_required(VERSION 3.11) # Use fetchcontent
project(cengine VERSION 0.1.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(
  ${PROJECT_NAME}
  src/main.c
  src/texture.c
)

# target_include_directories(cengine PRIVATE
#   include/
# )

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
include(FetchContent)

# if(SDL3_FOUND)
#   message(STATUS "SDL3 found!")
# else()
#   message(STATUS "SDL3 not found. Building from source...")
#   FetchContent_Declare(
#     SDL3
#     GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
#     GIT_TAG        main
#   )
#   FetchContent_MakeAvailable(sdl3)
# endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
  SDL3::SDL3
  SDL3_image::SDL3_image
)

# Make Visual Studio invoke in the correct directory
# if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#   set_target_properties(desertedcraft PROPERTIES
#     VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:desertedcraft>"
#   )
# elseif("GNU|Clang")
#   target_compile_options(desertedcraft PRIVATE
#     -Wall
#     -Wextra
#     -pedantic-errors
#   )
# endif()
#
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
