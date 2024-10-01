#ifndef SPECIAL_SLOT_H
#define SPECIAL_SLOT_H

#include "Game.hpp"
#include "Board.hpp"
#include "Slot.hpp"

class Game;
class Board;
// Enum for special actions
enum class SpecialAction {
    AdvanceToGo,
    BankDividend,
    GoBack3Spaces,
    GoToJail,
    GeneralRepairs,
    PoorTax,
    TripToReadingRailroad,
    WalkOnBoardwalk,
    ElectedChairman,
    LoanMaturity,
    GetOutOfJailFree,
    AdvanceToIllinois,
    AdvanceToStCharles,
    AssessStreetRepairs,
    AdvanceToNearestUtility,
    AdvanceToNearestRailroad,
    ElectricCompany,
    WaterWorks,
    LuxuryTax,
    CommunityChest,
    Jail,
    FreeParking,
    Any
};

class SpecialSlot : public Slot {
private:
    Game* game;
    Board& board;
    SpecialAction action;
public:
    SpecialSlot(const std::string& name, Game* game, Board& board, SpecialAction action);
    void landOn(Player& player) override;
    void executeAction(Player& player, SpecialAction action);

    SpecialAction getAction();
};

#endif // SPECIAL_SLOT_H
