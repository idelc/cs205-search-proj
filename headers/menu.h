#ifndef CS205_SEARCH_PROJ_MENU_H
#define CS205_SEARCH_PROJ_MENU_H

#include <iostream>
#include <cstdlib>
#include <locale>
#include <cctype>

#include "algorithms.h"
#include "puzzle_generator.h"

// ask user for the puzzle size they would like
unsigned getUsrSize(){
    unsigned menuIn = 0;
    cout << "Enter puzzle size: ";
    cin >> menuIn;
    cout << endl;
    return menuIn;
}

// ask user if they want tile switching
// Ex: 7, 8 returned to board as 8, 7
unsigned getUsrSwtch(){
    char menuIn = 'f';
    while(menuIn){
        cout << "Switch tile order when placing (Y/N)? ";
        cin >> menuIn;
        cout << endl;
        menuIn = toupper(menuIn);
        switch (menuIn) {
            case 'Y':
                return 1;
            case 'N':
                return 0;
            default:
                cout << "Unrecognized input, please try again" << endl;
                menuIn = -1;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
        }
    }
    return 1;
}

// ask user which heuristic they want to use
unsigned getUsrHeu(){
    int menuIn = -1;
    while(menuIn){
        cout << "What heuristic would you like to use?\n";
        cout << "1. Misplaced Tile\n";
        cout << "2. Manhattan Distance\n";
        cout << "3. Uniform Cost\n";
        cin >> menuIn;
        cout << endl;
        // read option from user, call appropriate function
        switch (menuIn) {
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return 3;
            default:
                cout << "Unrecognized input, please try again" << endl;
                menuIn = -1;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
        }
    }
    return 1;
}

// Menu to set up custom test, allows puzzle manipulation
// Checks for legality of moves
void customTest(){
    int menuIn = -1;
    unsigned pzl_sz = getUsrSize();
    unsigned sth = getUsrSwtch();
    unsigned hu = getUsrHeu();
    int inO = -1, inT = -2;
    int inTh = -1, inF = -2;

    BW_Puzzle toTest(pzl_sz);

    while(menuIn != 3){
        cout << "Here is the puzzle so far:\n" << toTest << endl;
        cout << "1. Swap tiles, keep order\n";
        cout << "2. Swap tiles, swap order\n";
        cout << "3. Continue\n";
        cout << "0. Return\n";
        cin >> menuIn;
        cout << endl;

        switch (menuIn) {
            case 0:
                return;
            case 1:

                cout << "Left Index: ";
                cin >> inO;
                cout << "\nRight Insdex: ";
                cin >> inT;
                cout << endl;
                if(!toTest.swap_with_blank(inO,inT)){
                    cout << "Invalid, try again" << endl;
                }
                break;
            case 2:

                cout << "Left Index: ";
                cin >> inTh;
                cout << "\nRight Insdex: ";
                cin >> inF;
                cout << endl;
                if(!toTest.swap_with_blank_swtch(inTh,inF)){
                    cout << "Invalid, try again" << endl;
                }
                break;
            case 3:
                break;
            default:
                cout << "Unrecognized input, please try again" << endl;
                menuIn = -1;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
        }
    }
    generalSearch(toTest, hu, 1, sth);
    return;
}

// setup for a simple test of the puzzle with passed in parameters
void basicTest(unsigned pzl_sz, bool swtch){
    int menuIn = -1;
    BW_Puzzle toUse(pzl_sz);
    unsigned hu = getUsrHeu();
    generalSearch(toUse, hu, true, swtch);
    return;
}

// allow user to pass in the size of the puzzle they want and do quick search
void customSize(bool swtch){
    unsigned menuIn = 8;
    while(menuIn){
        cout << "Enter the size of the puzzle (0 to exit): ";
        cin >> menuIn;
        cout << endl;
        if(menuIn == 0){
            return;
        }
        else{
            cout << "Starting puzzle of size " << menuIn << endl;
            basicTest(menuIn, swtch);
            return;
        }
    }
}

// primary control mechanism for interface, just take user input
// and use switch statements to call appropriate functions
// called in main
void mainMenu(){
    int menuIn = 1;
    while(menuIn){
        // main output
        cout << "\nBlack, White Puzzle Solver- idelc\n" << endl;
        cout << "Main Menu" << endl;
        cout << "1. 8 tiles, No Switching Order\n";
        cout << "2. 8 tiles, Switch Order\n";
        cout << "3. Custom Size, No Switching Order\n";
        cout << "4. Custom Size, Switch Order\n";
        cout << "5. Full Custom\n";
        cout << "0. Exit\n" << endl;
        cin >> menuIn;
        cout << endl;
        // read option from user, call appropriate function
        switch (menuIn){
            case 0:
                break;

            case 1:
                basicTest(8, false);
                break;

            case 2:
                basicTest(8, true);
                break;

            case 3:
                customSize(false);
                break;

            case 4:
                customSize(true);
                break;

            case 5:
                customTest();
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
