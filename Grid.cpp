#include "Grid.h"
#include "BuggeredFormatException.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

/* The default constructor. Prompts user for dimensions of their grid and initial poulation density, then builds a grid to specs.
*/
Grid::Grid()
{

  inFileName = "\0";
  string tempIn;
  cout << endl << "Enter number of rows in your randomly generated table: ";
  getline(cin, tempIn);
  while (true) {
    try {
      rows = stoi(tempIn);
      if (rows < 1) {
        throw invalid_argument("Integer not positive.");
      }
      break;
    } catch (invalid_argument &ia) {
      cout << "Not a valid positive integer." << endl;
      cout << "Enter number of rows: ";
      getline(cin, tempIn);
    }
  }
  cout << "Enter number of columns in your randomly generated table: ";
  getline(cin, tempIn);
  while (true) {
    try {
      columns = stoi(tempIn);
      if (columns < 1) {
        throw invalid_argument("Integer not positive.");
      }
      break;
    } catch (invalid_argument &ia) {
      cout << "Not a valid positive integer." << endl;
      cout << "Enter number of columns: ";
      getline(cin, tempIn);
    }
  }
  cout << "Enter a decimal greater than 0 and less than 1, representing initial population density: ";
  getline(cin, tempIn);
  while (true) {
    try {
      popDensity = stof(tempIn);
      if (popDensity <= 0 || popDensity > 1) {
        throw invalid_argument("Float out of bounds (0 < float <= 1).");
      }
      break;
    } catch (invalid_argument &ia) {
      cout << "Not a valid decimal." << endl;
      cout << "Enter a decimal greater than 0 and less than 1, representing initial population density: ";
      getline(cin, tempIn);
    }
  }

  srand(time(0));
  currentArray = new char*[rows];  // Dynamic multidimensional array
  for (int i = 0; i < rows; ++i) {
    currentArray[i] = new char[columns];
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (((double)rand() / (double)RAND_MAX) < popDensity) {
        currentArray[i][j] = 'X';
      } else {
        currentArray[i][j] = '-';
      }
    }
  }

  pastArray = new char*[rows];  // Dynamic multidimensional array
  for (int i = 0; i < rows; ++i) {
    pastArray[i] = new char[columns];
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      pastArray[i][j] = 'q';
    }
  }

  nextArray = new char*[rows];  // Dynamic multidimensional array
  for (int i = 0; i < rows; ++i) {
    nextArray[i] = new char[columns];
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      nextArray[i][j] = 'q';
    }
  }


}

/* The overloaded constructor. Reads in a text file to build the starting grid.
* Parameter string ifn: The name of the file to be read in.
*/
Grid::Grid(const string &ifn)
{

  popDensity = NAN;
  inFileName = ifn;
  ifstream file;
  file.open(inFileName);
  while (!file) {
    cout << inFileName << " is not a valid file name. Please enter a valid file name: ";
    getline(cin, inFileName);
    file.open(inFileName);
  }
  string tempIn;
  try {
    getline(file, tempIn);
    rows = stoi(tempIn);
    getline(file, tempIn);
    columns = stoi(tempIn);
    if (rows < 1 || columns < 1) {
      throw BuggeredFormatException("Text file improperly formatted; row and column numbers must be positive.");
    }
  } catch (invalid_argument &ia) {
    cout << "There was a problem reading your file. Please make sure your file is formatted as follows and try again." << endl << endl;
    cout << "5" << endl;
    cout << "7" << endl;
    cout << "--XX-XX" << endl;
    cout << "-X--X--" << endl;
    cout << "-----XX" << endl;
    cout << "X-X-X--" << endl;
    cout << "-----XX" << endl << endl;
    cout << "Where the first line is the number of rows, the second line is the number of columns, and the subsequent lines represent the rows of the grid (dash (-) for an empty cell, X for an occupied cell)." << endl;
    file.close();
    throw BuggeredFormatException("Text file improperly formatted.");
  }

  currentArray = new char*[rows];  // Dynamic multidimensional array
  for (int i = 0; i < rows; ++i) {
    currentArray[i] = new char[columns];
  }
  for (int i = 0; i < rows; ++i) {
    getline(file, tempIn);
    for (int j = 0; j < columns; ++j) {
      if (tempIn[j] == '-') {
        currentArray[i][j] = '-';
      } else if (tempIn[j] == 'X') {
        currentArray[i][j] = 'X';
      } else {
        throw BuggeredFormatException("Text file improperly formatted; line 3 and on must consist only of - or X.");
      }
    }
  }
  file.close();

  pastArray = new char*[rows];  // Dynamic multidimensional array
  for (int i = 0; i < rows; ++i) {
    pastArray[i] = new char[columns];
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      pastArray[i][j] = 'q';
    }
  }

  nextArray = new char*[rows];  // Dynamic multidimensional array
  for (int i = 0; i < rows; ++i) {
    nextArray[i] = new char[columns];
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      nextArray[i][j] = 'q';
    }
  }



}

/* The destructor. Empty so that derived classes don't cause a double free error.
*/
Grid::~Grid() {}

/* A function that constructs the next table based on current cell configuration, evaluates if the simulation is in a simple holding pattern, and if not, copies the current table to the past table and sets the newly assembled table to current table.
* Returns true if the Grid should continue advancing (in other words, if it isn't stable). Returns false if table is at rest.
*/
bool Grid::NextTable()
{

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      nextArray[i][j] = NextCell(i, j);
    }
  }

  if (IsStable()) {
    return false;
  } else {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        pastArray[i][j] = currentArray[i][j];
      }
    }
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        currentArray[i][j] = nextArray[i][j];
      }
    }
    return true;
  }

}

/* Evaluates grid stability, accounting for very basic oscillation.
* Returns false if the grid is unstable, and returns true if the grid is stable.
*/
bool Grid::IsStable()
{

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (pastArray[i][j] == nextArray[i][j]) {
        continue;
      } else if (currentArray[i][j] != nextArray[i][j]) {
        return false;
      }
    }
  }
  return true;

}

/* Converts the grid to a string.
* Returns a string representing the grid.
*/
string Grid::ToString()
{

  string temp = "";
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      temp += currentArray[i][j];
    }
    temp += '\n';
  }
  return temp;

}

/* Evaluates the next cell based on its number of neighbors. (Implemented in derived classes)
* Returns a char, X for a full cell, - for an empty cell.
*/
char Grid::NextCell(int r, int c){}
