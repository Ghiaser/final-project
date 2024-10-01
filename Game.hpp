#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Board.hpp"
#include "Slot.hpp"
#include "Player.hpp"
#include "Dice.hpp"
class Game {
private:
    Board board;
    std::vector<Player> players;
    int currentPlayerIndex;
    bool gameOver;
    int doubleCounter;
    Dice dice;
public:
    Game(); // Empty constructor
    Game(const std::vector<std::string>& playerNames);
    void initializeGame();
    void initializeCorners();
    void playTurn();
    void checkBankruptcy(Player& player);
    void endGame();
    void displayGameState();
    void addPlayer(const Player& player);
    bool isGameOver() const;
    std::vector<Player>& getPlayers();
    void playerTurn(Player& player);
    Player getWinner() const;
    int getCurrentPlayerIndex();
    Dice getDice();
    
};

#endif // GAME_H
