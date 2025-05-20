# Peer Code Review by Subigya Parajuli
**Reviewee:** Brandon

---

## Initial Thoughts
Code itself was a little confusing and out of structure.

---

## ARCHITECTURE Problems

### Issue #1: GitHub Format
+ No `README.md` file visible - for user description.
    - While running the code I was very confused by the way the program is meant to be run.
    - User-based documentation is a must-have.
    - [link](https://imgur.com/a/If3G6Vp)

### Issue #2: Main "Theme" not consistent
+ The `main.cpp` consists of multiple `cout` statements in different formatting styles.
+ Better practice would be to use a centralized `display()` function so the UI aligns visually.
    - [Before](https://imgur.com/WTVuh85) VS [After](https://imgur.com/IvjVIHj)
    - [UI Before](https://imgur.com/a/5QS5zg6) VS [UI After](https://imgur.com/a/B60UPmY)
    + Result: Cleaner interface and better presentation.

---

## Modularity & Readability Problems

### Issue #1: Variable Names & Lack of Comments
+ Example: [Here](https://imgur.com/a/GJTYvjE)
    - Constant theme of not naming variables properly.
    - Major readability issues.
    - Barely any comments present in the files to clarify logic for future developers.

### Issue #2: Global Variables Being Modified Across Files
+ Creates major traceability and safety issues.
+ Example: `isExplosiveFrame`, `selectedBarrel` can be modified in both `inputGetter.cpp` and `weaponAssembler.cpp`
    - This made testing more difficult.
    - Recommendation: Use scoped/local variables instead of globals wherever possible.

### Issue #3: Poor Input Structuring in `main()`
+ Strongly recommend usage of `struct` to organize user input logic.
    - Example: [Better Struct Design](https://imgur.com/UtASalW)
    - How to implement: [Image](https://imgur.com/sKMOXqc)
    - Header Structure: [Here](https://imgur.com/a/3DvEqnf)
    + Benefits:
        - Clearer logic and encapsulation.
        - Avoids repeated global state mutation.
        - Easier to scale code for future features.

---

## Code Bugs That Crash the Code

### Issue #1: Missed Input Validation
+ If the user enters multiple inputs (e.g., `1 2 3`), the code breaks.
    - [Crash Example](https://imgur.com/a/LPBjjto)
    - Reason: `cin` leaves leftover buffer entries (e.g., `2 3` stay in input stream).
    - Result: `getReceiverInput()` grabs a leftover input instead of prompting correctly.
    - Fix: Add input sanitization and stream flushing logic.

---

## Code Structure & CMake

+ The current CMake system builds successfully, which is a positive.
+ However, improvements are needed in project structure:
    - The `CMakeLists.txt` at the root correctly separates `WeaponizerCore` and `RedShiftWeaponizer`, but the test file organization could be improved.
    - `RedShiftTests` should be clearly isolated into a `test/` folder with its own subdirectory structure for test modules if the project grows.
    - Test files like `weapon_tests.cpp` should follow a clear naming convention (e.g., `test_input.cpp`, `test_assembler.cpp`) to improve scalability.
---

## 5 Official Google Test Cases

> ✅ These are the 5 official tests submitted as part of the assignment requirement.

1. **AISightNeedsFullAuto**
    - Ensures AI Sight (option 5) only works with Full Auto receiver.
    - Validates `getSightInput()` compatibility logic for `receiverChoice == 3`.

2. **ExplosiveGunAutoBarrel**
    - Explosive frame auto-assigns barrel without user input.
    - Tests bypass logic in `getBarrelInput()` when `isExplosiveFrame == true`.

3. **InvalidPartsShowError**
    - Passes invalid configuration (e.g., 99) to weapon assembler.
    - Verifies that `assembleWeapon()` has error handling for nonsensical part combos.

4. **MultipleInputsTogether**
    - Simulates user typing `1 2 3 4 5` too fast.
    - Exposes broken `cin` input buffering and misaligned prompts.

5. **SniperScopeOnShotgun**
    - Chooses sniper scope with shotgun receiver.
    - Reveals lack of validation in `getSightInput()` for this invalid pairing.
    - Test fails correctly and shows a missed logic branch.

---

## Additional Google Tests Added (Nice-To-Have)

6. **FrameInputBadData**
    - Simulates random bad input like `"xyz"`
    - Verifies program doesn't crash and loops until valid entry.

7. **GunRangeMinimum**
    - Full Auto + Short Barrel combo should never result in negative range.
    - Confirms final value is clamped properly in `assembleWeapon()`.

8. **ExplosiveGunReceiverCheck**
    - Tries explosive frame with a semi-auto receiver.
    - Ensures logic in `getReceiverInput()` blocks invalid match.

9. **FullAutoDamageMath**
    - Full Auto's -2 damage modifier shouldn’t push weapon below d4.
    - Initially failed due to incorrect expectations, but now verifies clamping logic.

---

## Architecture & Design Feedback

+ **Modularization Needed:**
    - Logic (like `getFrameInput()`, `assembleWeapon()`) is spread across multiple files but lacks encapsulation.
    - Suggested fix: group related logic into modules/classes (e.g., `Weapon`, `InputManager`, etc.).

+ **Global State Dependency:**
    - Multiple parts of the code rely on shared globals (`isExplosiveFrame`, `receiverChoice`), making the codebase fragile.
    - Refactor into parameter-passing + local return values instead.

+ **UI Consistency & Theming:**
    - Use centralized display functions for prompts and menus.
    - Ensures better presentation and future reusability (such as skinning, CLI themes, or localization).

---

**Final Recommendation:**  
The project shows promise but needs work on readability, test safety, and modular architecture. You’ve done a great job with some core logic and the base functionality, but to take this from a student project to something production-ready, serious refactoring and cleanup are needed—especially around input handling, global state, and logic isolation.

