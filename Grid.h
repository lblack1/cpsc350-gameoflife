#ifndef GRID
#define GRID

#include <iostream>
#include <fstream>

using namespace std;

/* A class that builds a grid per the rules of Conway's Game of Life. Computes next tables, evaluates stability or period 2 holding patterns (blinkers) and converts the grid to a string.
*/
class Grid
{

  public:
    Grid();
    Grid(const string &ifn);
    ~Grid();

    bool NextTable();
    bool IsStable();
    string ToString();
    virtual char NextCell(int r, int c);


  protected:
    string inFileName;
    int rows;
    int columns;
    float popDensity;
    char** pastArray;
    char** currentArray;
    char** nextArray;

};

#endif
