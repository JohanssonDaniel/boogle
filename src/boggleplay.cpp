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
// TODO: include any other header files you need

const string alphabet  = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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
    char answer;
    bool answered = false;
    string manualGrid;
    bool correctFormat;

    while(!answered) {
        cin >> answer;
        if (answer == 'y') {
            boggle.createGrid();
            answered = true;
        }
        else if (answer == 'n') {
            //TODO: Manuel inmatning av kubsträng.
            answered = true;
            while (!correctFormat) {
                cout << "Please type a string with size 16, a-z" << endl;
                cin >> manualGrid;
                int noCubes = boggle.fetchNUM_CUBES();
                if (manualGrid.size() == noCubes) {

                    for (int j = 0; j < noCubes; j++) {
                        if (!alphabet.find(manualGrid[j])) {
                            cout << "Not a valid string" << endl;
                            correctFormat = false;
                            break;
                        }
                        correctFormat = true;

                    }

                } else {
                    cout << "Not a valid string" << endl;
                }
            }
        }
    }

    cout << "It's your turn!" << endl;
    printGrid(boggle.fetchGrid());

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
