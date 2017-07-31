// Sophie Lancaster and Brianna Hoelting
// December 8, 2016
// Final Project (tiles.cpp)
// CSE 20311

#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;
#include "tiles.h" // pound includes the tiles class
#include "gfxnew.h" // pound includes the gfx class

Tiles::Tiles()
{} // default constructor

// function that initializes the board
Tiles::Tiles(int width, int height)
{
  // sets the private data of the class to the width and height that were passed in
  wd = width;
  ht = height;

  // call menu function to initialize the game
  displayMenu();

  // nested for loops that initialize the board to a board of zeros
  vector <int> inner ((boardSize), 0);
    for (int j = 0; j < boardSize; j++) {
      board.push_back(inner);
    }

  // for loop that adds exactly one 1 to each row on the board (corresponds to black tiles)
  for (int i = 0; i < boardSize - 1; i++) {
    int c = rand() % (boardSize) + 0; // gets random column
    board[i][c] = 1; // sets one tile to 1 (black)
  }
}

Tiles::~Tiles()
{} // default destructor

// function that updates the board over time
void Tiles::updateBoard()
{
  // nested for loops that move each row of the board down
  for (int k =  boardSize - 2; k >= 0; k--) {
    for (int j = 0; j < boardSize; j++) {
      board[k + 1][j] = board[k][j]; // moves rows down
    }
  }
  // for loop that creates a new row with a random black tile
  for (int j = 0; j < boardSize; j++) {
    board[0][j] = 0; // initializes row to white
  }
  int c = rand() % (boardSize) + 0; // gets random column
  board[0][c] = 1; // sets one tile to 1 (black)
}

// function that updates the board towards the end of the game
void Tiles::towardsEndUpdate()
{
  // nested for loops that move each row of the board down
  for (int k =  boardSize - 2; k >= 0; k--) {
    for (int j = 0; j < boardSize; j++) {
      board[k + 1][j] = board[k][j]; // moves rows down
    }
  }
  // for loop that makes the new row green signifying the end of the game is approaching
  for (int j = 0; j < boardSize; j++) {
    board[0][j] = 3; // sets the spot in the array to 3 which corresponds to green for the end of the game
  }
}

// function that draws and displays the board
void Tiles::drawBoard()
{
  float width = wd/boardSize; // determines the width of each individual tile
  float length = ht/boardSize; // determines the length of each individual tile
  gfx_clear(); // clears the window

  // nested for loops that go through each element of the board
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      // if statement that draws a black square if there is a one in the array at that spot
      if (board[i][j] == 1) {
        gfx_color(0, 0, 0);
        gfx_fill_rectangle((j * width), (i * length), width, length);
      }
    }
  }

  // nested for loops that go through each element of the board
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      // if statement that draws a white square if there is a zero in the array at that spot
      if (board[i][j] == 0) {
        gfx_color(255, 255, 255);
        gfx_fill_rectangle((j * width), (i * length), width, length);
        gfx_color(0, 0, 0); // changes the color to black for the lines
        // draws the lines on the board
        gfx_line((j * width), (i * length), (j * width + width), (i * length));
        gfx_line((j * width + width), (i * length), (j * width + width), (i * length + length));
        gfx_line((j * width + width), (i * length + length), (j * width), (i * length + length));
        gfx_line((j * width), (i * length + length), (j * width), (i * length));
      }
    }
  }

  // nested for loops that go through each element of the board
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      // if statement that draws a green square if there is a two in the array at that spot
      if (board[i][j] == 2) {
        gfx_color(0, 255, 0);
        gfx_fill_rectangle((j * width), (i * length), width, length);
        gfx_color(0, 0, 0); // changes the color to black for the lines
        // draws the lines on the board
        gfx_line((j * width), (i * length), (j * width + width), (i * length));
        gfx_line((j * width + width), (i * length), (j * width + width), (i * length + length));
        gfx_line((j * width + width), (i * length + length), (j * width), (i * length + length));
        gfx_line((j * width), (i * length + length), (j * width), (i * length));
      }
    }
  }

  // nested for loops that go through each element of the board
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      // if statement that draws a green square AND NO LINES if there is a three in the array at that spot
      // used for the towardsEndUpdate function
      if (board[i][j] == 3) {
        gfx_color(0, 255, 0);
        gfx_fill_rectangle((j * width), (i * length), width, length);
      }
    }
  }
}

// function that determines if anything was pressed and if so what location was pressed
int Tiles::ifPressed(int &xc, int &yc)
{
  int n, xstart, xend, ytop, ybottom, boxwidth, boxheight, spot; // initializes the variables necessary to determine which box was clicked
  boxwidth = wd/boardSize; // calculates the width of the boxes
  boxheight = ht/boardSize; // calculates the height of the boxes

  // for loop that determines the boundaries for the box that was clicked
  for (int j = 0; j < boardSize; j++) {
    if (board[boardSize - 2][j] == 1) { // goes through the row and finds the black box
      spot = j;
      xstart = j*boxwidth; // left bound of box
      xend = (j + 1)*boxwidth; // right bound of box
      ytop = (boardSize - 2)*boxheight; // top bound of box
      ybottom = (boardSize - 1)*boxheight; // bottom bound of box
    }
  }

  // if statement that sets the corresponding spot in the array to a two if the box was black
  // this makes it so that the box can be turned to green now that it has been pressed
  if ((xc >= xstart) && (xc <= xend) && (yc >= ytop) && (yc <= ybottom)) {
    xc = 0;
    board[boardSize - 2][spot] = 2; // changes the spot in the array
    n = 1; // sets the integer to a one when the black box is pressed
  }
  // else if that makes it so that nothing happens if the person clicks above or below the desired row
  else if ((yc <= ytop) || (yc >= ybottom)) {
    n = 2; // sets the integer to a two when arbitrary boxes in the other rows are pressed
  }
  // else statement that that sets the int to three if a white box in the desired row is clicked on
  else {
    n = 3;
  }
  return n;
}

// function that displays the menu
void Tiles::displayMenu()
{
  // initializes the necessary variables
  bool loop = true; // declares and initializes the loop variable
  int etype; // signifies the result from gfx_event_waiting
  char c; // signifies the result from gfx_wait

  gfx_open(wd, ht, "Tiles"); // opens the game window
  gfx_clear();

  // creates a white rectangle to display the text in
  gfx_color(255, 255, 255);
  gfx_fill_rectangle(0, (ht/4), wd, (ht/2));

  // displays the instructions in black text
  gfx_color(0, 0, 0);
  gfx_text((wd/3 + 20), ((ht/4) + 20), "Piano Tiles Instructions");
  gfx_text(20, ((ht/4) + 80), "To play, you will first select your board size as 4x4, 5x5, or 6x6.");
  gfx_text(20, ((ht/4) + 105), "Then, you will choose the number of tiles you want to go through.");
  gfx_text(20, ((ht/4) + 130), "Wanna just relax? Play forever in relax mode.");
  gfx_text(20, ((ht/4) + 155), "The object is to only select the black tiles in the bottom row.");
  gfx_text(20, ((ht/4) + 180), "You lose the game if you select a white tile from the bottom row.");
  gfx_text(20, ((ht/4) + 205), "There is no penalty for accidently selecting another tile from another row.");
  gfx_text(20, ((ht/4) + 230), "You can quit the program by pressing 'q' at any time.");
  gfx_text((wd/3 + 20), ((ht*3/4) - 20), "Press 'c' to continue");

  // while loop that does move on to the next part of the program until the user clicks c which signifies continuing
  while (loop) {
    if(etype = gfx_event_waiting()) {
      if(etype == 1) {
        c = gfx_wait();
        if(c == 'c') {
          loop = false; // exits the loop once c is pressed
        }
      }
      else {gfx_wait();}
    }
  }

  loop = true; // resets the loop variable so that it can be used later

  // displays the board dimensions menu in black text
  gfx_clear();
  gfx_color(255, 255, 255);
  gfx_fill_rectangle(0, (ht/4), wd, (ht/2));
  gfx_color(0, 0, 0);
  gfx_text( (wd/3 + 3), ((ht/4) + 40), "Select a Tile Layout");
  gfx_text((wd/6 - 20), ((ht/4) + 90), "Click the number key corresponding to the desired board dimensions");
  gfx_text((wd/4 + 10), ((ht/4) + 165), "1");
  gfx_text((wd/4), ((ht/4) + 190), "4 x 4");
  gfx_text((wd/2) + 10, ((ht/4) + 165), "2");
  gfx_text((wd/2), ((ht/4) + 190), "5 x 5");
  gfx_text((3*wd/4) + 10, ((ht/4) + 165), "3");
  gfx_text((3*wd/4), ((ht/4) + 190), "6 x 6");

  // while loop that does move on to the next part of the program until the user clicks one of the number keys
  while (loop) {
    if(etype = gfx_event_waiting()) {
      if(etype == 1) {
        c = gfx_wait();
        // sets the boardsize to 4 if the user clicks 1
        if(c == '1') {
          boardSize = 4;
        }
        // sets the boardsize to 5 if the user clicks 2
        else if (c == '2') {
          boardSize = 5;
        }
        // sets the boardsize to 6 if the user clicks 3
        else if (c == '3') {
          boardSize = 6;
        }
        loop = false; // exits the loop once a button is pressed
      }
      else {gfx_wait();}
    }
  }

  loop = true; // resets the loop variable so that it can be used later

  // displays the number of tiles menu in black text
  gfx_clear();
  gfx_color(255, 255, 255);
  gfx_fill_rectangle(0, (ht/4), wd, (ht/2));
  gfx_color(0, 0, 0);
  gfx_text((wd/3 + 3), ((ht/4) + 40), "Select the Number of Tiles");
  gfx_text((wd/6 - 20), ((ht/4) + 90), "Click the number key corresponding to the desired number of tiles");
  gfx_text((wd/4 + 10), ((ht/4) + 165), "1");
  gfx_text((wd/4), ((ht/4) + 190), "25");
  gfx_text((wd/2 + 10), ((ht/4) + 165), "2");
  gfx_text((wd/2), ((ht/4) + 190), "50");
  gfx_text((3*wd/4) + 20, ((ht/4) + 165), "3");
  gfx_text((3*wd/4), ((ht/4) + 190), "Relax Mode");

  // while loop that does move on to the next part of the program until the user clicks one of the number keys
  while (loop) {
    if(etype = gfx_event_waiting()) {
      if(etype == 1) {
        c = gfx_wait();
        // sets the number of tiles to 25 if the user clicks 1
        if(c == '1') {
          numTiles = 25;
        }
        // sets the number of tiles to 50 if the user clicks 2
        else if (c == '2') {
          numTiles = 50;
        }
        // sets the number of tiles to a high number if the user clicks 3 (relax mode)
        else if (c == '3') {
          numTiles = 100;
        }
      loop = false; // exits the loop once a button is pressed
      }
      else {gfx_wait();}
    }
  }
}

// function that displays the final results of the game
void Tiles::displayResults(int result, char * countCstr)
{
  // if the result that is passed in is a 1 then the player lost the game and the following window is displayd
  if (result == 1) {
    gfx_clear_color(255, 0, 0); // the color of the screen is turned to red
    gfx_clear();
    gfx_color(255, 255, 255); // color is turned to white for text
    gfx_text((wd/3 + 3), ((ht/4) + 40), "You Missed!!");
    gfx_text((wd/6 + 50), ((ht/4) + 90), "You got:");
    gfx_text((wd/4 + 75), ((ht/4) + 90), countCstr); // displays the number of tiles that were clicked by passing in the converted count
    gfx_text((wd/4 + 100), ((ht/4) + 90), "Tiles");
    gfx_text((wd/3 + 20), ((ht*3/4) - 20), "Press 'q' to exit");
  }
  // if the result that is passed in is a 2 then the player won the game and the following window is displayd
  else if (result == 2) {
    gfx_clear_color(0, 255, 0); // the color of the screen is turned to green
    gfx_clear();
    gfx_color(0, 0, 0); // color is turned to black for text
    gfx_text((wd/3 + 3), ((ht/4) + 40), "You Won!!");
    // displays that the player got all 25 tiles if numTiles is 25
    if (numTiles == 25) {
      gfx_text((wd/6 + 50), ((ht/4) + 90), "You got all 25 tiles!");
    }
    // displays that the player got all 50 tiles if numTiles is 50
    if (numTiles == 50) {
      gfx_text((wd/6 + 50), ((ht/4) + 90), "You got all 50 tiles!");
    }
    gfx_text((wd/3 + 20), ((ht*3/4) - 20), "Press 'q' to exit");
  }
}

// function that calls all other functions to play the game
void Tiles::playGame()
{
  int xc, yc, count;
  char Count[] = {"0"}; // creates a c string that will be used to display the number of tiles that have been clicked in relax mode
  int etype; // signifies the result from gfx_event_waiting
  bool loop = true; // declares and initializes the loop variable
  char c; // signifies the result from gfx_wait

  while(loop) {
    // if statement that receives the feedback from the user and executes accordingly
    if(etype = gfx_event_waiting()) {
      // if a key is pressed etype becomes 1
      if (etype == 1) {
        c = gfx_wait();
        if (c == 'q') loop = false; // if the q button is clicked the while loop quits and program ends
      }
      // if a mouse click occurs then etype becomes 3
      else if (etype == 3) {
        gfx_wait();
        // gets the x and y of the mouse click
        xc = gfx_xpos();
        yc = gfx_ypos();

        int pressLoc;
        pressLoc = ifPressed(xc, yc);

        // if statement that executes if the isPressed function returns a one after passing in the coordinates of the mouse click
        if(pressLoc == 1) {
          // if statement that executes if its approaching the end of the game
          if(count >= (numTiles - (boardSize - 1))) {
            towardsEndUpdate(); // calls the towardsEndUpdate function
          }
          else {
            updateBoard(); // regularly updates the board otherwise
          }

          drawBoard(); // draws the board
          count++; // iterates the counter to know how many times the mouse clicked / how many boxes were pressed
          Count[0] = Count[0] + 1; // creates the char value of the counter

          // displays the results of the game if all the tiles were clicked or the player won
          if(count == numTiles) {
            displayResults(2, Count);
          }
        }
        // if statement that executes if the isPressed function returns a three after passing in the coordinates of the mouse click
        else if(pressLoc == 3) {
          displayResults(1, Count); // displays the results of the game taking in a 1 meaning the player lost
        }
      }
      else {gfx_wait();}
    }
  }
}
