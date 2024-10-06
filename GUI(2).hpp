#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
class GUI {
private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture; // Texture for the background
    sf::Sprite backgroundSprite;    // Sprite to display the background
    const std::vector<sf::Color> playerColors = {
        sf::Color::Cyan,
        sf::Color::Red,
        sf::Color::Yellow,
        sf::Color::Blue,
        sf::Color::Magenta,
        sf::Color::Green,
        sf::Color::White,
        sf::Color::Black
    };
public:
    Game game; // Pointer to the game to access its state
    GUI();
    void setupPlayers();
    void run(); // Main loop to run the GUI
    void render(); // Function to render the game state
    void handleEvents(); // Function to handle user input
    void drawBoard(); // Function to draw the game board
    void drawPlayers(); // Function to draw players
    void drawGameInfo(); // Function to draw game information
    void displayText(const std::string& message);
    void drawPlayersPositions();
};

#endif // GUI_H
