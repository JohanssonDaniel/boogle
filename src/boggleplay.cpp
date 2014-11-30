/*
 * Class that handles input and output from/to the user, delegates input to Boggle.cpp
 * danjo732, piehe154
 * */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include "grid.h"
#include <algorithm>
#include <lexicon.h>
#include <set>

const string alphabet  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
/**
 * @brief clearWordsScore calls boggle.resetScore() to reset the score
 */
void clearWordsScore(Boggle& boggle){
    boggle.resetWordsScore();
}
/**
 * @brief printComputerWords prints the words that computer found and the score that it got
 * @param boggle
 */
void printComputerWords(Boggle& boggle){

    boggle.computerFind();

    set<string> words = boggle.getComputerWords();
    clearConsole();
    cout << "It's my turn!" << endl;
    cout << "My words (" << words.size() << "): " << "{";

    for(set<string>::iterator it = words.begin(); it != words.end(); it++){
        cout << "\""<< *it << "\",";
    }

    cout << "}";
    cout << "\nMy score: "  << boggle.getComputerScore() << endl;
    //If the computer has won the game, taunt the player
    if(boggle.getComputerScore() > boggle.getPlayerScore()){
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    }
}
/**
 * @brief printPlayerWords outputs the words that the player has found
 * @param boggle
 */
void printPlayerWords(Boggle& boggle) {
    set<string> playerWords = boggle.getPlayerWords();
    cout << "Your words (" <<  playerWords.size() << "):";

    for(set<string>::iterator it = playerWords.begin(); it != playerWords.end(); it++){
        cout << *it << " ";
    }

    cout << endl;
}
/**
 * @brief printGrid prints the cubes that are in the grid
 * @param boggle
 */
void printGrid(Boggle& boggle){
    Grid<char> grid = boggle.getGrid();
    for(int row = 0; row < grid.numRows(); row++){
        for(int col = 0; col < grid.numCols(); col++){
            cout << grid.get(row, col);
        }
        cout << endl;
    }
}
/**
 * @brief promptplayerInput asks the player to type in a valid word
 * @param boggle
 */
void promptplayerInput(Boggle& boggle){
    Lexicon lex("EnglishWords.dat");
    string tempWord;

    cout << "It's your turn!" << endl;

    printGrid(boggle);

    printPlayerWords(boggle);

    cout << "Your score: " << boggle.getPlayerScore() << endl;
    cout << "Type a word (or press 1 to quit): ";

    cin >> tempWord;
    //makes the str uppercase
    transform(tempWord.begin(), tempWord.end(),tempWord.begin(), ::toupper);
    clearConsole();
    while(tempWord != "1"){

        printGrid(boggle);

        if(!lex.contains(tempWord)){
            cout << "Not a word in the dictionary" << endl;
        }
        else if (!(boggle.getPlayerWords().find(tempWord) != boggle.getPlayerWords().end())) {
            cout << "Word already used" << endl;
        }
        else if ((tempWord.size() < 4)) {
            cout << "Word is too small" << endl;
        }
        else if (!(boggle.findWordInGrid(tempWord))) {
            cout << "That word can't be formed on this board." << endl;
        }
        else {
            boggle.updateScore(tempWord);
            boggle.insertplayerWord(tempWord);
        }

        printPlayerWords(boggle);

        cout << endl;
        cout << "Your score: " << boggle.getPlayerScore() << endl;

        cout << "Type a word (or press 1 to quit): ";
        cin >> tempWord;

        clearConsole();
        //makes the str uppercase
        transform(tempWord.begin(), tempWord.end(),tempWord.begin(), ::toupper);
    }
}
/**
 * @brief promptCreateGrid asks the player if it wants to create a random or
 * manually inputted grid
 */
void promptCreateGrid(Boggle& boggle){
    char answer;
    bool answered = false;
    string manualCharacters = "";
    bool correctFormat;

    cout << "\nDo you want to generate a random board? ";

    while(!answered) {
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            boggle.createGrid(manualCharacters);
            answered = true;
        }
        else if (answer == 'n' || answer == 'N') {
            answered = true;
            while (!correctFormat) {
                cout << "Enter a string with 16 characters, must be a-z" << endl;
                cin >> manualCharacters;
                transform(manualCharacters.begin(), manualCharacters.end(),manualCharacters.begin(), ::toupper); //makes the str uppercase

                int noCubes = boggle.getNUM_CUBES();
                if (manualCharacters.size() == noCubes && (!manualCharacters.find_first_not_of(alphabet) != string::npos)) {
                    correctFormat = true;
                } else {
                    cout << "Incorrect size of string or character, must be 16, a-z" << endl;
                }
            }
            boggle.createGrid(manualCharacters);
        }
    }
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    promptCreateGrid(boggle);
    promptplayerInput(boggle);
    printComputerWords(boggle);
    clearWordsScore(boggle);
}



/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
