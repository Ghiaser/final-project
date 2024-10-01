#ifndef TRAIN_H
#define TRAIN_H
#include "Slot.hpp"

class Train : public Slot {
private:
    int cost;
    int taxPerTrain;

public:
    Train(const std::string& name, int cost, int taxPerTrain);
    void landOn(Player& player) override;
};

#endif // TRAIN_H
