#include <iostream>
#include "Game.h"

int main() {
    std::cout << "\n=== GAME BASIC TEST ===\n\n";

    // Create Game instance
    std::cout << "[1] Constructing Game object...\n";
    Game game;

    std::cout << "[2] Starting game initialization (run)...\n";
    std::cout << "    NOTE: Type 'quit' when prompted to exit game loop.\n\n";

    // Run the actual game loop
    // User will type "quit" immediately to exit
    game.run();

    std::cout << "\n=== GAME BASIC TEST COMPLETE ===\n";
    return 0;
}
