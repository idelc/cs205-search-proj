#ifndef CS205_SEARCH_PROJ_MENU_H
#define CS205_SEARCH_PROJ_MENU_H

#include <iostream>
#include <cstdlib>
#include <locale>

#include "algorithms.h"
#include "puzzle_generator.h"

void basicTest(bool stch){
    int menuIn = -1;
    BW_Puzzle toUse(8);
    cout << "What heuristic would you like to use?\n";
    cout << "1. Misplaced Tile\n";
    cout << "2. Manhattan Distance\n";
    cout << "3. Uniform Cost\n";
    cout << "0. Return\n";
    cin >> menuIn;
    cout << endl;
    // read option from user, call appropriate function
    switch (menuIn) {
        case 0:
            return;
        case 1:
            generalSearch(toUse, 1, 0);
            return;
        case 2:
            generalSearch(toUse, 2, 1);
            return;
        case 3:
            generalSearch(toUse, 3, 0);
            return;
        default:
            cout << "Unrecognized input, please try again" << endl;
            menuIn = -1;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
    }
}

void mainMenu(){
    int menuIn = -1;
    while(menuIn){
        // main output
        cout << "\nBlack, White Puzzle Solver- idelc\n" << endl;
        cout << "Main Menu" << endl;
        cout << "1. 8 tiles, No Switching Order\n";
        cout << "2. 8 tiles, Switch Order\n";
        cout << "3. Custom Size\n";
        cout << "4. Custom Size, with printout to Trace.txt\n";
        cout << "0. Exit\n" << endl;
        cin >> menuIn;
        cout << endl;
        // read option from user, call appropriate function
        switch (menuIn){
            case 0:
                break;

            case 1:
                basicTest(false);
                break;

            case 2:
                basicTest(true);
                break;

            case 3:
//                customSize(false);
                break;

            case 4:
//                customSize(true);
                break;

            default:
                cout << "Unrecognized input, please try again" << endl;
                menuIn = -1;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
        }
    }
    cout << "Goodbye!\n" << endl;
    return;
}


#endif //CS205_SEARCH_PROJ_MENU_H
