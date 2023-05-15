#ifndef ALG
#define ALG

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <string>
#include <list>

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
    Search_Node(BW_Puzzle& pzl, unsigned cst, unsigned heu): node_pzl(pzl), cost(cst), heuristic(heu) {};

    Search_Node(const Search_Node& nd): node_pzl(nd.node_pzl), cost(nd.cost), heuristic(nd.heuristic) {};

    Search_Node(Search_Node* nd): node_pzl(nd->node_pzl), cost(nd->cost), heuristic(nd->heuristic) {};

    Search_Node& operator=(const Search_Node& rhs){
        this->node_pzl = rhs.node_pzl;
        this->cost = rhs.cost;
        this->heuristic = rhs.heuristic;
        return *this;
    }

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

unsigned misplacedTile(const BW_Puzzle& pz){
    unsigned mt = 0;
    int tmp_cls = -2;
    int cnt = 0;
    unsigned seen = 0;

    while((seen < ((pz.size-2)/2)) && (cnt < pz.size)){
        tmp_cls = get<1>(pz.board[cnt++]);
        if(tmp_cls != -1){
            seen++;
            if(tmp_cls != 1){
                mt++;
            }
        }
    }
    mt *= 2;
    if((pz.blanks[0] != 0) && (pz.blanks[0] != pz.size-2)){mt += 2;}
    return mt;
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

unsigned manhattan(const BW_Puzzle& pz){
    unsigned mh = 0;
    int tmp_cls = -2;
    int seen = 0;
    unsigned sz = pz.size;
    unsigned first_half = (sz-2) / 2;
    unsigned temp_lbls[sz - 2];

//    cout << "mh sees: ";
    for(unsigned i = 0; i < sz; i++){
        tmp_cls = get<1>(pz.board[i]);
        if(tmp_cls != -1){
            temp_lbls[seen++] = tmp_cls;
//            cout << tmp_cls << " ";
        }
    }
//    cout << endl;

    for(unsigned i = 0; i < sz-2; i++){
        if(i < first_half){
            if(temp_lbls[i] != 1){
                mh += first_half - i;
            }
        }
        else{
            if(temp_lbls[i] != 0){
                mh += (i - first_half) + 1;
            }
        }
    }
    return mh;
}

//unsigned manhattan(const BW_Puzzle& pz){
//    unsigned mh = 0;
//    int tmp_cls = -2;
//    int cnt = 0;
//    int first_class = -2;
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
//    first_class = (cls_cnts[0] > cls_cnts[1]) ? 0 : 1;
//
//    mx_cnt = (pz.size-2) / 2;
//    cnt = 0;
//    while(mx_cnt > 0){
//        tmp_cls = get<1>(pz.board[cnt]);
//        if((tmp_cls != first_class) && (tmp_cls != -1)){
//            mx_cnt--;
//            mh += ((pz.size-2) / 2) - cnt;
//        }
//        else if(tmp_cls == -1){
//            mx_cnt--;
//        }
//        cnt++;
//    }
//    first_class = first_class ? 0 : 1;
//    while(cnt < pz.size){
//        tmp_cls = get<1>(pz.board[cnt]);
//        if((tmp_cls != first_class) && (tmp_cls != -1)){
//            mh += cnt - ((pz.size-2) / 2) - 1;
//        }
//        cnt++;
//    }
//    return mh;
//}

unsigned is_solution(BW_Puzzle& pzl){
    unsigned target_cls;
    unsigned sz = pzl.size;
    unsigned first_half = (sz-2) / 2;

    if((pzl.blanks[0] != 0) && (pzl.blanks[0] != pzl.size-2)){return false;}

    for(unsigned i = 0; i < sz; i++){
        target_cls = get<1>(pzl.board[i]);
        if(i < first_half){
            if(target_cls == 0){
                return false;
            }
        }
        else{
            if(target_cls == 1){
                return false;
            }
        }
    }

    return true;
}

string hash_state(BW_Puzzle& pzl){
    string temp = "";
    for(unsigned i = 0; i < pzl.size; i++){
        temp += to_string(get<1>(pzl.board[i]));
    }
    return temp;
}

void generalSearch(BW_Puzzle& pzl, const unsigned heu, bool print, bool swtch){
    clock_t timeS = clock();
    unsigned mostExpanded = 0;  // largest size of the queue
    unsigned sizeTemp = 0;      // used to store size of queue every time
    unsigned totalExp = 0;      // increments when a node is expanded
    bool solved = false;        // loop condition
    unordered_map<string, uint8_t> visited_nodes;
//    list<Search_Node*> solution path;
    list<Search_Node*> nodes;          // list of nodes
    ofstream write;             // write stream for tracing file
    nodes.push_front(new Search_Node(pzl,0,0)); //First node, no cost, no heuristic, last move is invalid
    if(print){
        write.open("Trace.txt");
        if(!write.is_open()){
            cout << "error opening file" << endl;
            exit(1);
        }
    }
    while(!solved){
        if(nodes.empty()){
            cout << "Failed to solve the puzzle" << endl; // node list empty, no solution
            if(print){write.close();}
            return;
        }
        nodes.sort(smallerNode); // sort node list every loop execution
        Search_Node temp = *nodes.front(); // make a copy so as to not need top directly
        nodes.pop_front(); // delete top
        sizeTemp = nodes.size(); // store size temporarily
        totalExp++;             // increment number of nodes expanded
        mostExpanded = max(mostExpanded, sizeTemp); // compare what the max size of the list was to the current size,
        visited_nodes.insert({hash_state(temp.node_pzl),0});

        if(print){ write << temp.node_pzl << "cost: " << temp.cost << " heu: " << temp.heuristic <<" in queue: " << nodes.size() << "\n" << endl;}
//        cout << "\n\n" << temp.node_pzl << " cost: " << temp.cost << " heu: " << temp.heuristic <<" in queue: " << nodes.size() << "\n" << endl;
        if(is_solution(temp.node_pzl)){ // output the data needed for the report
            cout << "Solution found at depth: " << temp.cost;
            cout << "\nTotal nodes expanded: " << totalExp;
            cout << "\nMax size of queue: "<< mostExpanded;
            cout << "\nCPU time (linux only): " << static_cast<double>((clock()-timeS))/CLOCKS_PER_SEC << " seconds";
            cout << "\nNodes at frontier: " << nodes.size() << endl;
            if(print){write.close();}
            return;
        }
        else{ // expand nodes
//            cout << "Node expansion" << endl;
            Search_Node tempMoves = temp; // dummy variable
            for(unsigned i = 0; i < (temp.node_pzl.size - 1); i++){
                tempMoves = temp;
                bool validMove = swtch ? tempMoves.node_pzl.swap_with_blank_swtch(i, i+1) : tempMoves.node_pzl.swap_with_blank(i, i+1);
                if(validMove){
                    string tmp_hsh = hash_state(tempMoves.node_pzl);
//                    cout << "Checking if " << tmp_hsh << " already exists" << endl;
                    if(visited_nodes.find(tmp_hsh) == visited_nodes.end()){
                        tempMoves.cost += 1;
                        switch (heu) {
                            case 0:
                                //misplaced tile
                                tempMoves.heuristic = misplacedTile(tempMoves.node_pzl);
                                break;
                            case 1:
                                // manhattan
                                tempMoves.heuristic = manhattan(tempMoves.node_pzl);
                                break;
                            default:
                                // uniform cost
                                tempMoves.heuristic = 0;
                                break;
                        }
                        nodes.push_front(new Search_Node(tempMoves));
                    }
                }
            }
        }
    }
}

#endif