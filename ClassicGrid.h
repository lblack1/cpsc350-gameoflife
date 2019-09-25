#ifndef CLASSIC_GRID
#define CLASSIC_GRID

#include "Grid.h"
#include <iostream>

using namespace std;

/* A class derived from Grid, which interprets grids by classic grid tables.
*/
class ClassicGrid : public Grid
{

  public:
    ClassicGrid();
    ClassicGrid(const string &ifn);
    ~ClassicGrid();

    virtual char NextCell(int r, int c);

};

#endif
