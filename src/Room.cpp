#include "Room.h"
#include <iostream>
#include <algorithm>

// TODO: Implement Room constructor
Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description), visited(false), monster(NULL) {
}


// TODO: Implement Room destructor
Room::~Room() {
    // TODO: Clean up monster and items
    if (monster) {
        delete monster;
        monster = NULL;
    }
    
    for (Item* item : items) {
        delete item;
    }
    items.clear();
}


// TODO: Implement display
// HINTS:
// - Print formatted room information with decorative borders
// - Format:
//   ========================================
//   Room Name
//   ========================================
//   Description text
//   
//   [If monster] A MonsterName blocks your path!
//   
//   [If items] Items here:
//     - item1
//     - item2
//   
//   Exits: north, south, east
//   ========================================
//
void Room::display() const {
    // TODO: Display room information
    std::cout << "========================================\n";
    std::cout << "           " << name << "\n";
    std::cout << "========================================\n";
    std::cout << description << "\n\n";

    if (monster) {
        std::cout << "A " << monster->getName() << " blocks your path!\n\n";
    }

    if (!items.empty()) {
        std::cout << "Items here:\n";
        displayItems();
        std::cout << "\n";
    }

    displayExits();
    std::cout << "========================================\n\n";
}


// TODO: Implement displayExits
// HINTS:
// - Print "Exits: "
// - Iterate through exits map using iterator
// - Print each direction (the key) separated by commas
// - Example output: "Exits: north, south, east"
//
void Room::displayExits() const {
    // TODO: Display available exits
    std::cout << "Exits: ";

    if (exits.empty()) {
        std::cout << "None\n";
        return;
    }

    bool first = true;
    for (const auto& pair : exits) {
        if (!first) std::cout << ", ";
        std::cout << pair.first;
        first = false;
    }
    std::cout << "\n";
}


// TODO: Implement addExit
// HINTS:
// - Check if room pointer is not NULL
// - Add to exits map: exits[direction] = room
//
void Room::addExit(const std::string& direction, Room* room) {
    // TODO: Add exit to map
    if (room != NULL) {
        exits[direction] = room;
    }
}


// TODO: Implement getExit
// HINTS:
// - Look up direction in exits map
// - Use exits.find(direction)
// - If not found, return NULL
//
Room* Room::getExit(const std::string& direction) const {
    // TODO: Look up and return exit
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    return NULL;
}


// TODO: Implement hasExit
// HINTS:
// - Check if direction exists in exits map
bool Room::hasExit(const std::string& direction) const {
    // TODO: Check if exit exists
    return exits.count(direction) > 0;
}


// TODO: Implement clearMonster
// HINTS:
// - If monster exists, delete it
// - Set monster pointer to NULL
//
void Room::clearMonster() {
    // TODO: Delete and clear monster
    if (monster) {
        delete monster;
        monster = NULL;
    }
}


// TODO: Implement addItem
// HINTS:
// - Check if item pointer is not NULL
// - Add to items vector using push_back()
//
void Room::addItem(Item* item) {
    // TODO: Add item to room
    if (item != NULL) {
        items.push_back(item);
    }
}


// TODO: Implement removeItem
// HINTS:
// - Search items vector for item by name (case-insensitive)
// - If found: erase from vector (DON'T delete - ownership transferred)
//
void Room::removeItem(const std::string& item_name) {
    // TODO: Find and remove item from room
    std::string target = item_name;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);

    for (size_t i = 0; i < items.size(); ++i) {
        std::string current = items[i]->getName();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        
        if (current == target) {
            items.erase(items.begin() + i);
            return;
        }
    }

}


// TODO: Implement displayItems
// HINTS:
// - Print each item's name in a list
// - Format: "  - ItemName"
//
void Room::displayItems() const {
    // TODO: Display all items in room
    for (Item* item : items) {
        std::cout << "  - " << item->getName() << "\n";
    }
}


// TODO: Implement getItem
// HINTS:
// - Search items vector for item by name (case-insensitive)
// - If found, return pointer to item
// - If not found, return NULL
//
Item* Room::getItem(const std::string& item_name) {
    // TODO: Find and return item pointer
    std::string target = item_name;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);

    for (Item* item : items) {
        std::string current = item->getName();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        
        if (current == target) {
            return item;
        }
    }
    return NULL;  // REPLACE THIS
}
