#ifndef SLOT_H
#define SLOT_H

#include <string>
#include "Player.hpp"
class Player;
class Slot {
protected:
    std::string name;
    bool owned;
    Player* owner; // Pointer to the owning player
    int houseCount;
    int hotelCount;
    bool isUtility;
    bool isRailroad;

public:
    Slot(const std::string& name, bool isUtility, bool isRailroad);
    virtual ~Slot() = default;

    virtual void landOn(Player& player) = 0; // Pure virtual function
    const std::string& getName() const;
    bool isOwned() const;
    void setOwner(Player* newOwner);
    int getHouseCount() const;
    int getHotelCount() const;
    void incrementHouseCount();
    void incrementHotelCount();
    bool getIsUtility();
    bool getIsRailroad();
};

#endif // SLOT_H
