# cpsc350-gameoflife
J.H. Conway's game of life in C++

Lloyd Black
2295968
CPSC350, Section 2
Rene German

A program for running a Game of Life with one of three types of grids (classic, donut, and mirror) and outputting the results in one of three ways (enter-delineated, brief pause-delineated, and write to text file).

1. Source Files - main.cpp, Driver.h, Driver.cpp, Grid.h, Grid.cpp, ClassicGrid.h, ClassicGrid.cpp, DonutGrid.h, DonutGrid.cpp, MirrorGrid.h, MirrorGrid.cpp, BuggeredFormatException.h, BuggeredFormatException.cpp

2. Issues - Unable to detect oscillations that aren't blinkers.

3. Resources - cplusplus.com/reference, stackoverflow, tutorialspoint, wikipedia on Game of Life, ibm.com, and Data Structures and Algorithms in C (by Goodrich, Tamassia, and Mount).

4. Description of Program - Prompts the user for how to build the initial grid, what game mode to run in, and what output mode to use (then asks for name of the output file if applicable). Proceeds to run a game of life according to the settings until it consists only of still lives or blinker oscillators. Continues to run infinitely if there exists an oscillator of period greater than two.

5. To run, execute  $ make
