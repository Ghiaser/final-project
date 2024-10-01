#include "Player.hpp"
#include "Train.hpp"
Player::Player(const std::string& name)
    : name(name), money(1500), position(0), trainsOwned(0),outOfJailCard(0), isBankrupt(false), isJailed(false) {}

void Player::pay(int amount) {
    if(money - amount < 0){
        std::cout << getName() << " has declared bankruptcy" << std::endl;
        isBankrupt = true;
    }
    money -= amount;
}

void Player::receive(int amount) {
    money += amount;
}

void Player::setPosition(int newPosition) {
    position = newPosition;
}

int Player::getPosition() const {
    return position;
}

const std::string& Player::getName() const {
    return name;
}

int Player::getMoney() const {
    return money;
}

void Player::addProperty(Slot* property) {
    if (property) {
        ownedProperties.push_back(property);
        if (dynamic_cast<Train*>(property)) {
            trainsOwned++;
        }
    }
}

int Player::getTrainCount() const {
    return trainsOwned;
}

void Player::IncrementTrainsOwned(){
    trainsOwned++;
}

std::vector<Slot*> Player::getOwnedProperties(){
    return ownedProperties;
}

void Player::addGetOutOfJailCard(){
    outOfJailCard++;
}

bool Player::removeGetOutOfJailCard(){
    if(outOfJailCard > 0){
        outOfJailCard--;
        return true;
    }
    return false;
}

std::string Player::toString() const{
    std::string output;
    output = name + "\nMoney: " + std::to_string(money) + "\nPosition: " + 
        std::to_string(position) + "\nTrains owned: " + std::to_string(trainsOwned)
         + "\nOut of jail cards: " + std::to_string(outOfJailCard) + "\nBankrupt?: " + std::to_string(isBankrupt)
         + "\nOwned properties:\n";
    for(unsigned int i = 0; i < ownedProperties.size(); i++){
        output += ownedProperties[i]->getName() + "\n";
    }
    if(ownedProperties.size() == 0){
        output += "None\n";
    }
    return output;
}