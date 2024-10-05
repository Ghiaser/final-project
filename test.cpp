#include "doctest.h"
#include "Board.hpp"
#include "Player.hpp"
#include "Street.hpp"
#include "Train.hpp"
#include "Dice.hpp"
#include "SpecialSlot.hpp"

using namespace std;

TEST_CASE("Test Board Initialization")
{
    Board board;
    CHECK(board.getNumberOfSlots() == 0); // Check initial slots count

    Slot* goSlot = new Slot("Go", false, false);
    Slot* jailSlot = new Slot("Jail", false, false);
    board.initializeCorners(goSlot, nullptr, jailSlot, nullptr);

    CHECK(board.getSlot(0)->getName() == "Go");
    CHECK(board.getSlot(1)->getName() == "Jail");
}

TEST_CASE("Test Player Functionality")
{
    Player player("Alice");
    CHECK(player.getMoney() == 1500); // Default money

    player.pay(200);
    CHECK(player.getMoney() == 1300); // Money after payment

    player.receive(100);
    CHECK(player.getMoney() == 1400); // Money after receiving

    Slot* street = new Street("Park Place", 350, 35, 50, 200, ColorGroup{"Blue", {}});
    player.addProperty(street);
    CHECK(player.getOwnedProperties().size() == 1);
    CHECK(player.getOwnedProperties()[0]->getName() == "Park Place");

    player.setPosition(5); // Move player
    CHECK(player.getPosition() == 5);
}

TEST_CASE("Test Street Rent Calculation")
{
    ColorGroup blueGroup{"Blue", {}};
    Street street("Boardwalk", 400, 50, 50, 200, blueGroup);
    
    street.buildHouse(nullptr); // Build 1 house
    CHECK(street.calculateRent() == 50); // Rent with 1 house

    street.buildHouse(nullptr); // Build 2nd house
    street.buildHouse(nullptr); // Build 3rd house
    CHECK(street.calculateRent() == 150); // Rent with 3 houses

    street.incrementHotelCount(); // Add a hotel
    CHECK(street.calculateRent() == 450); // Rent with hotel
}

TEST_CASE("Test Train Slot Functionality")
{
    Train train("Reading Railroad", 200, 25);
    Player player("Bob");

    // Test landing on train slot
    train.landOn(player); 
    CHECK(player.getMoney() == 1500); // Ensure player money remains unchanged
}

TEST_CASE("Test Dice Rolling")
{
    Dice dice;
    dice.roll();
    
    CHECK(dice.getTotal() >= 2); // Minimum roll
    CHECK(dice.getTotal() <= 12); // Maximum roll
    CHECK(dice.isDouble() == (dice.getFirst() == dice.getSecond())); // Check if it's a double
}

TEST_CASE("Test Bankruptcy Check")
{
    Player player("Charlie");
    player.pay(2000); // Overdrawn amount

    CHECK(player.getMoney() < 0); // Player should be bankrupt
}

TEST_CASE("Test Special Actions")
{
    Game game;
    game.initializeGame();

    Player player("Diana");
    SpecialSlot specialSlot("Advance to Go", &game, game.getBoard(), SpecialAction::AdvanceToGo);
    game.addPlayer(player);

    // Simulate landing on a special slot
    specialSlot.landOn(player);
    CHECK(player.getPosition() == 0); // Player should move to "Go"
    CHECK(player.getMoney() == 1500); // Ensure player money is unchanged
}

TEST_CASE("Test Special Slot Actions")
{
    Game game;
    Board board;
    Player player("Ethan");
    SpecialSlot specialSlot("Go to Jail", &game, board, SpecialAction::GoToJail);
    game.addPlayer(player);

    // Simulate landing on the "Go to Jail" slot
    specialSlot.landOn(player);
    CHECK(player.getPosition() == board.getJailIndex()); // Player should be in jail
}

TEST_CASE("Test Property Trading")
{
    Player player1("Alice");
    Player player2("Bob");

    Street* street1 = new Street("Park Place", 350, 35, 50, 200, ColorGroup{"Blue", {}});
    Street* street2 = new Street("Boardwalk", 400, 50, 50, 200, ColorGroup{"Blue", {}});

    player1.addProperty(street1);
    player2.addProperty(street2);

    // Trade street1 for some money
    player1.addProperty(street2); // Player 1 receives Boardwalk
    player2.pay(100); // Player 2 pays $100
    CHECK(player1.getOwnedProperties().size() == 2); // Player 1 should have both properties
    CHECK(player2.getOwnedProperties().size() == 1); // Player 2 should have 1 property
}

TEST_CASE("Test Train Ownership and Rent")
{
    Player player("Fiona");
    Train train("Reading Railroad", 200, 25);
    
    player.addProperty(&train);
    train.landOn(player);
    
    CHECK(player.getMoney() == 1500); // Check initial money
    player.pay(train.getTaxPerTrain()); // Check rent payment
    CHECK(player.getMoney() == 1475); // Money after paying rent
}

TEST_CASE("Test Invalid Actions")
{
    Player player("Gina");
    CHECK_THROWS(player.pay(2000)); // Should throw exception if trying to pay more than money
}

TEST_CASE("Test Game Over Conditions")
{
    Game game;
    Player player1("Alice");
    Player player2("Bob");
    
    game.addPlayer(player1);
    game.addPlayer(player2);

    player1.pay(1600); // Player 1 goes bankrupt
    game.checkBankruptcy(player1);
    
    CHECK(game.isGameOver() == true); // Game should be over
}
