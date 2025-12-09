#include <iostream>
#include <vector>
#include "Monster.h"
#include "Item.h"

int main() {
    std::cout << "=== MONSTER BASE CLASS TEST ===\n\n";

    // Create a basic monster
    Monster orc("Orc", 50, 8, 3, 20, 10);
    orc.addLoot(new Consumable("Potion", "Heals", 15));

    orc.displayStats();
    std::cout << orc.getAttackMessage() << std::endl;

    std::cout << "\nOrc takes 30 damage...\n";
    orc.takeDamage(30);
    orc.displayStats();

    std::cout << "\nOrc drops loot!\n";
    std::vector<Item*> loot = orc.dropLoot();

    for (Item* item : loot) {
        std::cout << "- Loot: ";
        item->displayInfo();
        delete item;  // cleanup
    }

    loot.clear();

    std::cout << "\n=== DERIVED MONSTER TEST ===\n\n";

    // Polymorphism test
    Monster* monsters[3];
    monsters[0] = new Goblin();
    monsters[1] = new Skeleton();
    monsters[2] = new Dragon();

    for (int i = 0; i < 3; i++) {
        monsters[i]->displayStats();
        std::cout << monsters[i]->getAttackMessage() << std::endl;
        std::cout << "Damage: " << monsters[i]->calculateDamage() << std::endl;
        std::cout << std::endl;
    }

    // Cleanup
    for (int i = 0; i < 3; i++) {
        delete monsters[i];
    }

    std::cout << "=== TEST COMPLETE ===\n";
    return 0;
}
