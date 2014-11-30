/*
 * A class representing a grid with characters which are randomly choosen from 16 different six sided cubes
 * The layout of the grid decides what words can be created by the player and the computer.
 * danjo732, piehe154
 * */

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <grid.h>
#include <lexicon.h>
#include <set>

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    void updateScore(string word);

    /**
     * @brief findWordInGrid
     * @param tempWord
     * @return if word is in the board
     */
    bool findWordInGrid(string tempWord);

    void computerFind();

    /**
     * @brief createGrid
     * @param gridString
     */
    void createGrid(string gridString);


    /**
     * @brief getGrid
     * @return our grid
     */
    Grid<char> getGrid();

    /**
     * @brief getNUM_CUBES
     * @return NUM CUBES
     */
    int getNUM_CUBES() const;

    set<string> getPlayerWords() const;

    void insertplayerWord(string playerWord);

    int getPlayerScore() const;

    int getComputerScore() const;

    set<string> getComputerWords() const;

    void resetWordsScore();

private:
    /**
     * @brief boggleGrid representation of cubes in a grid
     */
    Grid<char> boggleGrid;
    int playerScore = 0;
    int computerScore = 0;
    set<string> computerWords;
    set<string> playerWords;

    bool findNeighbours(int row, int col, string word, Grid<char> grid);
    void findComputerNeighbours(int row, int col, string currentWord, Grid<char> grid, Lexicon lex);

};

#endif
