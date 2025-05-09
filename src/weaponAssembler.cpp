#include "weaponAssembler.h"

using namespace std;

double finalWeapon[7];


// --- Weapon Data Tables ---

// [0] = weight
// [1] = hit modifier
// [2] = die quantity
// [3] = die quality (step up or down)
// [4] = min range
// [5] = max range
// [6] = value

// Frames                   
double physicalFrame[7] = { 7.5,  0, 2, 2,  30,  150, 45 };
double plasmaFrame[7] = { 10,   0, 3, 2,  40,  200, 100 };
double laserFrame[7] = { 8,    0, 3, 2,  60,  300, 85 };
double explosiveFrame[7] = { 15,   1, 6, 1,  15,   50, 170 };

// Receivers
double oneShotReceiver[7] = { -1, 2, 1,  1,  20,  100, 20 };
double semiAutoReceiver[7] = { 1,  1, 0,  1,   0,    0,  0 };
double fullAutoReceiver[7] = { 2,  0, 3, -2, 0, -50, 55 };
double grenadeLobber[7] = { 4,  0, 0,  0,   0,   50, 120 };  // Compatible only with explosive frame
double rocketLauncher[7] = { 7,  2, 2,  2,  100,  500, 225 };  // Compatible only with explosive frame

// Barrels
double shortBarrel[7] = { -2, -1, 0, 1,  -50, -100, 25 };
double regularBarrel[7] = { 0,   0, 0, 0,    0,    0, 30 };
double longBarrel[7] = { 1,   1, 0, 0,   25,   25, 50 };
double sniperBarrel[7] = { 4,   2, 2, 1,   75,  150, 120 };

// Sights
double ironSights[7] = { -1, -1, 0, 0,   0,    0, 15 };
double twoXscope[7] = { 1,   1, 0, 0,   0,   50, 50 };
double fiveXscope[7] = { 3,   1, 0, 0,  50,  100, 95 };
double holoNoAI[7] = { 2,   2, 0, 0, -50,  -25, 120 };
double holoWithAI[7] = { 8,   5, 0, 0, -50, -100, 765 }; // Requires full auto frame

// Pointers for the selected parts
double* selectedFrame = nullptr;
double* selectedReceiver = nullptr;
double* selectedBarrel = nullptr;
double* selectedSight = nullptr;

// Sums values in same indices for corresponding stat sum
void calculateWeapon(double* selectedFrame, double* selectedReceiver, double* selectedBarrel, double* selectedSight) {
    for (int i = 0; i < 7; i++) {
        finalWeapon[i] = selectedFrame[i] + selectedReceiver[i] + selectedBarrel[i] + selectedSight[i];
    }
}

// Main function that assembles the weapon.
// It accepts the user selections for frame, receiver, barrel, and sight,
// then selects the appropriate data arrays, calculates the final stats, determines dice info, and prints them.
void assembleWeapon(int frameChoice, int receiverChoice, int barrelChoice, int sightChoice) {
    bool isExplosiveFrame = false;

    // --- Select the Frame ---
    switch (frameChoice) {
    case 1:
        selectedFrame = physicalFrame;
        break;
    case 2:
        selectedFrame = plasmaFrame;
        break;
    case 3:
        selectedFrame = laserFrame;
        break;
    case 4:
        selectedFrame = explosiveFrame;
        isExplosiveFrame = true;
        break;
    default:
        cout << "Invalid frame choice!" << endl;
        return;
    }

    // --- Select the Receiver ---
    switch (receiverChoice) {
    case 1:
        selectedReceiver = oneShotReceiver; break;
    case 2:
        selectedReceiver = semiAutoReceiver; break;
    case 3:
        selectedReceiver = fullAutoReceiver; break;
    case 4:
        selectedReceiver = grenadeLobber; break;
    case 5:
        selectedReceiver = rocketLauncher; break;
    default:
        cout << "Invalid receiver choice!" << endl;
        return;
    }

    // --- Select the Barrel ---

        switch (barrelChoice) {
        case 1:
            selectedBarrel = shortBarrel; break;
        case 2:
            selectedBarrel = regularBarrel; break;
        case 3:
            selectedBarrel = longBarrel; break;
        case 4:
            selectedBarrel = sniperBarrel; break;
        default:
            cout << "Invalid barrel choice!" << endl;
            return;
        }

    // --- Select the Sight ---
    if (isExplosiveFrame) {
        selectedSight = ironSights;
    }
    else {
        switch (sightChoice) {
        case 1:
            selectedSight = ironSights; break;
        case 2:
            selectedSight = twoXscope; break;
        case 3:
            selectedSight = fiveXscope; break;
        case 4:
            selectedSight = holoNoAI; break;
        case 5:
            selectedSight = holoWithAI; break;
        default:
            cout << "Invalid sight choice!" << endl;
            return;
        }
    }

    // Calculates final weapon stats
    calculateWeapon(selectedFrame, selectedReceiver, selectedBarrel, selectedSight);

    // Determine quantity of dice
    int diceQuantity = static_cast<int>(finalWeapon[2]);
    if (diceQuantity < 1) diceQuantity = 1;

    int diceQuality = static_cast<int>(finalWeapon[3]);
    if (diceQuality < 1) diceQuality = 1; // d4 minimum
    if (diceQuality > 6) diceQuality = 6; // d20 maxmimum

    // Determine quality of dice
    string diceType;
    switch (diceQuality) {
    case 1: diceType = "d4"; break;
    case 2: diceType = "d6"; break;
    case 3: diceType = "d8"; break;
    case 4: diceType = "d10"; break;
    case 5: diceType = "d12"; break;
    case 6: diceType = "d20"; break;
    }
    if (finalWeapon[4] <= 0) {
        finalWeapon[4] = 0;
    }

    // Final weapon output table
    cout << "\n\nFinal Weapon Stats\n";
    cout << "===============================\n";
    cout << setw(15) << left << "Stat" << setw(10) << "|" << "Value" << "\n";
    cout << "===============================\n";
    cout << setw(15) << left << "Weight:" << setw(10) << "|" <<  finalWeapon[0] << "\n";
    cout << setw(15) << left << "Hit Modifier: " << setw(10) << "|" <<  finalWeapon[1] << "\n";
    cout << setw(15) << left << "Damage:" << setw(10) << "|" <<  diceQuantity << diceType << "\n";
    cout << setw(15) << left << "Range:" << setw(10) << "|" << finalWeapon[4] << "/" << finalWeapon[5] << "\n";
    cout << setw(15) << left << "Value:" << setw(10) << "|" << finalWeapon[6] << "\n";
}

