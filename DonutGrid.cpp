#include "Grid.h"
#include "DonutGrid.h"
#include <iostream>

using namespace std;

/* Default constructor. Calls base class constructor.
*/
DonutGrid::DonutGrid() : Grid() {}

/* Overloaded constructor. Calls base class constructor.
* Parameter string ifn: the name of the file to read in as a starting grid.
*/
DonutGrid::DonutGrid(const string &ifn) : Grid(ifn) {}

/* The destructor. Deallocates all pointer array members.
*/
DonutGrid::~DonutGrid() {
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
char DonutGrid::NextCell(int r, int c) {

  int neighbors = 0;
  int nonSegFaultR;
  int nonSegFaultC;
  if (r-1 == -1) {
    nonSegFaultR = rows-1;
  } else {
    nonSegFaultR = r-1;
  }
  if (c-1 == -1) {
    nonSegFaultC = columns-1;
  } else {
    nonSegFaultC = c-1;
  }

  if (currentArray[r][(c+1)%columns] == 'X') {
    neighbors++;
  }
  if (currentArray[(r+1)%rows][c] == 'X') {
    neighbors++;
  }
  if (currentArray[(r+1)%rows][(c+1)%columns] == 'X') {
    neighbors++;
  }
  if (currentArray[(r+1)%rows][nonSegFaultC] == 'X') {
    neighbors++;
  }
  if (currentArray[r][nonSegFaultC] == 'X') {
    neighbors++;
  }
  if (currentArray[nonSegFaultR][nonSegFaultC] == 'X') {
    neighbors++;
  }
  if (currentArray[nonSegFaultR][(c+1)%columns] == 'X') {
    neighbors++;
  }
  if (currentArray[nonSegFaultR][c] == 'X') {
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
