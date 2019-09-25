#ifndef DRIVER
#define DRIVER

#include "Grid.h"
#include "ClassicGrid.h"
#include "DonutGrid.h"
#include "MirrorGrid.h"
#include "BuggeredFormatException.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

/* A class containing the basic logic for running a Game of Life, such as constructing a grid following one of three neighbor rules, advancing through generations, and outputting results.
*/
class Driver
{

  public:
    Driver();
    Driver(string ifn, char gm, char om, string of);
    ~Driver();

    void RunGame();
    void Output();

  private:
    string inputFile;
    int genNumber;
    char gameMode;
    char outputMode;
    ofstream outFile;
    Grid* grid;

};

#endif
