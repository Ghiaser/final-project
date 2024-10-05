CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = monopoly
OBJS = main.o SpecialSlot.o Game.o Board.o Player.o Dice.o Slot.o Street.o Train.o GUI.o
SOURCES = main.cpp SpecialSlot.cpp Game.cpp Board.cpp Player.cpp Dice.cpp Slot.cpp Street.cpp Train.cpp GUI.cpp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

gui:
	g++ -c GUI.cpp
	g++ GUI.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	
clean:
	rm -f $(TARGET) $(OBJS)
