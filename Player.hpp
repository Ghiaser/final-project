#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "Slot.hpp"
class Slot;
class Player {
private:
    std::string name;
    int money;
    int position;
    std::vector<Slot*> ownedProperties;
    int trainsOwned;
    int outOfJailCard;
    bool isBankrupt;
public:
    Player(const std::string& name);
    std::vector<Slot*> getOwnedProperties();
    void pay(int amount);
    void receive(int amount);
    void setPosition(int newPosition);
    int getPosition() const;
    const std::string& getName() const;
    int getMoney() const;
    void addProperty(Slot* property);
    int getTrainCount() const;
    void IncrementTrainsOwned();
    void addGetOutOfJailCard();
    bool removeGetOutOfJailCard();
    bool isJailed;
    std::string toString()  const;
};

#endif // PLAYER_H
