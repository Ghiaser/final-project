#ifndef DICE_H
#define DICE_H

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

class Dice {
private:
    int die1;
    int die2;

public:
    Dice();
    void roll();
    int getTotal() const;
    int getFirst() const;
    int getSecond() const;
    bool isDouble() const;
};

#endif // DICE_H
