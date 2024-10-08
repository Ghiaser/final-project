#include "GUI.hpp"
#include <string>
#include <sstream>

GUI::GUI() : window(sf::VideoMode(1000, 1000), "Monopoly"), game() {
    if (!backgroundTexture.loadFromFile("board.jpeg")) {
        std::cerr << "Could not load background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    float targetWidth = 600.f;
    float targetHeight = 600.f;

    float scaleX = targetWidth / backgroundTexture.getSize().x; // Width scale
    float scaleY = targetHeight / backgroundTexture.getSize().y; // Height scale

    backgroundSprite.setScale(scaleX, scaleY);
    setupPlayers();
}
void GUI::setupPlayers() {
    // Initialize player names
    int numPlayers = 0;
    bool validInput = false;

    // Input for number of players
    while (!validInput) {
        // Display input prompt
        window.clear();
        displayText("Enter number of players (2-8):");
        std::cin >> numPlayers;

        if (numPlayers >= 2 && numPlayers <= 8) {
            validInput = true;
        } else {
            window.clear();
            displayText("Invalid number of players. Please enter a valid number.");
        }
    }

    // Input for player names
    validInput = false;
    while (!validInput) {
        window.clear();
        displayText("Want to use default names (Player1, Player2, ...)? (y/n)");
        std::string input;
        std::cin >> input;
        if (input == "y" || input == "Y") {
            for (int i = 0; i < numPlayers; ++i) {
                std::string playerName = "Player" + std::to_string(i + 1);
                game.addPlayer(Player(playerName));
            }
            validInput = true;
        } else if (input == "n" || input == "N") {
            for (int i = 0; i < numPlayers; ++i) {
                std::stringstream prompt;
                prompt << "Enter name for player " << (i + 1) << ":";
                window.clear();
                displayText(prompt.str());
                std::string playerName;
                std::cin >> playerName;
                game.addPlayer(Player(playerName));
            }
            validInput = true;
        } else {
            window.clear();
            displayText("Invalid input. Please enter 'y' or 'n'.");
        }
    }
}

void GUI::run() {
    while (window.isOpen()) {
        // Main game loop
        while (!game.isGameOver()) {
            for (auto& player : game.getPlayers()) {
                handleEvents();
                render();
                displayText(player.getName() + "'s turn. Press Enter to roll the dice...");
                std::cin.ignore();
                game.playerTurn(player);
                if (game.isGameOver()) {
                    break; // Exit if game is over
                }
            }
        }

        // Determine and display the winner
        Player winner = game.getWinner();
        displayText(winner.getName() + " wins the game!");
    }
}

void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GUI::render() {
    window.clear();
    window.draw(backgroundSprite); // Draw the background image
    drawPlayers();
    drawPlayersPositions();
    drawGameInfo();
    window.display();
}

void GUI::drawBoard() {
    // Load and draw the game board here (replace with actual drawing logic)
    sf::RectangleShape board(sf::Vector2f(600, 600));
    board.setFillColor(sf::Color::Green);
    window.draw(board);
}

void GUI::drawPlayers() {
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Couldn't load font!" << std::endl;
    }

    // Positioning variables
    float startY = 650; // Start drawing player info below the image
    float startX = 10;   // Left margin
    float spacingX = 100; // Space between player name columns

    // Draw player names and their information
    for (size_t i = 0; i < game.getPlayers().size(); ++i) {
        const Player& player = game.getPlayers()[i];

        // Draw player name
        sf::Text playerNameText(player.toString(), font, 12);
        playerNameText.setFillColor(sf::Color::White);
        playerNameText.setPosition(startX + i * spacingX, startY);
        window.draw(playerNameText);
    }
}

void GUI::drawPlayersPositions() {
    // Loop through each player to draw their position
    int colorIndex = 0;
    for (const auto& player : game.getPlayers()) {
        unsigned int position = player.getPosition(); // Get player's current position
        int x = 0, y = 0;
        int boardSize = 600;
        int space = 50;
        // Determine x and y based on the position, moving clockwise
        if(position == 0){
            x = 540;
            y = 540;
        } else if (position > 0 && position <= 9) {
            x = boardSize - (position * space + space);
            y = boardSize - space;
        } else if(position == 10){
            x = 25;
            y = 540;
        } else if (position > 10 && position <= 18) {
            x = space/2;
            y = boardSize - ((position - 10) * space + space);
        } else if(position == 19){
            x = 25;
            y = 55;
        } else if (position > 19 && position <= 28) {
            x = (28 - position) * space + space;
            y = space/2;
        } else if(position == 29){
            x = 540;
            y = 25;
        } else if (position > 29 && position <= 37) {
            x = boardSize - space;
            y = (position - 29) * space + space;
        }

        // Create a colored circle for the player
        sf::CircleShape playerBall(10); // Radius of 15 pixels
        playerBall.setFillColor(playerColors[colorIndex]); // Use the primary color
        playerBall.setPosition(x, y); // Set position based on calculated x and y

        window.draw(playerBall); // Draw the player ball
        colorIndex++;
    }
}

void GUI::drawGameInfo() {
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Couldn't load font!" << std::endl;
    }
    Dice dice = game.getDice();
    std::stringstream roundInfo;
    //roundInfo << "Round: " << game.getCurrentRound() << "\n"; // Assuming you have this function
    roundInfo << "Dice Values: " << dice.getFirst() << ", " << dice.getSecond(); // Replace with actual values

    sf::Text roundText(roundInfo.str(), font, 24);
    roundText.setFillColor(sf::Color::White);
    roundText.setPosition(1000, 10); // Adjust position as needed
    window.draw(roundText);
}


void GUI::displayText(const std::string& message) {
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cerr << "couldn't load font" << std::endl;
    }
    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setString(message);
    text.setPosition(10, 620); // Position it where you want to display it

    // Display the message
    window.draw(text);
    window.display();
}
