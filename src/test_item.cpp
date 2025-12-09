#include <iostream>
#include <vector>
#include <string>
#include "Item.h"

int main() {

    std::vector<Item*> inventory;


    inventory.push_back(new Weapon("Iron Sword", "A sturdy blade", 5));
    inventory.push_back(new Armor("Chain Mail", "Protective armor", 3));
    inventory.push_back(new Consumable("Health Potion", "Restores health", 30));
    inventory.push_back(new Consumable("Mega Potion", "Restores lots of health", 80));


    std::cout << "=== INVENTORY LIST ===" << std::endl;
    for (Item* item : inventory) {
        item->displayInfo();
        std::cout << std::endl;
    }

    std::cout << "=== POLYMORPHISM TEST ===" << std::endl;
    Item* poly = inventory[0];   // Should call Weapon::displayInfo()
    poly->displayInfo();
    std::cout << std::endl;

    std::cout << "=== USING A CONSUMABLE ===" << std::endl;
    Consumable* potion = dynamic_cast<Consumable*>(inventory[2]);
    if (potion) {
        potion->use();
        potion->use();  // Should show "already used"
    }
    std::cout << std::endl;

    std::string remove_name = "Chain Mail";
    std::cout << "Removing item: " << remove_name << "\n";

    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == remove_name) {
            delete *it;        
            inventory.erase(it);
            break;
        }
    }

    std::cout << "\n=== UPDATED INVENTORY ===" << std::endl;
    for (Item* item : inventory) {
        item->displayBrief();
    }
    std::cout << std::endl;

    for (Item* item : inventory) {
        delete item;
    }
    inventory.clear();

    std::cout << "All items deleted. No memory leaks should remain.\n";

    return 0;
}
