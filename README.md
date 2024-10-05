```markdown
# Monopoly Game Project

## Overview

This project implements a digital version of the classic Monopoly board game. Players buy, sell, and trade properties while trying to bankrupt their opponents. The game features streets, railroads, utilities, and special slots that enhance the strategic gameplay.

## Features

- **Board Management**: Organizes slots and maintains game state.
- **Player Interaction**: Players can buy properties, pay rent, and manage finances.
- **Dice Rolling**: Simulates rolling two six-sided dice.
- **Graphical User Interface (GUI)**: Built with SFML for an engaging user experience.
- **Game Mechanics**: Includes bankruptcy rules, special actions, and property management.

## Getting Started

### Prerequisites

- C++ Compiler (g++, clang++)
- CMake (for building the project)
- SFML (Simple and Fast Multimedia Library)

### Installation

1. **Clone the repository**:
   ```bash
   git clone 
   cd monopoly-game
   ```

2. **Build the project**:
   ```bash
   make
   ```

3. **Run the game**:
   ```bash
   ./monopoly
   ```

## Main Components

### Board Class

- **Attributes**:
  - `std::vector<Slot*> slots`: Holds pointers to all slots on the board.
  - `std::vector<ColorGroup> colorGroups`: Manages color groups for properties.
  - `int jailIndex`, `int IllinoisAveIndex`, `int CharlesPlaceIndex`: Specific indexes for certain slots.

- **Functions**:
  - `Board()`: Constructor initializes the board.
  - `~Board()`: Destructor to clean up dynamically allocated slots.
  - `void initializeCorners(Slot* Go, Slot* goToJail, Slot* Jail, Slot* FreeParking)`: Sets up corner slots.
  - `void addSlot(Slot* slot)`: Adds a new slot to the board.
  - `Slot* getSlot(int index) const`: Retrieves a slot by its index.
  - `int getNumberOfSlots() const`: Returns the total number of slots on the board.
  - `void initializeColorGroups()`: Initializes and organizes color groups.

### Slot Class

- **Attributes**:
  - `std::string name`: Name of the slot.
  - `bool owned`: Indicates if the slot is owned.
  - `Player* owner`: Pointer to the owning player.

- **Functions**:
  - `virtual void landOn(Player& player) = 0`: Pure virtual function to define actions when a player lands on the slot.
  - `const std::string& getName() const`: Returns the slot's name.
  - `void setOwner(Player* newOwner)`: Sets the owner of the slot.

### Street Class

- **Inherits from**: `Slot`

- **Attributes**:
  - `struct ColorGroup& colorGroup`: Reference to the color group the street belongs to.
  - `int price`, `int rent`, `int housePrice`, `int hotelPrice`: Financial details related to the street.

- **Functions**:
  - `void landOn(Player& player) override`: Executes actions when a player lands on the street.
  - `void buildHouse(Player& player)`: Allows a player to build a house on the street.
  - `int calculateRent() const`: Calculates the rent based on the number of houses/hotels.

### Train Class

- **Inherits from**: `Slot`

- **Attributes**:
  - `int cost`, `int taxPerTrain`: Cost of the train and tax per train owned.

- **Functions**:
  - `void landOn(Player& player) override`: Defines actions for landing on a train slot.

### SpecialSlot Class

- **Inherits from**: `Slot`

- **Attributes**:
  - `Game* game`: Pointer to the game instance.
  - `SpecialAction action`: Enum defining the special action triggered.

- **Functions**:
  - `void landOn(Player& player) override`: Executes a special action when landed on.

### Player Class

- **Attributes**:
  - `std::string name`: Player's name.
  - `int money`: Player's current balance.
  - `std::vector<Slot*> ownedProperties`: List of properties owned by the player.

- **Functions**:
  - `Player(const std::string& name)`: Constructor to create a player.
  - `void pay(int amount)`: Deducts money from the player's balance.
  - `void receive(int amount)`: Adds money to the player's balance.
  - `void addProperty(Slot* property)`: Allows the player to purchase a property.

### Dice Class

- **Attributes**:
  - `int die1`, `int die2`: Represents two dice.

- **Functions**:
  - `Dice()`: Constructor to initialize the dice.
  - `void roll()`: Simulates rolling the dice.
  - `int getTotal() const`: Returns the total value of the two dice.
  - `bool isDouble() const`: Checks if the rolled dice are doubles.

### Game Class

- **Attributes**:
  - `Board board`: Manages the game board.
  - `std::vector<Player> players`: List of players in the game.
  - `bool gameOver`: Indicates if the game has ended.

- **Functions**:
  - `Game()`: Constructor to initialize a new game.
  - `void playTurn()`: Manages the flow of a player's turn.
  - `void checkBankruptcy(Player& player)`: Checks if a player is bankrupt.

## GUI Class

- **Attributes**:
  - `sf::RenderWindow window`: Main window for the game interface.
  - `Game game`: Manages the game state visually.

- **Functions**:
  - `void run()`: Main loop to run the GUI.
  - `void render()`: Renders the game state on the screen.
  - `void handleEvents()`: Processes user input.

## Contributing

If you'd like to contribute to this project, please fork the repository and submit a pull request. You can also open issues to report bugs or request features.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
```