#ifndef ALG
#define ALG

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <string>
#include <list>
#include <algorithm>
#include <stack>

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
    // basic constructor with info needed for node
    Search_Node(BW_Puzzle& pzl, unsigned cst, unsigned heu): node_pzl(pzl), cost(cst), heuristic(heu) {};

    // copy constructor using reference
    Search_Node(const Search_Node& nd): node_pzl(nd.node_pzl), cost(nd.cost), heuristic(nd.heuristic) {};

    // copy constructor using pointer
    Search_Node(Search_Node* nd): node_pzl(nd->node_pzl), cost(nd->cost), heuristic(nd->heuristic) {};

    // assignment overload to simplify code
    Search_Node& operator=(const Search_Node& rhs){
        this->node_pzl = rhs.node_pzl;
        this->cost = rhs.cost;
        this->heuristic = rhs.heuristic;
        return *this;
    }

    // destructor
    ~Search_Node(){}

    // Puzzle at the node
    BW_Puzzle node_pzl;
    // Cost so far, or amount of moves made so far
    unsigned cost;
    // The value returned by the heuristic function for the puzzle
    unsigned heuristic;
};

// comparitor function for nodes, adapted from list sort reference above
bool smallerNode(const Search_Node& node1, const Search_Node& node2){
    return ((node1.cost+node1.heuristic)<(node2.cost+node2.heuristic));
}

// receive puzzle as input, then begin going through it and pointing out
// which tiles are out of place. Want all black then all white tiles
// Divide by 2 because symmetrical (if white tile is out of place, there is a black tile
// taking its place on the other size. Testing revealed NOT accounting for this overestimates
unsigned misplacedTile(const BW_Puzzle& pz){
    unsigned mt = 0;
    int tmp_cls = -2;
    unsigned sz = pz.size;
    unsigned half = (sz-2) / 2; // halfway point calculation for ease of use

    for(unsigned i = 0; i < sz-2; i++){ // check whole board
        if(i < half){ // if in first half
            if(get<1>(pz.board[i]) != 1){ // note number of non black tiles
                mt++;
            }
        }
        else if(i < sz-2){
            if(get<1>(pz.board[i]) != 0){ // repeat for white tiles in second half
                mt++;
            }
        }
    }
//    if(pz.blanks[0] != sz-2){
//        mt += 2;
//    }
    return mt/2;
}

//unsigned misplacedTile(const BW_Puzzle& pz){
//    unsigned mt = 0;
//    int tmp_cls = -2;
//    int cnt = 0;
//    unsigned mx_cnt = (pz.size-2) / 2;
//    unsigned cls_cnts[2] = {0,0}; // white at 0, black at 1
//
//    while(mx_cnt > 0){
//        tmp_cls = get<1>(pz.board[cnt]);
//        if(tmp_cls >= 0){
//            mx_cnt--;
//            cls_cnts[tmp_cls] += 1 ;
//        }
//        cnt++;
//    }
//
//    if(cls_cnts[0] > cls_cnts[1]){
//        mt = cls_cnts[1] * 2;
//    }
//    else{
//        mt = cls_cnts[0] * 2;
//    }
//
//    return mt;
//}

// checks the distance from a tile which is out of place to its destination
// Since we do not know proper end spot, try to underestimate by finding minimal movement distance
// note, since we do not move tiles alone or in a simple linear manner, this will overestimate and is
// not a good heuristic for this puzzle
unsigned manhattan(const BW_Puzzle& pz){
    unsigned mh = 0;
    int tmp_cls = -2;
    int seen = 0;
    unsigned sz = pz.size;
    unsigned first_half = (sz-2) / 2;
//    unsigned temp_lbls[sz - 2];

    for(unsigned i = 0; i<sz; i++){ // check all the board
        tmp_cls = get<1>(pz.board[i]); // store value we are looking at to minimize access
        if(tmp_cls != -1){ // if not a blank
            if(i < first_half){ // if in first half
                if(tmp_cls != 1){ // check how far away white tiles are from their side
                    mh += first_half - i;
                }
            }
            else{ // in second half
                if(tmp_cls != 0){ // check how far away black tiles are from their side
                    mh += i-first_half-1;
                }
            }
        }
    }

    // check how far blanks are away from edge
    // problem statement says result must be contiguous
    if(pz.blanks[0] != sz-2){
        mh += (sz-2-pz.blanks[0])*2;
    }
    return mh;
}

//unsigned manhattan(const BW_Puzzle& pz){
//    unsigned mh = 0;
//    int tmp_cls = -2;
//    int seen = 0;
//    unsigned sz = pz.size;
//    unsigned first_half = (sz-2) / 2;
//    unsigned temp_lbls[sz - 2];
//
////    cout << "mh sees: ";
//    for(unsigned i = 0; i < sz; i++){
//        tmp_cls = get<1>(pz.board[i]);
//        if(tmp_cls != -1){
//            temp_lbls[seen++] = tmp_cls;
////            cout << tmp_cls << " ";
//        }
//    }
////    cout << endl;
//
//    for(unsigned i = 0; i < sz-2; i++){
//        if(i < first_half){
//            if(temp_lbls[i] != 1){
//                mh += first_half - i;
//            }
//        }
//        else{
//            if(temp_lbls[i] != 0){
//                mh += (i - first_half) + 1;
//            }
//        }
//    }
//
//    if((pz.blanks[0] != 0) && (pz.blanks[0] != pz.size-2)){
//        mh += min((pz.blanks[0]*2),((pz.size-2-pz.blanks[0])*2));
//    }
//    return mh;
//}

// checks if current state is all black then all white tiles
unsigned is_solution(BW_Puzzle& pzl){
    unsigned target_cls;
    unsigned sz = pzl.size;
    unsigned first_half = (sz-2) / 2;

    // if tiles not contiguous, easy exit
    if((pzl.blanks[0] != 0) && (pzl.blanks[0] != pzl.size-2)){return false;}

    // else check ordering of color, not ID
    for(unsigned i = 0; i < sz; i++){
        target_cls = get<1>(pzl.board[i]);
        if(i < first_half){ // first half
            if(target_cls == 0){ // find white tile, exit
                return false;
            }
        }
        else{ // second half
            if(target_cls == 1){ // find black tile exit
                return false;
            }
        }
    }

    // if we reach here, we are done!
    return true;
}

// to keep track of visited states, use hash table, but need unique key
// simply turn their ID into a string, return that for hashing
// the ID for everything except blanks are unique, and we dont care about
// which blank is where
string hash_state(BW_Puzzle& pzl){
    string temp = "";
    for(unsigned i = 0; i < pzl.size; i++){
        temp += to_string(get<1>(pzl.board[i]));
    }
    return temp;
}

// This is the general search algorithm from the course notes and project description
// get all info, then start by making the root node. Push it into a waiting queue
// loop: check if empty (for fully searched/ fail)
// if not then grab best node and check if solution
// if not expand its children into the queue
void generalSearch(BW_Puzzle& pzl, const unsigned heu, bool print, bool swtch){
    clock_t timeS = clock();    // time stamp for start
    unsigned mostExpanded = 0;  // largest size of the queue
    unsigned sizeTemp = 0;      // used to store size of queue every time
    unsigned totalExp = 0;      // increments when a node is expanded
    bool solved = false;        // loop condition
//    stack<Search_Node> sol_path;
    unordered_map<string, uint8_t> visited_nodes; // hash map for repeat states
    list<Search_Node*> nodes;          // list of nodes
    ofstream write;             // write stream for tracing file
    nodes.push_front(new Search_Node(pzl,0,0)); //First node, no cost, no heuristic, last move is invalid
//    Search_Node temp = *nodes.front();
//    sol_path.push(temp);
    if(print){ // if printing to file, open it
        write.open("Trace.txt");
        if(!write.is_open()){
            cout << "error opening file" << endl;
            exit(1);
        }
    }
    while(!solved){ // infinite loop, returns on its own
        if(nodes.empty()){ // searched to failure, print data then close file
            cout << "Failed to solve the puzzle"; // node list empty, no solution
            cout << "\nTotal nodes expanded: " << totalExp;
            cout << "\nMax size of queue: "<< mostExpanded;
            cout << "\nCPU time (linux only): " << static_cast<double>((clock()-timeS))/CLOCKS_PER_SEC << " seconds" << endl;
            if(print){write.close();}
            return;
        }
        nodes.sort(smallerNode); // sort node list every loop execution (works regardless of heuristic)
        Search_Node temp = *nodes.front(); // make a copy so as to not need top directly
//        while(sol_path.top().cost >= temp.cost){ // track solution path, broken
//            sol_path.pop();
//        }
//        sol_path.push(temp);
        nodes.pop_front(); // delete top
        sizeTemp = nodes.size(); // store size temporarily
        totalExp++;             // increment number of nodes expanded
        mostExpanded = max(mostExpanded, sizeTemp); // compare what the max size of the list was to the current size,
        visited_nodes.insert({hash_state(temp.node_pzl),0}); // hash state as seen

        if(print){ write << temp.node_pzl << " cost: " << temp.cost << " heu: " << temp.heuristic <<" in queue: " << nodes.size() << "\n" << endl;}
//        cout << "\n\n" << temp.node_pzl << " cost: " << temp.cost << " heu: " << temp.heuristic <<" in queue: " << nodes.size() << "\n" << endl;
        if(is_solution(temp.node_pzl)){ // output the data needed for the report
            cout << "Solution found at depth: " << temp.cost;
            cout << "\nTotal nodes expanded: " << totalExp;
            cout << "\nMax size of queue: "<< mostExpanded;
            cout << "\nCPU time (linux only): " << static_cast<double>((clock()-timeS))/CLOCKS_PER_SEC << " seconds";
            cout << "\nNodes at frontier: " << nodes.size() << endl;
            if(print){write.close();}
//            ofstream writeSol;
//            writeSol.open("solution_path.txt");
//            if(!writeSol.is_open()){
//                cout << "error opening file" << endl;
//                exit(1);
//            }
//            while(!sol_path.empty()){
//                temp = sol_path.top();
//                writeSol << temp.node_pzl << " cost: " << temp.cost << " heu: " << temp.heuristic <<" in queue: " << nodes.size() << "\n" << endl;
//                sol_path.pop();
//            }
            return;
        }
        else{ // expand nodes becase not solution
//            cout << "Node expansion" << endl;
            Search_Node tempMoves = temp; // dummy variable
            for(unsigned i = 0; i < (temp.node_pzl.size - 1); i++){ // iterate through all pairs
                tempMoves = temp;
                // check if current index and next one are able to be pulled out then pushed in
                // also checks problem definition (tile switching)
                bool validMove = swtch ? tempMoves.node_pzl.swap_with_blank_swtch(i, i+1) : tempMoves.node_pzl.swap_with_blank(i, i+1);
                // valid mode
                if(validMove){
                    string tmp_hsh = hash_state(tempMoves.node_pzl);
//                    cout << "Checking if " << tmp_hsh << " already exists" << endl;
                    // check if we have seen it
                    if(visited_nodes.find(tmp_hsh) == visited_nodes.end()){
                        // if we havent, then create it, traversing edge
                        tempMoves.cost += 1;
                        // then calculating the heuristic (0 for Uniform cost of course)
                        switch (heu) {
                            case 1:
                                //misplaced tile
                                tempMoves.heuristic = misplacedTile(tempMoves.node_pzl);
                                break;
                            case 2:
                                // manhattan
                                tempMoves.heuristic = manhattan(tempMoves.node_pzl);
                                break;
                            default:
                                // uniform cost
                                tempMoves.heuristic = 0;
                                break;
                        }
                        // add to queue then start loop again
                        nodes.push_front(new Search_Node(tempMoves));
                    }
                }
            }
        }
    }
}

#endif