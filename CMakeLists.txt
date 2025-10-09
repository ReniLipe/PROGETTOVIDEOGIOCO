cmake_minimum_required(VERSION 4.0)
project(PROGETTOVIDEOGIOCO)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL SYSTEM)

FetchContent_MakeAvailable(SFML)

add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE SFML::Graphics)
target_include_directories(main PRIVATE ${SFML_SOURCE_DIR}/include)
target_compile_definitions(main PRIVATE SFML_STATIC)
