#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// TODO: Implement Game constructor
Game::Game() : player(NULL), current_room(NULL), 
               game_over(false), victory(false) {
}


// TODO: Implement Game destructor
Game::~Game() {
    // TODO: Clean up player and all rooms
    if (player) {
        delete player;
        player = NULL;
    }

    for (std::map<std::string, Room*>::iterator it = world.begin(); 
         it != world.end(); ++it) {
        delete it->second;
    }
    world.clear();
}


// TODO: Implement initializeWorld
// HINTS:
// - Create all rooms with new
// - Add each room to world using addRoom()
// - Connect rooms using connectRooms()
// - Add monsters to appropriate rooms using room->setMonster()
// - Add items to rooms using room->addItem()
// - Set current_room to starting room (entrance)
//
// SUGGESTED WORLD LAYOUT:
//                [Throne Room]
//                     |
//     [Armory] - [Hallway] - [Treasury]
//                     |
//                 [Entrance]
//
// MONSTERS:
// - Hallway: Goblin
// - Armory: Skeleton
// - Treasury: Skeleton
// - Throne Room: Dragon (boss!)
//
// ITEMS:
// - Entrance: Small Potion
// - Armory: Iron Sword, Chain Mail
// - Treasury: Health Potion
//
void Game::initializeWorld() {
    // TODO: Create rooms
    // Room* entrance = new Room("Dungeon Entrance", "A dark stone corridor...");
    Room* entrance = new Room("Dungeon Entrance", "A dark stone corridor...");
    Room* hallway   = new Room("Hallway", "A long hall with flickering torches.");
    Room* armory    = new Room("Armory", "Rows of old weapons and armor.");
    Room* treasury  = new Room("Treasury", "Piles of gold sparkle faintly.");
    Room* throne    = new Room("Throne Room", "A massive chamber with a looming throne.");
    // TODO: Add rooms to world
    addRoom(entrance);
    addRoom(hallway);
    addRoom(armory);
    addRoom(treasury);
    addRoom(throne);
    // TODO: Connect rooms bidirectionally
    connectRooms("Dungeon Entrance", "north", "Hallway");
    connectRooms("Hallway", "east", "Armory");
    connectRooms("Hallway", "west", "Treasury");
    connectRooms("Hallway", "north", "Throne Room");

    // TODO: Add monsters
    hallway->setMonster(new Goblin());
    armory->setMonster(new Skeleton());
    treasury->setMonster(new Skeleton());
    throne->setMonster(new Dragon()); // Boss monster

    // TODO: Add items
    entrance->addItem(new Consumable("Small Potion", "Restores 10 HP", 10));
    armory->addItem(new Weapon("Iron Sword", "Sharp blade", 6));
    armory->addItem(new Armor("Chain Mail", "Solid armor", 4));
    treasury->addItem(new Consumable("Health Potion", "Restores 30 HP", 30));

    // TODO: Set starting room
    current_room = entrance;
}


// TODO: Implement createStartingInventory
// HINTS:
// - Give player starting weapon: Rusty Dagger (damage +2)
// - Give player starting food: Bread (heals 5 HP)
// - Use: player->addItem(new Weapon(...))
//
void Game::createStartingInventory() {
    // TODO: Give player starting items
    player->addItem(new Weapon("Rusty Dagger", "Barely usable", 2));
    player->addItem(new Consumable("Bread", "Restores 5 HP", 5));
}


// TODO: Implement addRoom
// HINTS:
// - Check if room pointer is not NULL
// - Add to world map using room's name as key
// - Use: world[room->getName()] = room
//
void Game::addRoom(Room* room) {
    // TODO: Add room to world map
    if (room) {
        world[room->getName()] = room;
    }
}


// TODO: Implement connectRooms
// HINTS:
// - Look up both rooms in world map
// - If both exist:
//   - Add forward direction: room1->addExit(direction, room2)
//   - Determine reverse direction:
//     * north ↔ south
//     * east ↔ west
//   - Add reverse direction: room2->addExit(reverse, room1)
//
void Game::connectRooms(const std::string& room1_name, const std::string& direction,
                       const std::string& room2_name) {
    // TODO: Connect rooms bidirectionally
    Room* r1 = world.count(room1_name) ? world[room1_name] : NULL;
    Room* r2 = world.count(room2_name) ? world[room2_name] : NULL;

    if (!r1 || !r2) return;

    r1->addExit(direction, r2);

    // Reverse direction
    std::string reverse;
    if (direction == "north") reverse = "south";
    else if (direction == "south") reverse = "north";
    else if (direction == "east") reverse = "west";
    else if (direction == "west") reverse = "east";

    r2->addExit(reverse, r1);
}


// TODO: Implement run - main game loop
// HINTS:
// - Print welcome message and game title
// - Get player name from input 
// - Create player: player
// - Call initializeWorld()
// - Call createStartingInventory()
// - Display starting room
// - Mark starting room as visited
// - Main loop: 
//   - Print prompt: "> "
//   - Get command (use std::getline)
//   - Convert to lowercase (use std::transform)
//   - Call processCommand()
//   - Check victory condition
//   - Check defeat condition (player dead)
//
void Game::run() {
    // TODO: Implement main game loop
    std::cout << "=====================================\n";
    std::cout << "      WELCOME TO DUNGEON QUEST       \n";
    std::cout << "=====================================\n";

    std::string name;
    std::cout << "Enter your name, hero: ";
    std::getline(std::cin, name);

    player = new Player(name);

    initializeWorld();
    createStartingInventory();

    std::cout << "\nYour adventure begins...\n\n";
    current_room->markVisited();
    current_room->display();

    while (!game_over) {
        if (!player->isAlive()) {
            std::cout << "You have perished... GAME OVER.\n";
            game_over = true;
            break;
        }

        if (victory) {
            std::cout << "Congratulations! You defeated the Dragon and won the game!\n";
            break;
        }

        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        processCommand(input);
    }
}


// TODO: Implement processCommand
// HINTS:
// - Parse command into verb and object
// - Extract first word as verb
// - Rest of line is object
// - Dispatch to appropriate method based on verb:
//   * "go" or "move" → move(object)
//   * "look" or "l" → look()
//   * "attack" or "fight" → attack()
//   * "pickup" or "get" or "take" → pickupItem(object)
//   * "inventory" or "i" → inventory()
//   * "use" → useItem(object)
//   * "equip" or "e" → equip(object)
//   * "stats" → player->displayStats()
//   * "help" or "h" or "?" → help()
//   * "quit" or "exit" → set game_over to true
//
void Game::processCommand(const std::string& command) {
    // TODO: Parse and dispatch command
    if (command.empty()) return;

    std::istringstream iss(command);
    std::string verb;
    iss >> verb;

    std::string object;
    getline(iss, object);
    if (!object.empty() && object[0] == ' ')
        object = object.substr(1);

    if (verb == "go" || verb == "move")        move(object);
    else if (verb == "look" || verb == "l")    look();
    else if (verb == "attack" || verb == "fight") attack();
    else if (verb == "pickup" || verb == "get" || verb == "take") pickupItem(object);
    else if (verb == "inventory" || verb == "i") inventory();
    else if (verb == "use")                    useItem(object);
    else if (verb == "equip" || verb == "e")   equip(object);
    else if (verb == "stats")                  player->displayStats();
    else if (verb == "help" || verb == "h" || verb == "?") help();
    else if (verb == "quit" || verb == "exit") game_over = true;
    else std::cout << "Unknown command.\n";
}


// TODO: Implement move
// HINTS:
// - Check if monster blocks path (current_room->hasMonster())
// - If blocked, print message and return
// - Get exit in specified direction
// - If exit exists:
//   - Update current_room
//   - Display new room
//   - Mark as visited
// - Otherwise print error: "You can't go that way!"
//
void Game::move(const std::string& direction) {
    // TODO: Move to adjacent room
    if (current_room->hasMonster()) {
        std::cout << "A monster blocks your way!\n";
        return;
    }

    Room* next = current_room->getExit(direction);
    if (!next) {
        std::cout << "You can't go that way!\n";
        return;
    }

    current_room = next;
    current_room->markVisited();
    current_room->display();
}


// TODO: Implement look
// HINTS:
// - Simply display current room
//
void Game::look() {
    // TODO: Display current room
    current_room->display();
}


// TODO: Implement attack
// HINTS:
// - Check if monster in room
// - If no monster, print message and return
// - If monster present, call combat()
//
void Game::attack() {
    // TODO: Attack monster in room
    Monster* monster = current_room->getMonster();
    if (!monster) {
        std::cout << "There is nothing to attack.\n";
        return;
    }

    combat(monster);
}


// TODO: Implement combat
// HINTS:
// - Print "=== COMBAT BEGINS ==="
// - Combat loop: while both player and monster are alive
//   - Prompt for player action: attack/use <item>/flee
//   - If attack:
//     * Calculate player damage
//     * Monster takes damage
//     * If monster dead:
//       - Print victory
//       - Player gains exp and gold
//       - Get loot from monster
//       - Add loot to current room
//       - Check if Dragon 
//       - Clear monster from room
//       - Break from loop
//   - If use:
//     * Extract item name from command
//     * Call player->useItem()
//   - If flee:
//     * Print message and break
//   - Monster turn (if alive):
//     * Print attack message
//     * Calculate monster damage
//     * Player takes damage
// - Print "=== COMBAT ENDS ==="
//
void Game::combat(Monster* monster) {
    // TODO: Implement turn-based combat
    std::cout << "\n=== COMBAT BEGINS ===\n";

    while (player->isAlive() && monster->isAlive()) {
        std::cout << "\nYour HP: " << player->getCurrentHP()
                  << " | Monster HP: " << monster->getCurrentHP() << "\n";

        std::cout << "Action (attack/use <item>/flee): ";
        std::string cmd;
        std::getline(std::cin, cmd);
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

        if (cmd == "attack") {
            int damage = player->calculateDamage();
            std::cout << "You strike for " << damage << " damage!\n";
            monster->takeDamage(damage);

            if (!monster->isAlive()) {
                std::cout << "You defeated the " << monster->getName() << "!\n";
                player->gainExperience(monster->getExperienceReward());
                player->addGold(monster->getGoldReward());

                // Loot
                std::vector<Item*> loot = monster->dropLoot();
                for (Item* item : loot)
                    current_room->addItem(item);

                if (monster->getName() == "Dragon")
                    victory = true;

                current_room->clearMonster();
                break;
            }
        }
        
        else if (cmd.rfind("use ", 0) == 0) {
            std::string item_name = cmd.substr(4);
            player->useItem(item_name);
        }

        else if (cmd == "flee") {
            std::cout << "You flee from combat!\n";
            break;
        }

        // Monster attacks (if alive)
        if (monster->isAlive()) {
            std::cout << monster->getAttackMessage() << "\n";
            int dmg = monster->calculateDamage();
            player->takeDamage(dmg);
        }
    }

    std::cout << "=== COMBAT ENDS ===\n\n";
}


// TODO: Implement pickupItem
// HINTS:
// - Get item from current room
// - If exists:
//   - Add to player inventory
//   - Remove from room (ownership transfer!)
// - Otherwise print error
//
void Game::pickupItem(const std::string& item_name) {
    // TODO: Pick up item from room
    Item* item = current_room->getItem(item_name);
    if (!item) {
        std::cout << "No such item here.\n";
        return;
    }

    player->addItem(item);
    current_room->removeItem(item_name);
}


// TODO: Implement inventory
//
void Game::inventory() {
    // TODO: Display player inventory
    player->displayInventory();
}


// TODO: Implement useItem
// HINTS:
// - Call player->useItem(item_name)
//
void Game::useItem(const std::string& item_name) {
    // TODO: Use item from inventory
    player->useItem(item_name);
}


// TODO: Implement equip
// HINTS:
// - Get item from player inventory
// - Check if item exists
// - Check item type:
//   - If "Weapon": call player->equipWeapon()
//   - If "Armor": call player->equipArmor()
//   - Otherwise: print error (can't equip consumables)
//
void Game::equip(const std::string& item_name) {
    // TODO: Equip weapon or armor
    Item* item = player->getItem(item_name);
    if (!item) {
        std::cout << "You don't have that item.\n";
        return;
    }

    if (item->getType() == "Weapon")
        player->equipWeapon(item_name);
    else if (item->getType() == "Armor")
        player->equipArmor(item_name);
    else
        std::cout << "You cannot equip that.\n";
}


// TODO: Implement help
// HINTS:
// - Print all available commands with descriptions
// - Format nicely with headers
// - Commands:
//   * go <direction> - Move
//   * look - Look around
//   * attack - Attack monster
//   * pickup <item> - Pick up item
//   * inventory - Show inventory
//   * use <item> - Use consumable
//   * equip <item> - Equip weapon/armor
//   * stats - Show character stats
//   * help - Show this help
//   * quit - Exit game
//
void Game::help() {
    // TODO: Display help message
    std::cout << "\n=== COMMANDS ===\n"
              << "go <direction>  - Move to another room\n"
              << "look            - Look around the room\n"
              << "attack          - Attack the monster\n"
              << "pickup <item>   - Pick up an item\n"
              << "inventory       - Show inventory\n"
              << "use <item>      - Use a consumable\n"
              << "equip <item>    - Equip weapon/armor\n"
              << "stats           - Show player stats\n"
              << "help            - Show commands\n"
              << "quit            - Exit the game\n\n";
}
