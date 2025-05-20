#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "../include/inputGetter.h"
#include "../include/weaponAssembler.h"

using namespace std;

//for input
void simulateInput(const string& input) {
    static stringstream ss;
    ss.str(input);
    ss.clear();
    cin.rdbuf(ss.rdbuf());
}

// Resets std::cin to its normal state after each test.
void resetInput() {
    cin.rdbuf(cin.rdbuf());
    cin.clear();
}

// Captures all std::cout output while running a function.
// Useful for validating that error messages or specific prompts are printed.
string captureOutput(function<void()> func) {
    testing::internal::CaptureStdout();
    func();
    return testing::internal::GetCapturedStdout();
}

class WeaponTests : public ::testing::Test {
protected:
    void SetUp() override {
        receiverChoice = 1;
        isExplosiveFrame = false;
    }
    void TearDown() override {
        resetInput();
    }
};

// Test 1: Validates that AI Sight (option 5) is only allowed with Full Auto receivers.
// This test checks that the fallback to option 2 occurs if 5 is invalid.
TEST_F(WeaponTests, AISightNeedsFullAuto) {
    receiverChoice = 1; // Not full auto
    simulateInput("5\n2\n");
    int sight = getSightInput();
    EXPECT_EQ(sight, 2); // Should fallback
    EXPECT_NE(sight, 5); // Should not accept AI sight
}

// Test 2: Checks that explosive frame skips the barrel selection
// For explosive builds, barrel selection is predetermined
TEST_F(WeaponTests, ExplosiveGunAutoBarrel) {
    isExplosiveFrame = true;
    simulateInput("4\n"); // Input that should be ignored
    int barrel = getBarrelInput();
    EXPECT_EQ(barrel, 2); // Barrel should default
}

// Test 3: Ensures getFrameInput() can recover from invalid string input like "xyz".
// This simulates common user error and tests of input parsing.
TEST_F(WeaponTests, FrameInputBadData) {
    simulateInput("xyz\n4\n"); // Invalid input, then valid
    int frame = getFrameInput();
    EXPECT_EQ(frame, 4); // Valid recovery
    EXPECT_TRUE(isExplosiveFrame); // Frame 4 sets explosive flag
}

// Test 4: Verifies that passing invalid part numbers to assembleWeapon()
// triggers proper error messages (e.g., "Invalid").
TEST_F(WeaponTests, InvalidPartsShowError) {
    auto out = captureOutput([] {
        assembleWeapon(99, 1, 1, 1); // Frame 99 is invalid
    });
    EXPECT_TRUE(out.find("Invalid") != string::npos);
}

// Test 5: Confirms that max range calculation in assembleWeapon()
// never produces negative values, even with range-reducing parts.
TEST_F(WeaponTests, GunRangeMinimum) {
    assembleWeapon(1, 3, 1, 1); // Physical + Full Auto + Short Barrel
    EXPECT_GE(finalWeapon[5], 0); // Max range must be non-negative
}

// Test 6: Simulates selecting an invalid receiver (2) while explosive frame is active.
// This test currently fails if 2 is accepted, revealing a logic gap in validation.
TEST_F(WeaponTests, ExplosiveGunReceiverCheck) {
    isExplosiveFrame = true;
    simulateInput("2\n5\n"); // 2 should be rejected, 5 is fallback
    int receiver = getReceiverInput();
    EXPECT_EQ(receiver, 5); // Should only accept explosive receivers
}

// Test 7: Enters a long stream of valid inputs quickly to simulate real user input behavior.
// Ensures the input system doesn't misalign or skip prompts.
TEST_F(WeaponTests, MultipleInputsTogether) {
    simulateInput("1\n2\n3\n4\n5\n6\n");
    int frame = getFrameInput();
    int receiver = getReceiverInput();
    int barrel = getBarrelInput();
    int sight = getSightInput();

    EXPECT_TRUE(frame >= 1 && frame <= 4);
    EXPECT_TRUE(receiver >= 1 && receiver <= 5);
    EXPECT_TRUE(barrel >= 1 && barrel <= 4);
    EXPECT_TRUE(sight >= 1 && sight <= 5);
}

// Test 8: Should not allow sniper scope with shotgun receiver
TEST_F(WeaponTests, SniperScopeOnShotgun) {
    // Setup
    receiverChoice = 3; // Shotgun receiver (assuming 3 is shotgun)
    simulateInput("4\n"); // Try to select sniper scope (4)

    // Execution
    int sight = getSightInput();

    // Verification - this should FAIL because:
    // Shotguns shouldn't be compatible with sniper scopes
    EXPECT_NE(sight, 4);

    // Proper behavior would reject this and force a different sight
}

// Test 9: Full-auto receiver should enforce minimum damage dice
TEST_F(WeaponTests, FullAutoDamageMath) {
    // Setup full-auto receiver (reduces die quality by 2)
    simulateInput("1\n3\n2\n1\n"); // Physical frame + full auto + standard barrel + iron sights

    assembleWeapon(1, 3, 2, 1);
    EXPECT_EQ(finalWeapon[3], 1); // Should clamp to d4

    resetInput();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}