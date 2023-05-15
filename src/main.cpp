#include <iostream>

using namespace std;

#include "../headers/puzzle_generator.h"
#include "../headers/algorithms.h"
#include "../headers/menu.h"

int main(){
    mainMenu();
    return 0;
}

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
//    test4.swap_with_blank_swtch(5,6);
//    cout << test4 << ", left_blank = " << test4.blanks[0] << ", right_blank = " << test4.blanks[1] << endl;
//    cout << "Misplaced tiles; expected 4 got " << misplacedTile(test4) << endl;
//    cout << "Manhattan dist; got " << manhattan(test4) << endl;
//    test4.swap_with_blank_swtch(1,2);
//    cout << test4 << ", left_blank = " << test4.blanks[0] << ", right_blank = " << test4.blanks[1] << endl;
//    cout << "Misplaced tiles; expected 2 got " << misplacedTile(test4) << endl;
//    cout << "Manhattan dist; got " << manhattan(test4) << endl;
//    return 0;
//}