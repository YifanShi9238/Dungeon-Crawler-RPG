#include "Player.h"
#include <iostream>
#include <algorithm>
#include <cctype>

// TODO: Implement Player constructor
// HINTS:
// - MUST call Character base constructor. 
//
Player::Player(const std::string& name)
    : Character(name, 100, 10, 5),
      level(1), experience(0), gold(0),
      equipped_weapon(NULL), equipped_armor(NULL) {
}


// TODO: Implement Player destructor
// HINTS:
// - CRITICAL: Must delete all items in inventory to prevent memory leaks!
// - DON'T delete equipped_weapon or equipped_armor - they point to items
//   already in the inventory, so they're already deleted!
//
Player::~Player() {
    // TODO: Delete all inventory items
    for (Item* item : inventory) {
        delete item;
    }
    inventory.clear();
}


// TODO: Override displayStats
// HINTS:
// - Show player-specific information
// - Include: level, HP, attack (with weapon bonus), defense (with armor bonus), gold, experience
// - Show equipped weapon and armor names if any
// - Use decorative formatting (borders, headers)
// - Use getters to access inherited Character data
//
void Player::displayStats() const {
    // TODO: Display comprehensive player stats
    std::cout << "============================\n";
    std::cout << "      PLAYER STATUS\n";
    std::cout << "============================\n";
    std::cout << "Name: " << getName() << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "HP: " << getCurrentHP() << "/" << getMaxHP() << "\n";

    int attack = getAttack();
    if (equipped_weapon != NULL) {
        attack += equipped_weapon->getValue();
    }

    int defense = getDefense();
    if (equipped_armor != NULL) { 
        defense += equipped_armor->getValue();
    }

    std::cout << "Attack: " << attack;
    if(equipped_weapon) {
        std::cout << " (+" << equipped_weapon->getValue()
                  << " from " << equipped_weapon->getName() << ")";
    }
    std::cout << "\n";

    std::cout << "Defense: " << defense;

    if(equipped_armor) {
        std::cout << " (+" << equipped_armor->getValue()
                  << " from " << equipped_armor->getName() << ")";
    }
    std::cout << "\n";

    std::cout << "Gold: " << gold << "\n";
    std::cout << "Experience: " << experience << "/" << (level * 100) << "\n";
    std::cout << "============================\n\n";
}


// TODO: Override calculateDamage to include weapon bonus
// HINTS:
// - If weapon is equipped, add weapon's damage bonus
// - Return total damage
//
int Player::calculateDamage() const {
    // TODO: Calculate damage with weapon bonus
    int base = Character::calculateDamage();
    if (equipped_weapon != NULL){
        base += equipped_weapon->getValue();
    }
    return base;  // REPLACE THIS
}


// TODO: Implement addItem
// HINTS:
// - Add item to inventory vector using push_back()
// - Print pickup message with item name
//
void Player::addItem(Item* item) {
    // TODO: Add item to inventory
    if (item == NULL) return;
    inventory.push_back(item);
    std::cout << "Picked up: " << item->getName() << "\n";
}


// TODO: Implement removeItem
// HINTS:
// - Search inventory for item by name (case-insensitive comparison)
// - If found: delete the item, then erase from vector
// - If not found: print error message
// - Remember: inventory.erase(inventory.begin() + i) to remove at index i
//
void Player::removeItem(const std::string& item_name) {
    // TODO: Find and remove item from inventory
    std::string target = item_name;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);

    for (size_t i = 0; i < inventory.size(); ++i) {
        std::string current = inventory[i]->getName();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        
        if (current == target) {
            std::cout << "Removed: " << inventory[i]->getName() << "\n";
            delete inventory[i];
            inventory.erase(inventory.begin() + i);
            return;
        }
    }
    std::cout << "Item not found: " << item_name << "\n";

}


// TODO: Implement displayInventory
// HINTS:
// - Print header: "----- Inventory -----"
// - If inventory is empty, print "Empty"
// - Otherwise, loop through and print each item's name and type
// - Format: "- ItemName (ItemType)"
// - Print footer: "--------------------"
//
void Player::displayInventory() const {
    // TODO: Display all items in inventory
    std::cout << "----- Inventory -----\n";

    if (inventory.empty()) {
        std::cout << "      Empty\n";
    } else {
        for (Item* item: inventory) {
            std::cout << "- " << item->getName() 
                      << " (" << item->getType() << ")\n";
        }
    }

    std::cout << "--------------------\n";
}


// TODO: Implement hasItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return true if found, false otherwise
// - Use same case-insensitive comparison as removeItem
//
bool Player::hasItem(const std::string& item_name) const {
    // TODO: Check if item exists in inventory
    std::string target = item_name;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);

    for (Item* item : inventory) {
        std::string current = item->getName();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        
        if (current == target) {
            return true;
        }
    }
    return false;  // REPLACE THIS
}


// TODO: Implement getItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return pointer to item if found
// - Return NULL if not found
//
Item* Player::getItem(const std::string& item_name) {
    // TODO: Find and return item pointer
    std::string target = item_name;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);
    
    for (Item* item : inventory) {
        std::string current = item->getName();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        
        if (current == target) {
            return item;
        }
    }
    return NULL;  // REPLACE THIS
}


// TODO: Implement equipWeapon
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Weapon"
// - If current weapon equipped, print unequip message
// - Set equipped_weapon pointer to this item
// - Print equip message
//
void Player::equipWeapon(const std::string& weapon_name) {
    // TODO: Equip weapon from inventory
    Item* item = getItem(weapon_name);

    if (!item) {
        std::cout << "No such item to equip: " << weapon_name << "\n";
        return;
    }

    if(item->getType() != "Weapon") {
        std::cout << "Item is not a weapon: " << weapon_name << "\n";
        return;
    }

    if (equipped_weapon != NULL) {
        std::cout << "Unequipped: " << equipped_weapon->getName() << "\n";
    }

    equipped_weapon = item;
    std::cout << "Equipped weapon: " << equipped_weapon->getName() << "\n";
}


// TODO: Implement equipArmor
// HINTS:
// - Similar to equipWeapon but for armor
// - Check if item type is "Armor"
// - Set equipped_armor pointer
//
void Player::equipArmor(const std::string& armor_name) {
    // TODO: Equip armor from inventory
    Item* item = getItem(armor_name);

    if(!item) {
        std::cout << "No such item to equip: " << armor_name << "\n";
        return;
    }

    if(item->getType() != "Armor") {
        std::cout << "Item is not an armor: " << armor_name << "\n";
        return;
    }

    if(equipped_armor != NULL) {
        std::cout << "Unequipped: " << equipped_armor->getName() << "\n";
    }

    equipped_armor = item;
    std::cout << "Equipped armor: " << equipped_armor->getName() << "\n";

}


// TODO: Implement unequipWeapon
// HINTS:
// - Check if weapon is currently equipped
// - If so, print message and set equipped_weapon to NULL
// - If not, print error message
//
void Player::unequipWeapon() {
    // TODO: Unequip current weapon
    if (equipped_weapon == NULL) {
        std::cout << "No weapon is equipped.\n";
        return;
    }

    std::cout << "Unequipped: " << equipped_weapon->getName() << "\n";
    equipped_weapon = NULL;
}


// TODO: Implement unequipArmor
// HINTS:
// - Similar to unequipWeapon
// - Set equipped_armor to NULL
//
void Player::unequipArmor() {
    // TODO: Unequip current armor
    if (equipped_armor == NULL) {
        std::cout << "No armor is equipped.\n";
        return;
    }
    std::cout << "Unequipped: " << equipped_armor->getName() << "\n";
    equipped_armor = NULL;
}


// TODO: Implement useItem
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Consumable"
// - Cast to Consumable*: Consumable* consumable = static_cast<Consumable*>(item)
// - Check if already used: consumable->isUsed()
// - Get healing amount: consumable->getHealingAmount()
// - Call heal() with that amount
// - Call consumable->use() to mark as used
// - Remove item from inventory (it's been consumed!)
//
void Player::useItem(const std::string& item_name) {
    // TODO: Use consumable item
    Item* item = getItem(item_name);
    if (!item) {
        std::cout << "No such item: " << item_name << "\n";
        return;
    }
    if (item->getType() != "Consumable") {
        std::cout << "Item is not a consumable.\n";
        return;
    }

    Consumable* consumable = static_cast<Consumable*>(item);

    if (consumable->isUsed()) {
        std::cout << "This consumable was already used.\n";
        return;
    }

    int heal_amt = consumable->getHealingAmount();
    heal(heal_amt);
    consumable->use();

    removeItem(item_name);
}


// TODO: Implement gainExperience
// HINTS:
// - Add experience points
// - Print message showing exp gained
// - Check if enough exp to level up: if (experience >= level * 100)
// - If so, call levelUp()
//
void Player::gainExperience(int exp) {
    // TODO: Add experience and check for level up
    experience += exp;
    std::cout << "Gained " << exp << " EXP!\n";

    if (experience >= level * 100) {
        levelUp();
    }
}


// TODO: Implement levelUp
// HINTS:
// - Increment level
// - Reset experience to 0
// - Increase stats:
//   * Increase max_hp by 10 (use setMaxHP())
//   * Set current_hp to max (full heal on level up)
//   * Increase attack by 2
//   * Increase defense by 1
// - Print celebratory level up message
// - Display new stats
//
void Player::levelUp() {
    // TODO: Level up the player
    level++;
    experience = 0;

    setMaxHP(getMaxHP() + 10);
    setCurrentHP(getMaxHP());

    setAttack(getAttack() + 2);
    setDefense(getDefense() + 1);

    std::cout << "\n*** LEVEL UP! You are now level " << level << "! ***\n";
    displayStats();
}
