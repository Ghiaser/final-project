#include "Street.hpp"
#include <iostream>

Street::Street(const std::string& name, int price, int rent, int housePrice, int hotelPrice, struct ColorGroup& colorGroup)
    : Slot(name, true, false), colorGroup(colorGroup), price(price), rent(rent), housePrice(housePrice), hotelPrice(hotelPrice){
        colorGroup.streets.push_back(this);
    }

void Street::landOn(Player& player) {
    if (!isOwned()) {
        // Handle property purchase logic
        std::cout << player.getName() << " landed on " << getName() << " and can purchase it for " << price << "." << std::endl;
        // Logic to allow player to buy the property
        std::cout << "Would you like to purchase " << getName() << "? (y/n)" << std::endl;
        std::string input;
        std::cin >> input;
        if(input == "y" || input == "Y"){
            if(player.getMoney() >= price){
                player.pay(price);
                setOwner(&player);
                player.addProperty(this);
            } else {
                std::cerr << player.getName() << " can't afford this slot!" << std::endl;
            }
        } else if(!(input == "n" || input == "N")){
            std::cerr << "Invalid input, treated as a no." << std::endl;
        }
    } else {
        // Handle rent payment / build house logic
        if(player.getName() != owner->getName()){
            std::cout << player.getName() << " landed on " << getName() << " and has to pay rent to " << owner->getName() << "." << std::endl;
            int totalRent = calculateRent();
            player.pay(totalRent);
            owner->receive(totalRent);
            std::cout << player.getName() << " paid " << totalRent << " in rent to " << owner->getName() << "." << std::endl;
        } else {
            std::cout << player.getName() << " owns the current street." << std::endl;
            for(unsigned int i = 0; i < colorGroup.streets.size(); i++){
                if(colorGroup.streets[i]->owner->getName() != player.getName()){
                    std::cout << player.getName() << " doesn't own the entire color group, he can't build a house here." << std::endl;
                    return;
                }
            }
            std::cout << player.getName() << " owns the entire color group, he can build a house here." << std::endl;
            buildHouse(player);
        }
    }
}

// Logic to build a house on this street
void Street::buildHouse(Player& player) {
    if(houseCount == 4){
        std::cerr << "Would you like to upgrade the houses to a hotel?" << std::endl;
        std::string input;
        std::cin >> input;
        if(input == "y" || input == "Y"){
            if(player.getMoney() >= hotelPrice){
                player.pay(hotelPrice);
                houseCount = 0;
                incrementHotelCount();
            } else {
                std::cerr << player.getName() << " can't afford this slot!" << std::endl;
            }
        } else if(!(input == "n" || input == "N")){
            std::cerr << "Invalid input, treated as a no." << std::endl;
        }
    } else {
        std::cout << "Would you like to purchase a house on property" << getName() << "? (y/n)" << std::endl;
        std::string input;
        std::cin >> input;
        if(input == "y" || input == "Y"){
            if(player.getMoney() >= housePrice){
                player.pay(housePrice);
                incrementHouseCount();
            } else {
                std::cerr << player.getName() << " can't afford this slot!" << std::endl;
            }
        } else if(!(input == "n" || input == "N")){
            std::cerr << "Invalid input, treated as a no." << std::endl;
        }
    }
}

int Street::calculateRent() const {
    int rental = rent;
    for(int i = 0; i < houseCount; i++){
        rental *= 2;
    }
    for(int i = 0; i < hotelCount; i++){
        rental *= 16;
    }
    return rental;
}
