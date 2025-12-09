#include "Character.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed random generator (important for calculateDamage)
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "=== CHARACTER CLASS TEST ===\n";

    // Create test character
    Character hero("Hero", 100, 10, 5);

    // Display initial stats
    std::cout << "\n[Initial Stats]\n";
    hero.displayStats();

    // Test taking damaged
    std::cout << "\n[Damage Test]\n";
    hero.takeDamage(20);

    // Test healing
    std::cout << "\n[Healing Test]\n";
    hero.heal(10);

    // Test fatal damage
    std::cout << "\n[Fatal Damage Test]\n";
    hero.takeDamage(200);

    // Display final status
    std::cout << "\n[Final Status]\n";
    hero.displayStats();

    return 0;
}
