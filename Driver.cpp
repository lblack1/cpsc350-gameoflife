#include "Driver.h"
#include "Grid.h"
#include "ClassicGrid.h"
#include "DonutGrid.h"
#include "MirrorGrid.h"
#include "BuggeredFormatException.h"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

/* Default constructor. Exists purely for the sake of convention.
*/
Driver::Driver()
{
  inputFile = "\0";
  genNumber = 0;
  gameMode = '\0';
  outputMode = '\0';
}

/* Overloaded constructor. Reads in a few parameters and sets up a game of life accordingly.
* Parameter string ifn: the name of the text file to read in, if applicable.
* Parameter char gm: the game mode to run. 'c' for classic, 'd' for donut, or 'm' for mirror.
* Parameter char om: the output mode to run. 'e' for enter delineated, 'p' for brief pauses between generations, or 'f' for write to file.
* Parameter string of: the name of the file to output results to, if applicable.
*/
Driver::Driver(string ifn, char gm, char om, string of)
{
  inputFile = ifn; // for InFileName
  genNumber = 0;
  gameMode = gm;
  outputMode = om;
  if (ifn == "\0") {
    if (gm == 'c') {
      grid = new ClassicGrid();
    } else if (gm == 'd') {
      grid = new DonutGrid();
    } else if (gm == 'm') {
      grid = new MirrorGrid();
    }
  } else {
    if (gm == 'c') {
      grid = new ClassicGrid(ifn);
    } else if (gm == 'd') {
      grid = new DonutGrid(ifn);
    } else if (gm == 'm') {
      grid = new MirrorGrid(ifn);
    }
  }
  if (of != "\0") {
    outFile.open(of, ios::app);
  }
}

/* The destructor. Closes the file being written to.
*/
Driver::~Driver() {
  outFile.close();
}

/* Advances the grid through generations until it stablizes.
*/
void Driver::RunGame() {
  do {
    Output();
    genNumber++;
  } while (grid->NextTable());
}

/* Outputs the generation number and corresponding table in the selected manner.
*/
void Driver::Output() {
  if (outputMode == 'e') {
    cout << genNumber << endl;
    cout << grid->ToString() << endl;
    cin.ignore();
  } else if (outputMode == 'p') {
    cout << genNumber << endl;
    cout << grid->ToString() << endl;
    this_thread::sleep_for(chrono::seconds(1));
  } else if (outputMode == 'f') {
    outFile << genNumber << endl;
    outFile << grid->ToString() << endl;
  }
}
