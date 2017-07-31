// Sophie Lancaster and Brianna Hoelting
// December 8, 2016
// Final Project (tiles.h)
// CSE 20311

  // tiles interface

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "gfxnew.h"
using namespace std;

class Tiles {
public:
  Tiles(); // generic constructor
  Tiles(int, int); // function that initializes board
  ~Tiles(); // destructor

  void updateBoard(); // function that updates the board over time
  void towardsEndUpdate(); // function that updates the board towards the end of the game
  void drawBoard(); // function that draws and displays the board
  int ifPressed(int&, int&); // function that determines if anything was pressed and if so what location was pressed
  void displayMenu(); // function that displays the menu and sets the conditions for the game
  void displayResults(int, char*); // function that displays the final results of the game
  void playGame(); // function that calls all other functions to play the game

private:
  vector <vector<int>> board;
  int numTiles; // variable that represents the number of tiles to be placed
  int boardSize; // sets the size of the board
  int wd, ht; // dimensions of the board
};
