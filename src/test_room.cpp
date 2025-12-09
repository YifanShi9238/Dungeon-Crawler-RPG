#include <iostream>
#include "Room.h"
#include "Monster.h"
#include "Item.h"

int main() {
    std::cout << "=== ROOM CLASS TEST ===\n\n";

    // --------------------------------------------------------------
    // Create rooms
    // --------------------------------------------------------------
    Room entrance("Entrance", "A dark corridor with cold stone walls.");
    Room hall("Great Hall", "A vast room filled with ancient tapestries.");
    Room armory("Armory", "Weapons line the walls, covered in dust.");

    // --------------------------------------------------------------
    // Add exits (bi-directional)
    // --------------------------------------------------------------
    entrance.addExit("north", &hall);
    hall.addExit("south", &entrance);
    hall.addExit("east", &armory);
    armory.addExit("west", &hall);

    // --------------------------------------------------------------
    // Add items to rooms
    // --------------------------------------------------------------
    entrance.addItem(new Consumable("Torch", "Lights your path", 0));
    armory.addItem(new Weapon("Iron Sword", "Old but sharp", 6));
    armory.addItem(new Armor("Steel Shield", "Heavy and sturdy", 4));

    // --------------------------------------------------------------
    // Add monster to a room
    // --------------------------------------------------------------
    hall.setMonster(new Goblin());

    // --------------------------------------------------------------
    // Display Entrance
    // --------------------------------------------------------------
    std::cout << ">>> Displaying Entrance:\n";
    entrance.display();

    // --------------------------------------------------------------
    // Move north to the Great Hall
    // --------------------------------------------------------------
    std::cout << ">>> Moving north to the Great Hall\n";
    Room* next = entrance.getExit("north");
    if (next) {
        next->display();
    }

    // --------------------------------------------------------------
    // Check monster presence
    // --------------------------------------------------------------
    if (next->hasMonster()) {
        std::cout << "Monster present: " << next->getMonster()->getName() << "\n\n";
    }

    // --------------------------------------------------------------
    // Get an item from the Armory
    // --------------------------------------------------------------
    std::cout << ">>> Moving east to the Armory\n";
    Room* arm = next->getExit("east");
    if (arm) {
        arm->display();

        std::cout << "Attempting to retrieve 'iron sword' (case-insensitive)\n";
        Item* found = arm->getItem("iron sword");
        if (found) {
            std::cout << "Found item: " << found->getName() << "\n";
        }

        std::cout << "\nRemoving 'iron sword' from Armory...\n";
        arm->removeItem("IRON SWORD");
        arm->display();
    }

    // --------------------------------------------------------------
    // Clear monster
    // --------------------------------------------------------------
    std::cout << ">>> Clearing monster from Great Hall...\n";
    hall.clearMonster();

    hall.display();

    std::cout << "=== END OF ROOM TEST ===\n";
    return 0;
}
