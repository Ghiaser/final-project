#include "Train.hpp"
#include <iostream>

Train::Train(const std::string& name, int cost, int taxPerTrain)
    : Slot(name, false, true), cost(cost), taxPerTrain(taxPerTrain) {}

void Train::landOn(Player& player) {
    if (!isOwned()) {
        // Logic for purchasing the train
        std::cout << player.getName() << " landed on " << getName() << " and can purchase it for " << cost << "." << std::endl;
        // Logic to allow player to buy the property
        std::cout << "Would you like to purchase " << getName() << "? (y/n)" << std::endl;
        std::string input;
        std::cin >> input;
        if(input == "y" || input == "Y"){
            if(player.getMoney() >= cost){
                player.pay(cost);
                setOwner(&player);
                player.addProperty(this);
                player.IncrementTrainsOwned();
            } else {
                std::cerr << player.getName() << " can't afford this slot!" << std::endl;
            }
        } else if(!(input == "n" || input == "N")){
            std::cerr << "Invalid input, treated as a no." << std::endl;
        }
    } else {
        // Logic for paying tax based on number of trains owned by the owner
        if(owner->getName() != player.getName()){
            int ownerTrainCount = owner->getTrainCount();
            int totalTax = ownerTrainCount * taxPerTrain;
            player.pay(totalTax);
            owner->receive(totalTax);
            std::cout << player.getName() << " paid " << totalTax << " in tax to " << owner->getName() << "." << std::endl;
        } else {
            std::cout << player.getName() << " owns the current train." << std::endl;
        }
    }
}