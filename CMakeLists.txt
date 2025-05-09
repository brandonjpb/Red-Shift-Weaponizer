cmake_minimum_required(VERSION 3.15)
project(RedShiftWeaponizer)

set(CMAKE_CXX_STANDARD 20)

# First create a STATIC library with all shared code
add_library(WeaponizerCore STATIC
    src/inputGetter.cpp
    src/weaponAssembler.cpp
)
target_include_directories(WeaponizerCore PUBLIC include/)

# Then create main executable
add_executable(RedShiftWeaponizer
    src/main.cpp
)
target_link_libraries(RedShiftWeaponizer PRIVATE WeaponizerCore)

# Tests
enable_testing()
add_subdirectory(test)