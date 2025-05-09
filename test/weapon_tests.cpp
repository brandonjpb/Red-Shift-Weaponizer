#include "gtest/gtest.h"
#include "inputGetter.h"
#include "weaponAssembler.h"
#include <sstream>

// Test 1: Basic input test
TEST(InputTest, FrameInputAcceptsValidNumbers) {
    // Simulate user entering '2'
    std::stringstream input("2");
    std::cin.rdbuf(input.rdbuf());

    int result = getFrameInput();
    EXPECT_EQ(result, 2); // Simple check
}

// Test 2: Control flow test - checks explosive frame special case
TEST(InputTest, ExplosiveFrameSkipsBarrelChoice) {
    isExplosiveFrame = true;
    int result = getBarrelInput(); // Should auto-return 2
    EXPECT_EQ(result, 2); // Default barrel for explosives
    isExplosiveFrame = false; // Reset
}

// Test 3: Edge case test - invalid input recovery
TEST(InputTest, HandlesBadInput) {
    // Simulate user entering 'abc' then '3'
    std::stringstream input("abc\n3");
    std::cin.rdbuf(input.rdbuf());

    int result = getSightInput();
    EXPECT_EQ(result, 3); // Should recover and return valid input
}

// Test 4: Basic assembly test - just checks output exists
TEST(AssemblyTest, WeaponAssemblyRuns) {
    testing::internal::CaptureStdout();
    assembleWeapon(1, 1, 1, 1); // Simplest combo
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty()); // Just verify it printed something
}

// Test 5: Checks AI sight requirement
TEST(AssemblyTest, AISightNeedsFullAuto) {
    testing::internal::CaptureStdout();
    assembleWeapon(3, 3, 2, 5); // Valid AI combo
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("765") != std::string::npos); // Check for AI value
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}