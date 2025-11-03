cmake_minimum_required(VERSION 3.20)
project(PROGETTOVIDEOGIOCO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_USE_STATIC_STD_LIBS FALSE)
set(BUILD_SHARED_LIBS TRUE)

# Fix per Windows + MinGW (GTest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# ------------------ SFML 3.0 via FetchContent ------------------
include(FetchContent)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(sfml)

# Include headers
include_directories(include)

# ------------------ EXECUTABLE GIOCO ------------------
add_executable(PROGETTOVIDEOGIOCO
        main.cpp
        MAPPA.cpp
        Giocatore.cpp
        VistAstar.cpp
)

target_link_libraries(PROGETTOVIDEOGIOCO
        sfml-graphics
        sfml-window
        sfml-system
)

# Copia font dopo la build
add_custom_command(TARGET PROGETTOVIDEOGIOCO POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/arial-font
        $<TARGET_FILE_DIR:PROGETTOVIDEOGIOCO>/assets/arial-font
)

# ------------------ GOOGLE TEST ------------------
add_subdirectory(external/googletest)

# Target per i test
add_executable(UnitTests
        tests/test_main.cpp
        tests/GiocatoreTest.cpp
        Giocatore.cpp
        MAPPA.cpp
)

target_include_directories(UnitTests PRIVATE
        ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include
)

target_link_libraries(UnitTests PRIVATE
        gtest
        gtest_main
        sfml-graphics
        sfml-window
        sfml-system
)

# ------------------ Copia DLL SFML per UnitTests ------------------
# Dal momento che le DLL sono già nella cartella cmake-build-debug, basta copiarle accanto all'eseguibile.
add_custom_command(TARGET UnitTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/sfml-graphics-d-3.dll"
        "${CMAKE_BINARY_DIR}/sfml-window-d-3.dll"
        "${CMAKE_BINARY_DIR}/sfml-system-d-3.dll"
        $<TARGET_FILE_DIR:UnitTests>
        COMMENT "Copy SFML DLLs next to UnitTests.exe"
)

# Registra i test con CTest
add_test(NAME GiocatoreTest COMMAND UnitTests)
