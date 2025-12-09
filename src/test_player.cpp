#include <iostream>
#include "Player.h"
#include "Item.h"

int main() {
    std::cout << "=== PLAYER TEST PROGRAM ===\n\n";

    Player hero("Alice");
    hero.displayStats();

    std::cout << "\n=== Adding Items ===\n";
    hero.addItem(new Weapon("Iron Sword", "A sturdy training blade", 5));
    hero.addItem(new Armor("Leather Armor", "Light protective gear", 3));
    hero.addItem(new Consumable("Health Potion", "Restores health", 30));
    hero.addItem(new Consumable("Mega Potion", "Restores lots of health", 80));
    hero.displayInventory();


    std::cout << "\n=== Equipping Items ===\n";
    hero.equipWeapon("iron sword");
    hero.equipArmor("leather armor");
    hero.displayStats();

    std::cout << "\n=== Damage Calculation ===\n";
    int dmg = hero.calculateDamage();
    std::cout << "Hero's total damage: " << dmg << "\n";

    std::cout << "\n=== Taking Damage ===\n";
    hero.takeDamage(22);   // Should reduce HP properly based on defense
    hero.displayStats();

    std::cout << "\n=== Using Consumable ===\n";
    hero.useItem("health potion");  // case-insensitive
    hero.displayStats();

    std::cout << "\nTrying to use potion again (should fail):\n";
    hero.useItem("health potion");  // Should print "not found" (removed)

    std::cout << "\n=== Removing Item ===\n";
    hero.removeItem("mega potion");
    hero.displayInventory();

    std::cout << "\n=== Level Up Test ===\n";
    hero.gainExperience(50);
    hero.gainExperience(70);  // Should trigger level up (needs 100)
    hero.displayStats();

    std::cout << "\n=== END OF TEST ===\n";

    return 0;
}
