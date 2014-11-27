// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

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
// TODO: include any other header files you need

const string alphabet  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void promptUserInput(Boggle& boggle){

    set<string> userWords;
    Lexicon lex("EnglishWords.dat");
    string tempWord;
    cout << "Type a word (or press enter to quit: )";
    cin >> tempWord;

    while(tempWord != ""){

        if(!lex.contains(tempWord)){
            cout << "Not a word in the dictionary" << endl;
        }
        else if ((userWords.find(tempWord) != userWords.end())) {
            cout << "Word already used" << endl;
        }
        else if ((tempWord.size() < 4)) {
            cout << "Word is too small" << endl;
        }
        else if (boggle.findWordInGrid(tempWord)) {
            //giltigt ord
        }
        else {

            userWords.insert(tempWord);
        }

        cout << "Your words (" << userWords.size() << "):";
        for(set<string>::iterator it = userWords.begin(); it != userWords.end(); it++){
            cout << *it << " ";
        }
        cout << endl;

        cout << "Type a word (or press enter to quit: )";
        cin >> tempWord;
    }
}

void promptCreateGrid(Boggle& boggle){
    char answer;
    bool answered = false;
    string manualCharacters = "";
    bool correctFormat;

    while(!answered) {
        cin >> answer;
        if (answer == 'y') {
            boggle.createGrid(manualCharacters);
            answered = true;
        }
        else if (answer == 'n') {
            answered = true;
            while (!correctFormat) {
                cout << "Enter a string with 16 characters, must be a-z" << endl;
                cin >> manualCharacters;
                transform(manualCharacters.begin(), manualCharacters.end(),manualCharacters.begin(), ::toupper); //makes the str uppercase

                int noCubes = boggle.fetchNUM_CUBES();
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
void printGrid(Grid<char> grid){

    for(int row = 0; row < grid.numRows(); row++){
        for(int col = 0; col < grid.numCols(); col++){
            cout << grid.get(row, col);
        }
        cout << endl;
    }
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    cout << "Do you want to generate a random board?";
    promptCreateGrid(boggle);
    printGrid(boggle.fetchGrid());
    promptUserInput(boggle);
    cout << "It's your turn!" << endl;
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
