#include <iostream>
#include "Board.hpp"
#include "SpecialSlot.hpp"
#include "Train.hpp"
// Constructor to initialize the board
Board::Board(): jailIndex(0) {
    initializeColorGroups();
}

// Destructor to clean up dynamically allocated slots
Board::~Board() {
    for (auto slot : slots) {
        delete slot;
    }
}
void Board::initializeCorners(Slot* Go, Slot* goToJail, Slot* Jail, Slot* FreeParking){
    int step = slots.size() / 4;
    slots.insert(slots.begin() + 0, Go);
    slots.insert(slots.begin() + step + 1, Jail);
    slots.insert(slots.begin() + step * 2 + 2, FreeParking);
    slots.insert(slots.begin() + step * 3 + 3, goToJail);
}

// Add a new slot to the board
void Board::addSlot(Slot* slot) {
    slots.push_back(slot);
}

// Get a slot by index
Slot* Board::getSlot(int index) const {
    if (index >= 0 && (unsigned int)index < slots.size()) {
        return slots[index];
    }
    return nullptr; // Return nullptr for invalid index
}

// Get the total number of slots
int Board::getNumberOfSlots() const {
    return slots.size();
}

// Initialize color groups and add streets to them
void Board::initializeColorGroups() {
    // Define color groups and their respective streets
    colorGroups.push_back({"Brown", {}});
    colorGroups.push_back({"Light Blue", {}});
    colorGroups.push_back({"Pink", {}});
    colorGroups.push_back({"Orange", {}});
    colorGroups.push_back({"Red", {}});
    colorGroups.push_back({"Yellow", {}});
    colorGroups.push_back({"Green", {}});
    colorGroups.push_back({"Dark Blue", {}});
}

int Board::getJailIndex(){
    if(jailIndex == -1){
        for(unsigned int i = 0; i < slots.size(); i++){
            if(slots[i]->getName() == "JAIL"){
                jailIndex = i;
            }
        }
    }
    return jailIndex;
}

int Board::getIllinoisAveIndex(){
    if(IllinoisAveIndex == -1){
        for(unsigned int i = 0; i < slots.size(); i++){
            if(slots[i]->getName() == "ILLINOIS AVENUE"){
                IllinoisAveIndex = i;
            }
        }
    }
    if(IllinoisAveIndex == -1){
        std::cerr << "Illinois Aven doesn't exist, advancing to go" << std::endl;
        return 0;
    }
    return IllinoisAveIndex;
}
int Board::getCharlesPlaceIndex(){
    if(CharlesPlaceIndex == -1){
        for(unsigned int i = 0; i < slots.size(); i++){
            if(slots[i]->getName() == "ST.CHARLES PLACE"){
                CharlesPlaceIndex = i;
            }
        }
    }
    if(CharlesPlaceIndex == -1){
        std::cerr << "ST.CHARLES PLACE doesn't exist, advancing to go" << std::endl;
        return 0;
    }
    return CharlesPlaceIndex;
}


int Board::getNearestUtilityIndex(int startPosition){
    for(int i = startPosition+1; i != startPosition; i = (i + 1 ) % slots.size()){
        if(slots[i]->getIsUtility()){
            return i;
        }
    }
    std::cerr << "No ulitily found, probably an error, check the code." << std::endl;
    return 0;
}

int Board::getNearestRailroadIndex(int startPosition){
    for(int i = startPosition+1; i != startPosition; i = (i + 1 ) % slots.size()){
        if(slots[i]->getIsRailroad()){
            return i;
        }
    }
    std::cerr << "No railroad found, probably an error, check the code." << std::endl;
    return 0;
}

std::vector<ColorGroup>& Board::getColorGroups(){
    return colorGroups;
}