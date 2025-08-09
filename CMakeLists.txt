cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main 
    src/main.cpp
    src/Engine.cpp
    src/TextureHolder.cpp
    src/Personage.cpp
    src/Bob.cpp
    src/Thomas.cpp
    src/Level.cpp
)
add_custom_command(TARGET main PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/resources"
    "$<TARGET_FILE_DIR:main>/resources"
  COMMENT "Copying resources to output directory"
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::Audio
)
