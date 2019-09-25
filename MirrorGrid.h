#ifndef MIRROR_GRID
#define MIRROR_GRID

#include "Grid.h"
#include <iostream>

using namespace std;

/* A class derived from Grid, which interprets grids by mirror grid tables.
*/
class MirrorGrid : public Grid
{

  public:
    MirrorGrid();
    MirrorGrid(const string &ifn);
    ~MirrorGrid();

    virtual char NextCell(int r, int c);

};

#endif
