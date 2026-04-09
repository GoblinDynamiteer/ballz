cmake_minimum_required(VERSION 3.16)

project(ballz LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BALLZ_SOURCES
    main.c
    game/balls.c
    game/draw.c
    game/event.c
    game/load.c
)

set(BALLZ_HEADERS
    def.h
    game/balls.h
    game/draw.h
    game/event.h
    game/load.h
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf)

add_executable(ballz
    ${BALLZ_SOURCES}
)

target_include_directories(ballz PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} game/)
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

find_program(CLANG_FORMAT_BIN NAMES clang-format)
if(CLANG_FORMAT_BIN)
    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT_BIN} -i ${BALLZ_SOURCES} ${BALLZ_HEADERS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Formatting C sources with clang-format"
    )

    add_custom_target(
        format-check
        COMMAND ${CLANG_FORMAT_BIN} --dry-run --Werror ${BALLZ_SOURCES} ${BALLZ_HEADERS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Checking C formatting with clang-format"
    )
endif()

unset(CLANG_TIDY_BIN CACHE)
find_program(CLANG_TIDY_BIN NAMES clang-tidy PATHS /usr/bin /usr/local/bin NO_DEFAULT_PATH)
if(CLANG_TIDY_BIN)
    add_custom_target(
        lint
        COMMAND
            ${CLANG_TIDY_BIN}
            -p=${CMAKE_BINARY_DIR}
            --warnings-as-errors=*
            ${BALLZ_SOURCES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running clang-tidy"
    )
endif()
