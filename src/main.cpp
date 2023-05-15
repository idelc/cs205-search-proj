#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "../headers/puzzle_generator.h"
#include "../headers/algorithms.h"
#include "../headers/menu.h"

int main(){
    mainMenu(); // call the menu and done
    return 0;
}


// test suite for puzzle object
//int main(){
////    BW_Puzzle test3(8);
////    {
////        BW_Puzzle test(8);
////        cout << "Expect: [(0,_), (0,_), (1,W), (2,B), (3,W), (4,B), (5,W), (6,B), (7,W), (8,B)]\n Got: ";
////        cout << test << endl;
////
////        BW_Puzzle test2(test);
////        cout << test2 << endl;
////
////        test3 = test2;
////    }
////    cout << test3 << endl;
//
//    BW_Puzzle test4(8);
//    cout << test4 << ", left_blank = " << test4.blanks[0] << ", right_blank = " << test4.blanks[1] << endl;
//    cout << "Misplaced tiles; expected 4 got " << misplacedTile(test4) << endl;
//    cout << "Manhattan dist; got " << manhattan(test4) << endl;
//    test4.swap_with_blank_swtch(8,9);
//    cout << test4 << ", left_blank = " << test4.blanks[0] << ", right_blank = " << test4.blanks[1] << endl;
//    cout << "Misplaced tiles; expected 6 got " << misplacedTile(test4) << endl;
//    cout << "Manhattan dist; got " << manhattan(test4) << endl;
//    test4.swap_with_blank_swtch(1,2);
//    cout << test4 << ", left_blank = " << test4.blanks[0] << ", right_blank = " << test4.blanks[1] << endl;
//    cout << "Misplaced tiles; expected 8 got " << misplacedTile(test4) << endl;
//    cout << "Manhattan dist; got " << manhattan(test4) << endl;
//
////    BW_Puzzle test4(8);
////    cout << test4 << ", left_blank = " << test4.blanks[0] << ", right_blank = " << test4.blanks[1] << endl;
////    cout << "Misplaced tiles; expected 4 got " << misplacedTile(test4) << endl;
////    cout << "Manhattan dist; got " << manhattan(test4) << endl;
////    test4.swap_with_blank(5,6);
////    cout << test4 << ", left_blank = " << test4.blanks[0] << ", right_blank = " << test4.blanks[1] << endl;
////    cout << "Misplaced tiles; expected 6 got " << misplacedTile(test4) << endl;
////    cout << "Manhattan dist; got " << manhattan(test4) << endl;
////    test4.swap_with_blank(1,2);
////    cout << test4 << ", left_blank = " << test4.blanks[0] << ", right_blank = " << test4.blanks[1] << endl;
////    cout << "Misplaced tiles; expected 8 got " << misplacedTile(test4) << endl;
////    cout << "Manhattan dist; got " << manhattan(test4) << endl;
////    return 0;
//}

// testing suite for the report data
//int main(){
//
//    int pz_sz = 2;
//    for(unsigned i = 0; i < 6; i++){
//        cout << "Puzzle size: " << pz_sz << endl;
//        BW_Puzzle test(pz_sz);
//        generalSearch(test, 2, 0, 0);
//        pz_sz+=2;
//        cout << endl;
//    }
////
////    BW_Puzzle test(8);
//////    cout << test << endl;
////    generalSearch(test, 0, 0, 0);
//    return 0;
//}

// suite to try and find diameter by moving randomly through puzzle variations (size 8)
//int main(){
//    int max = -1;
//    int numRand = 5;
//    int r = 0;
//    unsigned index = 0;
//    int tmp_cst = -1;
//    srand(time(NULL));
//
//    for(unsigned i = 0; i < 1000; i++){
//        BW_Puzzle temp(8);
//        for(unsigned j = 0; j < numRand; j++){
//            r = rand() % 6;
//            temp.swap_with_blank_swtch(r, r+1);
//        }
//        cout << "trying " << temp << endl;
//        tmp_cst = generalSearch(temp, 0,0,1);
//        max = (tmp_cst > max) ? tmp_cst : max;
//        numRand++;
//    }
//    cout << "Got max of " << max << endl;
//    return 0;
//}