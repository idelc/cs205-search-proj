#include <iostream>

using namespace std;

#include "../headers/puzzle_generator.h"

int main(){
    BW_Puzzle test(8);
    cout << "Expect: [(0,_), (0,_), (1,W), (2,B), (3,W), (4,B), (5,W), (6,B), (7,W), (8,B)]\n Got: ";
    cout << test << endl;
    return 0;
}