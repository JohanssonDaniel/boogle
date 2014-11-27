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
bool findNeighbours(string tempWord, grid ){
    if(tempWord.size() == 0){
        return true;
    }

    vector<int> xValues {x - 1, x + 1, x, x - 1, x + 1, x, x - 1, x + 1};
    vector<int> yValues {y - 1, y - 1, y - 1, y + 1, y + 1, y + 1, y, y};

    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            if(){
                return findNeighbours();
            }
        }
    }
}
bool Boggle::findWordInGrid(string tempWord) {


    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            if(tempWord[0] == boggleGrid.get(row,col)){
                Grid tempGrid = boggleGrid;
                tempGrid.set(row,col,"-");
                findNeighbours(tempWord.substr(1,tempWord.size()-1), tempGrid)
            }
        }
    }
}


void Boggle::createGrid(string gridString){
    int gridIndex = 0;
    boggleGrid.nRows = BOARD_SIZE;
    boggleGrid.nCols = BOARD_SIZE;

    boggleGrid.resize(boggleGrid.numRows(),boggleGrid.numCols());

    if(gridString.size() == 0){
        for(int i = 0; i < BOARD_SIZE; i++){
            for(int j = 0; j < BOARD_SIZE; j++){
                int n = randomInteger(0,CUBE_SIDES - 1);
                boggleGrid.set(i, j, CUBES[gridIndex][n]);
                ++gridIndex;
            }
        }
        shuffle(boggleGrid);
    }
    else{
        for(int i = 0; i < BOARD_SIZE; i++){
            for(int j = 0; j < BOARD_SIZE; j++){
                boggleGrid.set(i, j, gridString[gridIndex]);
                ++gridIndex;
            }
        }
    }
}

Grid<char> Boggle::fetchGrid(){
    return boggleGrid;
}

int Boggle::fetchNUM_CUBES(){
    return NUM_CUBES;
}
