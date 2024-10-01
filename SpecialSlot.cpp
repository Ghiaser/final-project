#include "SpecialSlot.hpp"
#include <iostream>

SpecialSlot::SpecialSlot(const std::string& name, Game* game, Board& board, SpecialAction action): Slot(name, false, false), game(game), board(board), action(action) {}

void SpecialSlot::landOn(Player& player){
    if(action == SpecialAction::Any){
        executeAction(player, getAction());
    } else {
        executeAction(player, action);
    }
}

void SpecialSlot::executeAction(Player& player, SpecialAction action) {
    switch (action) {
        case SpecialAction::Any:
            //unreachable
            break;
        case SpecialAction::Jail:
            if(!player.removeGetOutOfJailCard())
                player.isJailed = true;
            break;
        case SpecialAction::FreeParking:
            std::cout << player.getName() << " Parked for free." << std::endl;
            break;
        case SpecialAction::AdvanceToGo:
            player.receive(200);
            player.setPosition(0); // Assuming Go is at index 0
            std::cout << player.getName() << " advances to Go and collects $200!" << std::endl;
            break;

        case SpecialAction::BankDividend:
            player.receive(50);
            std::cout << player.getName() << " receives a dividend of $50!" << std::endl;
            break;

        case SpecialAction::GoBack3Spaces:
            {
                int currentPosition = player.getPosition();
                player.setPosition(currentPosition - 3);
                std::cout << player.getName() << " goes back 3 spaces!" << std::endl;
                board.getSlot(player.getPosition())->landOn(player); //reland on the new slot
            }
            break;

        case SpecialAction::GoToJail:
            player.setPosition(board.getJailIndex()); // Assuming Jail is at index 10
            std::cout << player.getName() << " goes directly to Jail!" << std::endl;
            break;

        case SpecialAction::GeneralRepairs:
            {
                int totalCost = 0;
                for (const auto& street : player.getOwnedProperties()) {
                    totalCost += (street->getHouseCount() * 25) + (street->getHotelCount() * 100);
                }
                player.pay(totalCost);
                std::cout << player.getName() << " pays $" << totalCost << " for repairs!" << std::endl;
            }
            break;

        case SpecialAction::PoorTax:
            player.pay(15);
            std::cout << player.getName() << " pays a poor tax of $15!" << std::endl;
            break;

        case SpecialAction::TripToReadingRailroad:
            player.setPosition(5); // Assuming Reading Railroad is at index 5
            if (player.getPosition() == 0) {
                player.receive(200);
                std::cout << player.getName() << " passes Go and collects $200!" << std::endl;
            }
            std::cout << player.getName() << " takes a trip to Reading Railroad!" << std::endl;
            break;

        case SpecialAction::WalkOnBoardwalk:
            player.setPosition(39); // Assuming Boardwalk is at index 39
            std::cout << player.getName() << " advances to Boardwalk!" << std::endl;
            break;

        case SpecialAction::ElectedChairman:
            for (auto& otherPlayer : game->getPlayers()) {
                if (otherPlayer.getName() != player.getName()) {
                    otherPlayer.pay(50);
                    player.receive(50);
                }
            }
            std::cout << player.getName() << " pays each player $50!" << std::endl;
            break;

        case SpecialAction::LoanMaturity:
            player.receive(150);
            std::cout << player.getName() << " collects $150 from matured loan!" << std::endl;
            break;

        case SpecialAction::GetOutOfJailFree:
            player.addGetOutOfJailCard();
            std::cout << player.getName() << " receives a Get Out of Jail Free card!" << std::endl;
            break;

        case SpecialAction::AdvanceToIllinois:
            if (player.getPosition() > board.getIllinoisAveIndex()) {
                player.receive(200);
                std::cout << player.getName()  << " has passed the GO point and received $200" << std::endl;
            }
            player.setPosition(board.getIllinoisAveIndex());
            break;

        case SpecialAction::AdvanceToStCharles:
            if (player.getPosition() > board.getCharlesPlaceIndex()) {
                player.receive(200);
                std::cout << player.getName()  << " has passed the GO point and received $200" << std::endl;
            }
            player.setPosition(board.getCharlesPlaceIndex());
            break;

        case SpecialAction::AssessStreetRepairs:
            {
                int totalCost = 0;
                for (const auto& street : player.getOwnedProperties()) {
                    totalCost += (street->getHouseCount() * 40) + (street->getHotelCount() * 115);
                }
                player.pay(totalCost);
                std::cout << player.getName() << " pays $" << totalCost << " for street repairs!" << std::endl;
            }
            break;

        case SpecialAction::AdvanceToNearestUtility:
            {
                // Implement logic for advancing to nearest utility
                int currentPosition = player.getPosition();
                player.setPosition(board.getNearestUtilityIndex(player.getPosition()));
                if(currentPosition > player.getPosition()){
                    player.receive(200);
                    std::cout << player.getName()  << " has passed the GO point and received $200" << std::endl;
                }
            }
            break;
        case SpecialAction::AdvanceToNearestRailroad:
            {
                    // Implement logic for advancing to nearest utility
                int currentPosition = player.getPosition();
                player.setPosition(board.getNearestRailroadIndex(player.getPosition()));
                if(currentPosition > player.getPosition()){
                    player.receive(200);
                    std::cout << player.getName()  << " has passed the GO point and received $200" << std::endl;
                }
            }
            break;
        case SpecialAction::ElectricCompany:
            player.pay(150);
            std::cout << player.getName() << " pays a electric bill of $150!" << std::endl;
            break;
        case SpecialAction::WaterWorks:
            player.pay(150);
            std::cout << player.getName() << " pays a water bill of $150!" << std::endl;
            break;
        case SpecialAction::LuxuryTax:
            player.pay(100);
            std::cout << player.getName() << " pays a luxury tax of $100!" << std::endl;
            break;
        case SpecialAction::CommunityChest:
            int random = rand() % 100;
            player.receive(random);
            std::cout << player.getName() << " found $" << random << " in community chest!" << std::endl;
            break;        
    }
}

SpecialAction SpecialSlot::getAction(){
    return SpecialAction(rand() % 16);
}