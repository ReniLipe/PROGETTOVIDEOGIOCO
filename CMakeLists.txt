cmake_minimum_required(VERSION 3.20)
project(PROGETTOVIDEOGIOCO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SFML_USE_STATIC_STD_LIBS FALSE)
set(BUILD_SHARED_LIBS TRUE)
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
        Giocatore.cpp
        Giocatore.h
        VistAstar.cpp
        VistAstar.h
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
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:PROGETTOVIDEOGIOCO>
)
