#include "Grid.h"
#include "ClassicGrid.h"
#include <iostream>

using namespace std;

/* Default constructor. Calls base class constructor.
*/
ClassicGrid::ClassicGrid() : Grid() {}

/* Overloaded constructor. Calls base class constructor.
* Parameter string ifn: the name of the file to read in as a starting grid.
*/
ClassicGrid::ClassicGrid(const string &ifn) : Grid(ifn) {}

/* The destructor. Deallocates all pointer array members.
*/
ClassicGrid::~ClassicGrid() {
  for (int i = 0; i < rows; ++i) {
    delete[] pastArray[i];
    delete[] currentArray[i];
    delete[] nextArray[i];
  }
  delete[] pastArray;
  delete[] currentArray;
  delete[] nextArray;
}

/* A method that evaluates the state of a given cell in the next generation based on its number of neighbors (as per classic grid rules).
* Parameter int r: the row index of the cell in question
* Parameter int c: the column index of the cell in question
* Returns a char, X for a full cell, - for an empty cell.
*/
char ClassicGrid::NextCell(int r, int c) {

  int neighbors = 0;

  if (c+1 != columns && currentArray[r][c+1] == 'X') {
    neighbors++;
  }
  if (c+1 != columns && r != 0 && currentArray[r-1][c+1] == 'X') {
    neighbors++;
  }
  if (r != 0 && currentArray[r-1][c] == 'X') {
    neighbors++;
  }
  if (r != 0 && c != 0 && currentArray[r-1][c-1] == 'X') {
    neighbors++;
  }
  if (c != 0 && currentArray[r][c-1] == 'X') {
    neighbors++;
  }
  if (r+1 != rows && c != 0 && currentArray[r+1][c-1] == 'X') {
    neighbors++;
  }
  if (r+1 != rows && currentArray[r+1][c] == 'X') {
    neighbors++;
  }
  if (r+1 != rows && c+1 != columns && currentArray[r+1][c+1] == 'X') {
    neighbors++;
  }

  if (neighbors < 2) {
    return '-';
  } else if (neighbors == 2) {
    return currentArray[r][c];
  } else if (neighbors == 3) {
    return 'X';
  } else {
    return '-';
  }

}
