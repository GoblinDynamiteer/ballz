cmake_minimum_required(VERSION 3.16)

project(ballz LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf)

add_executable(ballz
    main.c
    game/balls.c
    game/draw.c
    game/event.c
    game/load.c
)

target_include_directories(ballz PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(
    ballz
    PRIVATE BALLZ_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)
target_link_libraries(
    ballz
    PRIVATE
        PkgConfig::SDL2
        PkgConfig::SDL2_IMAGE
        PkgConfig::SDL2_TTF
        m
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ballz PRIVATE -Wall -Wextra -g)
endif()
