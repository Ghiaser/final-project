#include "Slot.hpp"

Slot::Slot(const std::string& name, bool isUtility, bool isRailroad)
    : name(name), owned(false), owner(nullptr), houseCount(0), hotelCount(0), isUtility(isUtility), isRailroad(isRailroad) {}

const std::string& Slot::getName() const {
    return name;
}

bool Slot::isOwned() const {
    return owned;
}

void Slot::setOwner(Player* newOwner) {
    owner = newOwner;
    owned = (newOwner != nullptr);
}

int Slot::getHouseCount() const {
    return houseCount;
}

int Slot::getHotelCount() const {
    return hotelCount;
}


void Slot::incrementHouseCount(){
    houseCount++;
}

void Slot::incrementHotelCount(){
    hotelCount++;
}

bool Slot::getIsUtility(){
    return isUtility;
}
bool Slot::getIsRailroad(){
    return isRailroad;
}