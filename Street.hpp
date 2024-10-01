#ifndef STREET_H
#define STREET_H

#include <string>
#include "Board.hpp"
#include "Slot.hpp"

class Street : public Slot {
private:
    struct ColorGroup& colorGroup;
    int price;
    int rent;
    int housePrice;
    int hotelPrice;

public:
    Street(const std::string& name, int price, int rent, int housePrice, int hotelPrice, struct ColorGroup& colorGroup);
    void landOn(Player& player) override;
    void buildHouse(Player& player);
    int calculateRent() const;
};

#endif // STREET_H
