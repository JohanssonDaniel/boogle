// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// TODO: implement the members you declared in Boggle.h

void Boggle::createGrid(){
    boggleGrid.nRows = BOARD_SIZE;
    boggleGrid.nCols = BOARD_SIZE;

    boggleGrid.resize(boggleGrid.numRows(),boggleGrid.numCols());

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            int n = randomInteger(0,CUBE_SIDES - 1);
            boggleGrid.set(i, j, CUBES[i+j][n]);
        }
    }

    shuffle(boggleGrid);

}

Grid<char> Boggle::fetchGrid(){
    return boggleGrid;
}

int Boggle::fetchNUM_CUBES(){
    return NUM_CUBES;
}