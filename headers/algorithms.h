#ifndef ALG
#define ALG

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "puzzle_generator.h"

// https://www.geeksforgeeks.org/implement-min-heap-using-stl/
// https://en.cppreference.com/w/cpp/container/priority_queue
// https://www.cplusplus.com/reference/list/list/sort/
// https://stackoverflow.com/questions/20167685/measuring-cpu-time-in-c
// used the first two sites to review the way priority queues are defined in c++
// and used that to properly set up the code needed to sort Nodes
// ended up switching to a list because the min heap was not working
// as well as I hoped, but now I have optimal behavior at the cost of sorting speed
// last site is used to measure cpu time in linux only

class Search_Node{ // class to hold info about search tree node
 public:
    Search_Node(BW_Puzzle& pzl, unsigned cst, unsigned heu, int lstmv[4]): node_pzl(pzl), cost(cst), heuristic(heu) {
        for(unsigned i = 0; i < 4; i++){
            lastMove[i] = lstmv[i];
        }
    };

    Search_Node(const Search_Node& nd): node_pzl(nd.node_pzl), cost(nd.cost), heuristic(nd.heuristic) {
        for(unsigned i = 0; i < 4; i++){
            this->lastMove[i] = nd.lastMove[i];
        }
    };

    Search_Node(Search_Node* nd): node_pzl(nd->node_pzl), cost(nd->cost), heuristic(nd->heuristic) {
        for(unsigned i = 0; i < 4; i++){
            this->lastMove[i] = nd->lastMove[i];
        }
    };

    ~Search_Node(){}

    // Puzzle at the node
    BW_Puzzle node_pzl;
    // Cost so far, or amount of moves made so far
    unsigned cost;
    // The value returned by the heuristic function for the puzzle
    unsigned heuristic;
    // store last move and do not make a node undoing it
    int lastMove[4];
};

// comparitor function for nodes, adapted from list sort reference above
bool smallerNode(const Search_Node& node1, const Search_Node& node2){
    return ((node1.cost+node1.heuristic)<(node2.cost+node2.heuristic));
}

unsigned misplacedTile(BW_Puzzle& pz){
    unsigned mt = 0;
    int first_found = -1;
    int tmp_cls = -2;
    unsigned mx_cnt = (pz.size-2) / 2;
    while(first_found == -1){
        first_found = get<1>(pz.board[mt]);
        mt++;
    }
//    cout << "Found " << first_found << " first" << endl;
    mt = 0;
    for(unsigned i = 0; (i < pz.size) && (mx_cnt > 0); i++){
        tmp_cls = get<1>(pz.board[i]);
        if((tmp_cls != first_found)&&(tmp_cls != -1)){
            mt++;
//            cout << tmp_cls << " not " << first_found << ", " << mt << " " << mx_cnt << endl;
        }
        if(tmp_cls != -1){
            mx_cnt--;
        }
    }
    return mt * 2;
}

#endif