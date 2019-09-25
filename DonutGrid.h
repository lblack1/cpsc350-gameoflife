#ifndef DONUT_GRID
#define DONUT_GRID

#include "Grid.h"
#include <iostream>

using namespace std;

/* A class derived from Grid, which interprets grids by donut grid tables.
*/
class DonutGrid : public Grid
{

  public:
    DonutGrid();
    DonutGrid(const string &ifn);
    ~DonutGrid();

    virtual char NextCell(int r, int c);

};

#endif
