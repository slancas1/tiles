// Sophie Lancaster and Brianna Hoelting
// December 8, 2016
// Final Project (final.cpp)
// CSE 20311

// pound includes all necessary libraries
#include <ctime>
#include <vector>
#include <iostream>
#include <unistd.h>
using namespace std;
#include "tiles.h"
#include "gfxnew.h"

int main() {

  // declares and initializes variables
  int wd = 480, ht = 720;
  Tiles t(wd, ht); // creates the tiles object

  t.drawBoard(); // draws the tile board
  t.playGame(); // calls the playGame tile function

return 0;
}
