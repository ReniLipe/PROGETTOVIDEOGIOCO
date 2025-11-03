cmake_minimum_required(VERSION 3.20)
project(PROGETTOVIDEOGIOCO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------ ENABLE TESTING ------------------
include(CTest)
enable_testing()

# Evita warning pkg-config su Windows
set(PKG_CONFIG_EXECUTABLE "" CACHE FILEPATH "Path to pkg-config" FORCE)

# Fix GTest su Windows CRT
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# ------------------ SFML 3 via FetchContent ------------------
include(FetchContent)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(sfml)

# ------------------ INCLUDE HEADERS ------------------
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

# ------------------ COPY SFML DLLs FOR TESTS ------------------
add_custom_command(TARGET UnitTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/_deps/sfml-build/bin/sfml-graphics-d-3.dll"
        "${CMAKE_BINARY_DIR}/_deps/sfml-build/bin/sfml-window-d-3.dll"
        "${CMAKE_BINARY_DIR}/_deps/sfml-build/bin/sfml-system-d-3.dll"
        $<TARGET_FILE_DIR:UnitTests>
        COMMENT "Copy SFML DLLs for UnitTests.exe"
)

# ------------------ REGISTER TESTS ------------------
include(GoogleTest)
gtest_discover_tests(UnitTests)
