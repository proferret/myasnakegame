cmake_minimum_required(VERSION 3.15)

project(myasnakegame C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)


set(HOMEBREW_PREFIX "/opt/homebrew")
set(RAYLIB_INCLUDE_DIR "${HOMEBREW_PREFIX}/include")
set(RAYLIB_LIB_DIR "${HOMEBREW_PREFIX}/lib")

if(NOT EXISTS ${RAYLIB_INCLUDE_DIR})
    message(WARNING "Homebrew directory not found: ${RAYLIB_INCLUDE_DIR}")
endif()
if(NOT EXISTS ${RAYLIB_LIB_DIR})
    message(WARNING "Homebrew libraries directory not found: ${RAYLIB_LIB_DIR}")
endif()


set(SOURCE_FILES
        src/main.c
        src/apple.c
        src/controllers.c
        src/score.c
        src/snake.c
        src/timer.c
)

add_executable(myasnakegame ${SOURCE_FILES})


target_include_directories(myasnakegame
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${RAYLIB_INCLUDE_DIR}
)


target_link_directories(myasnakegame PRIVATE ${RAYLIB_LIB_DIR})


target_link_libraries(myasnakegame PRIVATE
        raylib
        "-framework CoreVideo"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework GLUT"
        "-framework OpenGL"
)

