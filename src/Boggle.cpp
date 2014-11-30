/*
 * Class representing the boogle grid, and the functions that is used to find words
 * in the grid.
 * danjo732, piehe154
 **/

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include <set>

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
                                          "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
                                          "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
                                          "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
                                          "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
                                 };
/**
 * @brief Boggle::findNeighbours checks to see if the word can be found by traversing the neighbours recursively
 * @param row marked letter column
 * @param col marked letter row
 * @param tempWord word to be found
 * @param tempGrid grid which gets marked if a letter in the word is found
 * @return true/false
 */
bool Boggle::findNeighbours(int row, int col, string tempWord, Grid<char> tempGrid){
    //If the word is empty it is in the grid
    if(tempWord.size() == 0){
        return true;
    }
    else{
        int y = row;
        int x = col;
        //Coords for the neighbours in the grid
        vector<int> yValues {y - 1, y - 1, y - 1, y + 1, y + 1, y + 1, y, y};
        vector<int> xValues {x - 1, x + 1, x, x - 1, x + 1, x, x - 1, x + 1};

        int noNeighbours = xValues.size();

        for(int i = 0; i < noNeighbours; i++){
            int tempRow = yValues[i];
            int tempCol = xValues[i];
            //If the neighbour is inbound and it is the same as the first letter in tempWord
            if(tempGrid.inBounds(tempRow,tempCol) && tempGrid.get(tempRow,tempCol) == tempWord[0]){
                //Save and mark the letter in the grid
                char tempLetter = tempGrid.get(tempRow,tempCol);
                tempGrid.set(tempRow,tempCol,'-');
                //Call the function with the rest of the word without the first letter
                if(findNeighbours(tempRow, tempCol, tempWord.substr(1,tempWord.size()-1), tempGrid)){
                    return true;
                }else{
                    //If the word isn't found, reset the mark to be able to traverse the neighbour again
                    tempGrid.set(tempRow,tempCol,tempLetter);
                }
            }
        }
        return false;
    }
}
/**
 * @brief Boggle::findWordInGrid checks to se if tempWord can be found in the grid
 * @param tempWord, word to be found in the grid
 * @return true/false
 */
bool Boggle::findWordInGrid(string tempWord) {
    //Loops through the grid
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            //checks to see if the first letter of tempWord matches a letter in the grid
            if(tempWord[0] == boggleGrid.get(row,col)){
                //Creates a copy of the grid and sets the choosen coords to '-' to mark it
                Grid<char> tempGrid = boggleGrid;
                tempGrid.set(row,col,'-');
                if (findNeighbours(row, col, tempWord.substr(1,tempWord.size()-1), tempGrid)){
                    return true;
                }
            }
        }
    }
    return false;
}
/**
 * @brief Boggle::findComputerNeighbours finds the remaining words by checking the
 * neigbours to the letters and adding each word that exists in the lexicon
 * Each recursive call a neighbour letter is added to the currentWord to be checked
 * @param row column for the current letter
 * @param col row for the current letter
 * @param currentWord string that is built up by neighbours
 * @param tempGrid grid that is marked when a neighbour is choosen
 * @param lex lexcon
 */
void Boggle::findComputerNeighbours(int row, int col, string currentWord, Grid<char> tempGrid, Lexicon lex){

    if(currentWord.size() >= 4){
        //Basecase: If the words exist in the lexicon but not in playerWords, add it to the computer's list
        if(lex.contains(currentWord) && !(playerWords.find(currentWord) != playerWords.end())){
            computerWords.insert(currentWord);
        }
    }

    int y = row;
    int x = col;
    vector<int> xValues {x - 1, x + 1, x,     x - 1, x + 1, x,     x - 1, x + 1};
    vector<int> yValues {y - 1, y - 1, y - 1, y + 1, y + 1, y + 1, y,     y    };

    int noNeighbours = xValues.size();

    for(int i = 0; i < noNeighbours; i++){
        int tempRow = yValues[i];
        int tempCol = xValues[i];
        //If the word is inbound and not already marked
        if(tempGrid.inBounds(tempRow,xValues[i]) && tempGrid.get(tempRow,tempCol) != '-'){
            //Save the letter from the grid and build a new word with it
            char tempLetter = tempGrid.get(tempRow,tempCol);
            string tempWord = currentWord + tempLetter;
            //If the lexicon contains the prefix
            if(lex.containsPrefix(tempWord)){
                //mark the letter in the grid and call on the function again with the new word
                tempGrid.set(tempRow,tempCol,'-');
                findComputerNeighbours(tempRow, tempCol, tempWord, tempGrid, lex);
            }
            tempGrid.set(tempRow,tempCol, tempLetter);
        }
    }
}
/**
 * @brief Boggle::computerFind finds the remaining words in the grid by marking each letter in the grid
 * and calling findComputerNeighbours() for each letter
 */
void Boggle::computerFind(){
    Lexicon lex(DICTIONARY_FILE);

    for(int row = 0; row < BOARD_SIZE; ++row){
        for(int col = 0; col < BOARD_SIZE; ++col){
            Grid<char> tempGrid = boggleGrid;
            char tempLetter = tempGrid.get(row,col);
            string tempLetterString = string(1,tempLetter);
            tempGrid.set(row,col,'-');
            findComputerNeighbours(row, col, tempLetterString, tempGrid, lex);
            tempGrid.set(row,col,tempLetter);
        }
    }
}

/**
 * @brief Boggle::createGrid creates a random grid or a grid specfied by the player
 * @param gridString string which represents the order of the cubes, if empty create random grid
 */
void Boggle::createGrid(string gridString){
    int gridIndex = 0;
    boggleGrid.nRows = BOARD_SIZE;
    boggleGrid.nCols = BOARD_SIZE;

    boggleGrid.resize(boggleGrid.numRows(),boggleGrid.numCols());

    if(gridString.size() == 0){
        for(int i = 0; i < BOARD_SIZE; ++i){
            for(int j = 0; j < BOARD_SIZE; ++j){
                //Choose the side of the cube randomly
                int n = randomInteger(0,CUBE_SIDES - 1);
                boggleGrid.set(i, j, CUBES[gridIndex][n]);
                ++gridIndex;
            }
        }
        //Shuffle the cubes around in the grid
        shuffle(boggleGrid);
    }
    else{
        for(int i = 0; i < BOARD_SIZE; ++i){
            for(int j = 0; j < BOARD_SIZE; ++j){
                //Set the cubes to be the same as the string
                boggleGrid.set(i, j, gridString[gridIndex]);
                ++gridIndex;
            }
        }
    }
}

Grid<char> Boggle::getGrid(){
    return boggleGrid;
}

int Boggle::getNUM_CUBES(){
    return NUM_CUBES;
}

set<string> Boggle::getPlayerWords(){
    return playerWords;
}
void Boggle::insertplayerWord(string playerWord){
    playerWords.insert(playerWord);
}
int Boggle::getPlayerScore(){
    return playerScore;
}
/**
 * @brief Boggle::updateScore updates the playerScore word.size() - 3
 * @param word size determines score
 */
void Boggle::updateScore(string word){
    playerScore += word.size() - 3;
}

set<string> Boggle::getComputerWords(){
    return computerWords;
}
/**
 * @brief Boggle::getComputerScore for every word in computerWords, the score is increased
 * @return computerScore
 */
int Boggle::getComputerScore(){
    for(set<string>::iterator it = computerWords.begin(); it != computerWords.end(); ++it){
        string tempWord = *it;
        computerScore += (tempWord.size() - 3);
    }
    return computerScore;
}

void Boggle::resetWordsScore(){
    playerScore = 0;
    computerScore = 0;
    playerWords.clear();
    computerWords.clear();
}
