#ifndef CS205_SEARCH_PROJ_PUZZLE_GENERATOR_H
#define CS205_SEARCH_PROJ_PUZZLE_GENERATOR_H

#include <iostream>
#include <cstdlib>
#include <tuple>
#include <cstring>

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

    // deep copy constructor
    BW_Puzzle(const BW_Puzzle &cpy):size(cpy.size){
        board = (tuple<unsigned, int>*) malloc(size * sizeof(tuple<unsigned, int>));
        memcpy(board, cpy.board, sizeof(tuple<unsigned, int>) * cpy.size);
        blanks[0] = cpy.blanks[0];
        blanks[1] = cpy.blanks[1];
    };

    // overload assignment operator
    BW_Puzzle & operator=(const BW_Puzzle & rhs){
        if(this->size != rhs.size) {exit(1);} // do not copy mismatched sizes
        memcpy(this->board, rhs.board, sizeof(tuple<unsigned, int>) * rhs.size);
        this->blanks[0] = rhs.blanks[0];
        this->blanks[1] = rhs.blanks[1];
        return *this;
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

    // Main manipulation method. Pass in two indexes, check if adjacent, non-blank
    // swap with blank after flipping. Return true for successful op.
    bool swap_with_blank_swtch(unsigned left, unsigned right){
        if((left >= this->size)||(left < 0)){return false;} // invalid index check
        if((right >= this->size)||(right < 0)){return false;}
        if((left + 1) != right){return false;} // non adjacency check
        if((left == blanks[0])||(left == blanks[1])){return false;} // check if blanks
        if((right == blanks[0])||(right == blanks[1])){return false;} // check if blanks

        tuple<unsigned, int> temp = this->board[left];
        this->board[left] = this->board[blanks[1]];
        this->board[blanks[1]] = temp;

        temp = this->board[right];
        this->board[right] = this->board[blanks[0]];
        this->board[blanks[0]] = temp;

        blanks[0] = left;
        blanks[1] = right;

        return true;
    }


    // variables
    unsigned size; // size of the board, will be input + 2 to add the blanks at the beginning
    unsigned blanks[2]; // the location of the two blanks
    tuple<unsigned, int> *board; // the physical board, holds tupples indicating <ID, is_black>
};


#endif //CS205_SEARCH_PROJ_PUZZLE_GENERATOR_H
