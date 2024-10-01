#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Slot.hpp"
#include "Street.hpp"
// Define a structure for color groups
class Street;
struct ColorGroup {
    std::string name;
    std::vector<Street*> streets; // Stores streets belonging to this color group
};

class Board {
private:
    std::vector<Slot*> slots; // Vector to hold pointers to Slot objects
    std::vector<ColorGroup> colorGroups; // Stores color groups
    int jailIndex;
    int IllinoisAveIndex;
    int CharlesPlaceIndex;

public:
    Board();
    ~Board(); // Destructor to clean up dynamically allocated slots

    void initializeCorners(Slot* Go, Slot* goToJail, Slot* Jail, Slot* FreeParking);
    void addSlot(Slot* slot); // Add a slot to the board
    Slot* getSlot(int index) const; // Get a slot by index
    int getNumberOfSlots() const; // Get the total number of slots
    int getJailIndex();
    int getIllinoisAveIndex();
    int getCharlesPlaceIndex();
    int getNearestUtilityIndex(int startPosition);
    int getNearestRailroadIndex(int startPosition);
    void initializeColorGroups(); // Initialize color groups and add streets
    std::vector<ColorGroup>& getColorGroups();
};

#endif // BOARD_H
