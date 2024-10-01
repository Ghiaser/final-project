#include "Dice.hpp"

Dice::Dice():die1(0), die2(0) {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    roll(); // Initial roll
}

void Dice::roll() {
    die1 = (std::rand() % 6) + 1; // Roll a die (1 to 6)
    die2 = (std::rand() % 6) + 1; // Roll a second die
}

int Dice::getTotal() const {
    return die1 + die2;
}

bool Dice::isDouble() const {
    return die1 == die2;
}

int Dice::getFirst() const{
    return die1;
}
int Dice::getSecond() const{
    return die2;
}