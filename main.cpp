#include "Driver.h"
#include "Grid.h"
#include "ClassicGrid.h"
#include "DonutGrid.h"
#include "MirrorGrid.h"
#include "BuggeredFormatException.h"
#include <cstdlib>
#include <iostream>

using namespace std;

/* Prompts user for a few guidelines before building a Game of Life as specified.
*/
int main(int argc, char** argv)
{

  string temp;
  string inFileName;
  char gameMode;
  char outputMode;
  string outputFile;

  cout << endl << "  -x-X-x- Lloyd's Conway's Game of Life -x-X-x-" << endl;

  cout << endl << "Would you like to import a pre-existing grid from a text file? Yes (y), or No (n): ";
  getline(cin, temp);
  if (tolower(temp[0]) == 'y') {
    cout << "Please enter name of text file to import: ";
    getline(cin, inFileName);
  } else {
    inFileName = "\0";
  }

  cout << endl << "Which game mode/grid type would you like to run? Classic (c), Donut (d), or Mirrored (m): ";
  getline(cin, temp);
  while (tolower(temp[0]) != 'c' && tolower(temp[0]) != 'd' && tolower(temp[0]) != 'm') {
    cout << "I'm sorry, that's not a valid dame mode/grid type. Please try again." << endl;
    cout << "Which game mode/grid type would you like to run? Classic (c), Donut (d), or Mirrored (m): ";
    getline(cin, temp);
  }
  gameMode = tolower(temp[0]);

  cout << endl << "How would you like the game to be outputted?\nCommand line with advance generation on Enter (e), command line with brief Pauses between generations (p), or results written to a File (f): ";
  getline(cin, temp);
  while (tolower(temp[0]) != 'e' && tolower(temp[0]) != 'p' && tolower(temp[0]) != 'f') {
    cout << "I'm sorry, that's not a valid output format. Please try again." << endl;
    cout << "Command line with advance generation on Enter (e), command line with brief Pauses between generations (p), or results written to a File (f): ";
    getline(cin, temp);
  }
  outputMode = tolower(temp[0]);
  if (outputMode == 'f') {
    cout << "Enter name of file to output game to: ";
    getline(cin, outputFile);
  } else {
    outputFile = "\0";
  }

  try {
    Driver gol(inFileName, gameMode, outputMode, outputFile);
    gol.RunGame();
  } catch (BuggeredFormatException e) {
    cout << e.GetError() << endl << endl;
  }

}
