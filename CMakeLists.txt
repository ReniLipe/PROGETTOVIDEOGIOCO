cmake_minimum_required(VERSION 3.20)
project(PROGETTOVIDEOGIOCO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML via FetchContent
include(FetchContent)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(sfml)

# Include headers
include_directories(include)

# Executable target
add_executable(PROGETTOVIDEOGIOCO
        main.cpp
        MAPPA.cpp
)

# Link SFML libraries
target_link_libraries(PROGETTOVIDEOGIOCO
        sfml-graphics
        sfml-window
        sfml-system
)

# Copy DLLs after build (debug version)
add_custom_command(TARGET PROGETTOVIDEOGIOCO POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${sfml_BINARY_DIR}/bin/sfml-graphics-d-3.dll
        ${sfml_BINARY_DIR}/bin/sfml-window-d-3.dll
        ${sfml_BINARY_DIR}/bin/sfml-system-d-3.dll
        $<TARGET_FILE_DIR:PROGETTOVIDEOGIOCO>
)
