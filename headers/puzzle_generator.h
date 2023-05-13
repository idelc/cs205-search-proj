#ifndef CS205_SEARCH_PROJ_PUZZLE_GENERATOR_H
#define CS205_SEARCH_PROJ_PUZZLE_GENERATOR_H

#include <iostream>
#include <cstdlib>
#include <tuple>

using namespace std;

class BW_Puzzle{
 public:
    // constructor for the black white puzzle
    BW_Puzzle(unsigned sz): size(sz+2){ // assume that appropriate size was passed in (even)
        // dynamically allocate the space we need for the board
        board = (tuple<unsigned, int>*) malloc(size * sizeof(tuple<unsigned, int>));

        // create the blanks, set their positions and place faux pieces on the board
        blanks[0] = 0;
        board[0] = {0,-1}; // ID: 0, is neither black nor white
        blanks[1] = 1;
        board[1] = {0,-1};

        // create the rest of the board
        int is_black = 0;
        for(unsigned i = 2; i<size ; i++){
            board[i] = {i-1, is_black}; // set ID based on index and alternate color
            is_black = is_black ? 0 : 1; // flip color every iteration
        }
    };

    ~BW_Puzzle(){ // destructor
        free(board); // release mem pointed to by malloc
    }

    // overloaded print operator
    friend ostream& operator<<(ostream& o, const BW_Puzzle& pz1){
        o << "[";
        for(unsigned i = 0; i < pz1.size - 1; i++){
            o << "(" << get<0>(pz1.board[i]) << ",";
            switch (get<1>(pz1.board[i])) {
                case -1:
                    o << "_), ";
                    break;
                case 0:
                    o << "W), ";
                    break;
                case 1:
                    o << "B), ";
                    break;
                default:
                    exit(1);
                    break;
            }
        }
        o << "(" << get<0>(pz1.board[pz1.size - 1]) << ",";
        switch (get<1>(pz1.board[pz1.size - 1])) {
            case -1:
                o << "_)]";
                break;
            case 0:
                o << "W)]";
                break;
            case 1:
                o << "B)]";
                break;
            default:
                exit(1);
                break;
        }

        return o;
    }



    // variables
    unsigned size; // size of the board, will be input + 2 to add the blanks at the beginning
    unsigned blanks[2]; // the location of the two blanks
    tuple<unsigned, int> *board; // the physical board, holds tupples indicating <ID, is_black>
};


#endif //CS205_SEARCH_PROJ_PUZZLE_GENERATOR_H
