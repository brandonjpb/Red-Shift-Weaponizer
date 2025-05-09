#include "inputGetter.h"
#include "weaponAssembler.h"

using namespace std;

int main() {

   cout << "Welcome to the weaponizer!\n";
   cout << "This program will walk you through weapon creation and output a stat block.\n";
   cout << "It makes it very easy for the DM to generate weapons on the fly.\n\n";
   cout << "Begin by deciding what weapon frame to begin with.\n";

   int frameChoice = getFrameInput();
   int receiverChoice = getReceiverInput();
   int barrelChoice = getBarrelInput();
   int sightChoice = getSightInput();
   assembleWeapon(frameChoice, receiverChoice, barrelChoice, sightChoice);
   return 0;
}
