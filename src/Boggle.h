// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <grid.h>
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    // TODO: decide the public member functions and declare them

    /**
     * @brief findWordInGrid
     * @param tempWord
     * @return if word is in the board
     */
    bool findWordInGrid(string tempWord);

    /**
     * @brief createGrid
     * @param gridString
     */
    void createGrid(string gridString);


    /**
     * @brief fetchGrid
     * @return our grid
     */
    Grid<char> fetchGrid();

    /**
     * @brief fetchNUM_CUBES
     * @return NUM CUBES
     */
    int fetchNUM_CUBES();

private:
    /**
     * @brief boggleGrid representation av kuber som ett grid av char
     */
    Grid<char> boggleGrid;

    // TODO: decide the private member variables/functions and declare them

};

#endif
