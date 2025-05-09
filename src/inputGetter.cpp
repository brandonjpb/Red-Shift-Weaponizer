#include "inputGetter.h"
#include "weaponAssembler.h"

using namespace std;

int frameChoice;
int receiverChoice;
int barrelChoice;
int sightChoice;


bool isExplosiveFrame = false;
// Gets input for the frame
int getFrameInput() {
    int input;
    while (true) {
        cout << "\n\nSelect a Frame:\n";
        cout << "1. Physical Frame\n";
        cout << "2. Plasma Frame\n";
        cout << "3. Laser Frame\n";
        cout << "4. Explosive Frame\n\n";
        cout << "Enter your choice: ";
        cin >> input;

        // Clears previous input if it is invalid
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a digit only.\n";
    }

    // Ensures input is within valid integer range
    else {
        if ((input >= 1) && (input <= 3)) {
            return input;
            break;
        }

        // Sets isExplosiveFrame to true for later use (part compatibility with explosive weapons)
        if (input == 4) {
            isExplosiveFrame = true;
            return input;
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n\n";
        }
      }
    }
    return input;
}

// Gets input for the receiver, shows only what is compatible with selected frame
int getReceiverInput() {
    int input;
    while (true) {
        if (!isExplosiveFrame) {            
            cout << "\n\nSelect a Receiver:\n";
            cout << "1. Single shot\n";
            cout << "2. Semi automatic\n";
            cout << "3. Fully automatic (required for Holographic AI sight use)\n";
            cout << "Enter your choice: ";
            } 
        else {
            cout << "\n\nSelect a Receiver:\n";
            cout << "4. Grenade lobber\n";
            cout << "5. Rocket launcher\n";
            cout << "Enter your choice: ";
        }
        cin >> input;

        // Input checking routine
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a digit only.\n";
        }

        // Ensures input is within valid integer range; ensures compatibility with explosive frame
        else {                        
            if ((!isExplosiveFrame && input >= 1 && input <= 3) || (isExplosiveFrame && input >= 4 && input <= 5)) {
                break;
            }
            else {
                cout << "Invalid choice. Please try again.\n\n";
            }
        }
    }
    return input;
}

// Gets input for the barrel
int getBarrelInput() {
    int input;
    while (true) {
        if (isExplosiveFrame) {
            // If explosive frame has been selected, skips barrel selection altogether and defaults to standard barrel
            input = 2;
            break;
        }
        cout << "\n\nSelect a Barrel:\n";
        cout << "1. Short Barrel\n";
        cout << "2. Standard Barrel\n";
        cout << "3. Long Barrel\n";
        cout << "4. Sniper Barrel\n\n";
        cout << "Enter your choice: ";
        cin >> input;

        // Input checking routine
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a digit only.\n";
        }

        // Ensures input is within valid integer range
        else {
            if (input >= 1 && input <= 4) {
                break;
            }
            else {
                cout << "Invalid choice. Please try again.\n\n";
            }
        }
    }
    return input;
}

// Gets input for the sight
int getSightInput() {
    int input;
    while (true) {
        if (isExplosiveFrame) {
            // If explosive frame has been selected, skips barrel selection altogether and defaults to iron sights (stats adjusted to compensate for loss with iron sights)
            input = 1;
            break;
        }
        cout << "\n\nSelect a Sight:\n";
        cout << "1. Iron Sight\n";
        cout << "2. 2x Scope\n";
        cout << "3. 5x Scope\n";
        cout << "4. Holographic Sight\n";
        cout << "5. Holographic Sight with AI Targeting (requires full auto receiver)\n\n";
        cout << "Enter your choice: ";
        cin >> input;

        // Input checking routine
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a digit only.\n";
        }
        else {
            // Ensures input is within valid integer range; ensures automatic receiver is selected for AI sight
            if ((input >= 1 && input <= 4) || (input == 5 && receiverChoice == 3)) {
                break;}
            if ((input == 5) && (receiverChoice != 3)) {
                cout << "Invalid choice. Automatic receiver must be selected to use this sight. Please select a different sight.\n";            
            }
            else {
                cout << "Invalid choice. Please try again.\n\n";
            }
        }
    }
    return input;
}
