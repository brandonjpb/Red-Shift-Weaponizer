# test/CMakeLists.txt
find_package(GTest REQUIRED)

add_executable(RedShiftTests
    weapon_tests.cpp
)
target_link_libraries(RedShiftTests PRIVATE
    WeaponizerCore
    GTest::GTest
    GTest::Main
)
add_test(NAME WeaponTests COMMAND RedShiftTests)