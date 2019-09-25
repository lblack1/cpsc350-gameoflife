#include "Grid.h"
#include "MirrorGrid.h"
#include <iostream>

using namespace std;

/* Default constructor. Calls base class constructor.
*/
MirrorGrid::MirrorGrid() : Grid() {}

/* Overloaded constructor. Calls base class constructor.
* Parameter string ifn: the name of the file to read in as a starting grid.
*/
MirrorGrid::MirrorGrid(const string &ifn) : Grid(ifn) {}

/* The destructor. Deallocates all pointer array members.
*/
MirrorGrid::~MirrorGrid() {
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
char MirrorGrid::NextCell(int r, int c) {

  int neighbors = 0;
  int mirrorRPlus;
  int mirrorRMinus;
  int mirrorCPlus;
  int mirrorCMinus;

  if (r+1 == rows) {
    mirrorRPlus = r;
  } else {
    mirrorRPlus = r+1;
  }
  if (r-1 == -1) {
    mirrorRMinus = r;
  } else {
    mirrorRMinus = r-1;
  }
  if (c+1 == columns) {
    mirrorCPlus = c;
  } else {
    mirrorCPlus = c+1;
  }
  if (c-1 == columns) {
    mirrorCMinus = c;
  } else {
    mirrorCMinus = c-1;
  }

  if (currentArray[r][mirrorCPlus] == 'X') {
    neighbors++;
  }
  if (currentArray[mirrorRMinus][mirrorCPlus] == 'X') {
    neighbors++;
  }
  if (currentArray[mirrorRMinus][c] == 'X') {
    neighbors++;
  }
  if (currentArray[mirrorRMinus][mirrorCMinus] == 'X') {
    neighbors++;
  }
  if (currentArray[r][mirrorCMinus] == 'X') {
    neighbors++;
  }
  if (currentArray[mirrorRPlus][mirrorCMinus] == 'X') {
    neighbors++;
  }
  if (currentArray[mirrorRPlus][c] == 'X') {
    neighbors++;
  }
  if (currentArray[mirrorRPlus][mirrorCPlus] == 'X') {
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
