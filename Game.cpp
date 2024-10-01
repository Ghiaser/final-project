#include <iostream>
#include <algorithm>
#include "Game.hpp"
#include "SpecialSlot.hpp"
#include "Train.hpp"
Game::Game():board(), currentPlayerIndex(0), gameOver(false), doubleCounter(0), dice() {
    initializeGame();
    initializeCorners();
}

Game::Game(const std::vector<std::string>& playerNames)
    : board(), currentPlayerIndex(0), gameOver(false) {
    // Create players based on the provided names
    for (const auto& name : playerNames) {
        players.emplace_back(name);
    }
    initializeGame();
    initializeCorners();
}

void Game::initializeGame() {
    // Set up the board and add slots
    // Example slots (you will need to create the actual Slot subclasses and instances)
    std::vector<ColorGroup>& colorGroups = board.getColorGroups();
    board.addSlot(new Street("MEDITERRANEAN AVENUE", 60, 50, 100, 200, colorGroups[0]));
    board.addSlot(new SpecialSlot("COMMUNITY CHEST", this, board, SpecialAction::CommunityChest));
    board.addSlot(new Street("BALTIC AVENUE", 60, 50, 100, 200, colorGroups[0]));
    board.addSlot(new SpecialSlot("INCOME TAX", this, board, SpecialAction::PoorTax));
    board.addSlot(new Train("READING RAILROAD" , 200, 50));
    board.addSlot(new Street("ORIENTAL AVENUE", 100, 50, 100, 200, colorGroups[1]));
    board.addSlot(new SpecialSlot("CHANCE", this, board, SpecialAction::Any));
    board.addSlot(new Street("VERMONT AVENUE", 100, 50, 100, 200, colorGroups[1]));
    board.addSlot(new Street("CONNECTICUT AVENUE", 120, 50, 100, 200, colorGroups[1]));
    
    board.addSlot(new Street("ST.CHARLES PLACE", 140, 50, 100, 200, colorGroups[2]));
    board.addSlot(new SpecialSlot("ELECTRIC COMPANY", this, board, SpecialAction::ElectricCompany));
    board.addSlot(new Street("STATES AVENUE", 140, 50, 100, 200, colorGroups[2]));
    board.addSlot(new Street("VIRGINIA AVENUE", 160, 50, 100, 200, colorGroups[2]));
    board.addSlot(new Train("PENNSYLVANIA RAILROAD", 200, 50));
    board.addSlot(new Street("ST.JAMES PLACE", 180, 50, 100, 200, colorGroups[3]));
    board.addSlot(new SpecialSlot("COMMUNITY CHEST", this, board, SpecialAction::CommunityChest));
    board.addSlot(new Street("TENNESSE AVENUE", 180, 50, 100, 200, colorGroups[3]));
    board.addSlot(new Street("NEW YORK AVENUE", 200, 50, 100, 200, colorGroups[3]));
    
    board.addSlot(new Street("KENTUCKY AVENUE", 220, 50, 100, 200, colorGroups[4]));
    board.addSlot(new SpecialSlot("CHANCE", this, board, SpecialAction::Any));
    board.addSlot(new Street("INDIANA AVENUE", 220, 50, 100, 200, colorGroups[4]));
    board.addSlot(new Street("ILLINOIS AVENUE", 240, 50, 100, 200, colorGroups[4]));
    board.addSlot(new Train("B.&O. RAILROAD", 200, 50));
    board.addSlot(new Street("ATLANTIC AVENUE", 260, 50, 100, 200, colorGroups[5]));
    board.addSlot(new Street("VENTNOR AVENUE", 260, 50, 100, 200, colorGroups[5]));
    board.addSlot(new SpecialSlot("WATER WORKS", this, board, SpecialAction::WaterWorks));
    board.addSlot(new Street("MARVIN GARDENS", 280, 50, 100, 200, colorGroups[5]));

    board.addSlot(new Street("PACIFIC AVENUE", 300, 50, 100, 200, colorGroups[6]));
    board.addSlot(new Street("NORTH CAROLINA AVENUE", 300, 50, 100, 200, colorGroups[6]));
    board.addSlot(new SpecialSlot("COMMUNITY CHEST", this, board, SpecialAction::CommunityChest));
    board.addSlot(new Street("PENNSYLVANIA AVENUE", 320, 50, 100, 200, colorGroups[6]));
    board.addSlot(new Train("SHORT LINE", 200, 50));
    board.addSlot(new SpecialSlot("CHANCE", this, board, SpecialAction::Any));
    board.addSlot(new Street("PARK PLACE", 350, 50, 100, 200, colorGroups[7]));
    board.addSlot(new SpecialSlot("LUXURY TAX", this, board, SpecialAction::LuxuryTax));
    board.addSlot(new Street("BOARDWALK", 400, 50, 100, 200, colorGroups[7]));
    std::cerr << "board size: " << board.getNumberOfSlots() << std::endl;
}

void Game::initializeCorners(){
    if(board.getNumberOfSlots() % 4 != 0){
        std::cerr << "The game must be a square (dividable by 4!" << std::endl;
        exit(1);
    }
    Slot* Go = new SpecialSlot("Go", this, board, SpecialAction::AdvanceToGo);
    Slot* goToJail = new SpecialSlot("Go", this, board, SpecialAction::GoToJail);
    Slot* Jail = new SpecialSlot("Go", this, board, SpecialAction::Jail);
    Slot* FreeParking = new SpecialSlot("Go", this, board, SpecialAction::FreeParking);
    board.initializeCorners(Go, goToJail, Jail, FreeParking);
}

void Game::playTurn() {
    Player& currentPlayer = players[currentPlayerIndex];
    
    std::cout << currentPlayer.getName() << "'s turn." << std::endl;
    
    dice.roll();
    int totalRoll = dice.getTotal();
    
    // Move the player on the board
    int newPosition = (currentPlayer.getPosition() + totalRoll) % board.getNumberOfSlots();
    currentPlayer.setPosition(newPosition);
    
    // Display the move
    std::cout << currentPlayer.getName() << " rolled a " << totalRoll
              << " and moved to position " << newPosition << "." << std::endl;
    
    // Check for doubles (to allow another turn)
    if (dice.isDouble()) {
        doubleCounter++;
        if(doubleCounter != 3){
            std::cout << currentPlayer.getName() << " rolled a double! Another turn! Total doubles so far: " << doubleCounter << std::endl;
        } else {
            std::cout << currentPlayer.getName() << " rolled his 3rd double! Time to go to Jail!" << std::endl;
            if(currentPlayer.removeGetOutOfJailCard()){
                std::cout << currentPlayer.getName() << " Skipped jail time thanks to his out of jail card!" << std::endl;
            } else {
                currentPlayer.setPosition(board.getJailIndex()); // Assuming Jail is at index 10
                std::cout << currentPlayer.getName() << " goes directly to Jail!" << std::endl;
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
                doubleCounter = 0;
            }
        }
    }

    // Handle landing on the slot
    Slot* landedSlot = board.getSlot(newPosition);
    landedSlot->landOn(currentPlayer);
    
    // Check for bankruptcy
    checkBankruptcy(currentPlayer);
    
    if(!dice.isDouble()){
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        doubleCounter = 0;
    }
}

void Game::checkBankruptcy(Player& player) {
    if (player.getMoney() < 0) {
        std::cout << player.getName() << " is bankrupt!" << std::endl;
        // Handle bankruptcy logic
        // For example, remove player from the game
        players.erase(std::remove_if(players.begin(), players.end(),
            [&player](const Player& p) { return p.getName() == player.getName(); }), players.end());
    }
}

void Game::endGame() {
    gameOver = true;
    // Determine the winner
    if (!players.empty()) {
        std::cout << players[0].getName() << " wins!" << std::endl;
    }
}

void Game::displayGameState() {
    for (const auto& player : players) {
        std::cout << player.getName() << ": " << player.getMoney() << " Shekels, Position: " 
                  << player.getPosition() << std::endl;
    }
}

void Game::addPlayer(const Player& player) {
    players.push_back(player);
}

bool Game::isGameOver() const {
    // Implement logic to determine if the game is over
    // For example, check if only one player is left with money
    int activePlayers = 0;
    for (const auto& player : players) {
        if (player.getMoney() > 0) {
            ++activePlayers;
        }
    }
    return activePlayers <= 1; // Game over if one or fewer players have money
}

std::vector<Player>& Game::getPlayers(){
    return players;
}

// The player's turn logic    
void Game::playerTurn(Player& player) {
    std::cout << player.getName() << "'s turn. Rolling dice..." << std::endl;

    Dice dice;
    dice.roll();

    int moveSteps = dice.getTotal();
    std::cout << player.getName() << " rolled a " << moveSteps << "!" << std::endl;
    player.setPosition(player.getPosition() + moveSteps);
    if(player.getPosition() > board.getNumberOfSlots()){
        std::cout << player.getName() << " has passed by the start mark and received 200!" << std::endl;
        player.receive(200);
        std::cerr << "number of slots: " << board.getNumberOfSlots() << std::endl;
        player.setPosition(player.getPosition() % board.getNumberOfSlots());
    }
    board.getSlot(player.getPosition())->landOn(player);
}

Player Game::getWinner() const {
    // Determine and return the winner (the last player remaining with money)
    for (const auto& player : players) {
        if (player.getMoney() > 0) {
            return player;
        }
    }
    // Return a default player if no winner is found (error handling can be improved)
    return Player("No Winner");
}

int Game::getCurrentPlayerIndex(){
    return currentPlayerIndex;
}

Dice Game::getDice(){
    return dice;
}