//
//  hw1.cpp
//  
//
//  Created by Mac Book on 9/17/17.
//
//


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <time.h>
#include <math.h>
#include <limits>
#include <list>
#include <map>


using namespace std;
typedef multimap<int, int>::iterator ListIterator;
ofstream outFile;


//BFS
void printVecPair(vector< pair<int, int> > vec, int n);
void printSolution(multimap <int, int> mm, int n);
void printSolution(multimap <int, int> mm, multimap <int, int> trees, int n);
bool isValid(multimap <int, int> poppedState, multimap <int, int> trees, int row, int col);
bool isValidWoTrees(multimap <int, int> poppedState, int row, int col);

void bfs(vector < vector <short> > array, int n, int p);


//DFS
void printVec(vector <vector <short> > vec, int n);
bool isAttackingLastLizardWithTrees(vector < vector <short> > array, int n, int row, int col);
bool isAttackingLastLizardWithoutTrees(vector < vector <short> > array, int n, int row, int col);
bool DFSsolveWithTrees(vector <vector <short> > array, int n, int p, int lizards, int row, int col);
bool DFSsolveNormal(vector <vector <short> > array, int n, int p, int lizards, int row);

bool dfs(vector <vector <short> > vec, int n, int p);


//Simulated Annealing
int calculateNumAttacks(vector <vector <short> > array, int n);
int schedule(int time);
bool accept(float p);
vector <vector <short> > initialSolution(vector <vector <short> > vec, int n, int lizards, int option);
vector <vector <short> > successor(vector <vector <short> > array, int n, int p);

void sa(vector <vector <short> > array, int n, int p);


//*********************************************************************************************//
//********************************* B F S *****************************************************//
//*********************************************************************************************//

void printVecPair(multimap <int, int> mm){
    for(multimap <int, int>::iterator it = mm.begin(); it != mm.end(); it++){
        cout<<"("<<it->first<<","<<it->second<<"), ";
    }
    cout<<endl;
}

void printSolution(multimap <int, int> mm, int n){
    multimap <int, int>::iterator it;
    
    vector <vector <int> > array;
    array.resize(n);
    for(int i=0; i<n; i++)
        array[i].resize(n);
    
    for(it = mm.begin(); it != mm.end(); it++){
        array[it->first][it->second] = 1;
    }
    
    outFile.open("output.txt");
    //cout<<"OK"<<endl;
    outFile<<"OK"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            outFile<<array[i][j];
            //cout<<array[i][j]<<" ";
        }
        outFile<<endl;
        //cout<<endl;
    }
    outFile.close();
    
}

void printSolution(multimap <int, int> mm, multimap <int, int> trees, int n){
    multimap <int, int>::iterator it;
    
    vector <vector <int> > array;
    array.resize(n);
    for(int i=0; i<n; i++)
        array[i].resize(n);
    
    for(it = mm.begin(); it != mm.end(); it++){
        array[it->first][it->second] = 1;
    }
    
    for(it = trees.begin(); it != trees.end(); it++){
        array[it->first][it->second] = 2;
    }
    
    outFile.open("output.txt");
    //cout<<"OK"<<endl;
    outFile<<"OK"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            outFile<<array[i][j];
            //cout<<array[i][j]<<" ";
        }
        outFile<<endl;
        //cout<<endl;
    }
    outFile.close();
    
}


bool isValid(multimap <int, int> poppedState, multimap <int, int> trees, int row, int col){
    //cout<<"In isValid function.."<<endl;
    //cout<<"row: "<<row<<" col: "<<col<<endl;
    //cout<<"poppedState"<<endl;
    //printVecPair(poppedState);
    //cout<<"trees: "<<endl;
    //printVecPair(trees);
    
    int storeRow, storeCol;
    multimap <int, int>::iterator search, search1;
    pair<ListIterator, ListIterator> allTrees, allStates;
    int i, j;
    int breakFlag = 0;
    
    // Skip the position of a tree
    //pair<ListIterator, ListIterator> allTrees;
    allTrees = trees.equal_range(row);
    for(ListIterator it = allTrees.first; it != allTrees.second; it++){
        //cout<<it->second<<endl;
        if(it->second == col){
            //cout<<"Found a tree in this place"<<endl;
            //col++;
            return false;
        }
    }
    
    //Search in the same row. LEFT direction
    //cout<<endl<<"Checking Row"<<endl;
    storeRow = row;
    storeCol = col;
    for(j = storeCol-1; j >= 0; j--){
        //cout<<"j: "<<j<<endl;
        allTrees = trees.equal_range(storeRow);
        allStates = poppedState.equal_range(storeRow);
        //search = trees.find(storeRow);cout<<"search: "<<search->first<<" "<<search->second<<endl;
        //search1 = poppedState.find(storeRow);cout<<"search1: "<<search1->first<<" "<<search1->second<<endl;
        
        // Break whenever we see a tree
        for(ListIterator it = allTrees.first; it != allTrees.second; it++){
            //cout<<"it->second"<<it->second<<endl;
            if(it->second == j){
                breakFlag = 1;
                break;
            }
        }
        
        if(breakFlag == 1){
            breakFlag = 0;
            break;
        }
        
        for(ListIterator it = allStates.first; it != allStates.second; it++){
            //cout<<"it->second"<<it->second<<endl;
            if(it->second == j)
                return false;
        }
    }
    
    //Search in the same column. upward direction
    //cout<<endl<<"Checking column"<<endl;
    storeRow = row;
    storeCol = col;
    for(i = storeRow-1; i >= 0; i--){
        //cout<<"i: "<<i<<endl;
        allTrees = trees.equal_range(i);
        allStates = poppedState.equal_range(i);
        //search = trees.find(i);cout<<"search: "<<search->first<<" "<<search->second<<endl;
        //search1 = poppedState.find(i);cout<<"search1: "<<search1->first<<" "<<search1->second<<endl;
        
        // Break whenever we see a tree
        for(ListIterator it = allTrees.first; it != allTrees.second; it++){
            //cout<<it->second<<endl;
            if(it->second == storeCol){
                breakFlag = 1;
                break;
            }
        }
        
        if(breakFlag == 1){
            breakFlag = 0;
            break;
        }
        
        for(ListIterator it = allStates.first; it != allStates.second; it++){
            //cout<<it->second<<endl;
            if(it->second == storeCol)
                return false;
        }
    }
    
    //Search in the UPPER LEFT diagonal
    //cout<<"Checking UPPER LEFT diagonal"<<endl;
    storeRow = row;
    storeCol = col;
    for(i = storeRow-1, j=storeCol-1; j >= 0; i--, j--){
        //cout<<"i: "<<i<<" j: "<<j<<endl;
        allTrees = trees.equal_range(i);
        allStates = poppedState.equal_range(i);
        //search = trees.find(i);cout<<"search: "<<search->first<<" "<<search->second<<endl;
        //search1 = poppedState.find(i);cout<<"search1: "<<search1->first<<" "<<search1->second<<endl;
        
        // Break whenever we see a tree
        for(ListIterator it = allTrees.first; it != allTrees.second; it++){
            //cout<<it->second<<endl;
            if(it->second == j){
                breakFlag = 1;
                break;
            }
        }
        
        if(breakFlag == 1){
            breakFlag = 0;
            break;
        }
        
        for(ListIterator it = allStates.first; it != allStates.second; it++){
            //cout<<it->second<<endl;
            if(it->second == j)
                return false;
        }
        
        /*
         if(search != trees.end()){
         if(search->second == j)
         break;
         }
         if(search1 != poppedState.end()){
         if(search1->second == j)
         return false;
         }*/
    }
    
    //Search in the UPPER RIGHT diagonal
    //cout<<"UPPER RIGHT"<<endl;
    storeRow = row;
    storeCol = col;
    for(i = storeRow-1, j=storeCol+1; i >= 0; i--, j++){
        //cout<<"i: "<<i<<" j: "<<j<<endl;
        allTrees = trees.equal_range(i);
        allStates = poppedState.equal_range(i);
        //search = trees.find(i);cout<<"search: "<<search->first<<" "<<search->second<<endl;
        //search1 = poppedState.find(i);cout<<"search1: "<<search1->first<<" "<<search1->second<<endl;
        
        // Break whenever we see a tree
        for(ListIterator it = allTrees.first; it != allTrees.second; it++){
            //cout<<it->second<<endl;
            if(it->second == j){
                breakFlag = 1;
                break;
            }
        }
        
        if(breakFlag == 1){
            breakFlag = 0;
            break;
        }
        
        for(ListIterator it = allStates.first; it != allStates.second; it++){
            //cout<<it->second<<endl;
            if(it->second == j)
                return false;
        }
    }
    
    return true;
}

bool isValidWoTrees(multimap <int, int> poppedState, int row, int col){
    //cout<<"In isValidWoTrees function.."<<endl;
    //cout<<"row: "<<row<<" col: "<<col<<endl;
    //printVecPair(poppedState);
    
    int storeRow, storeCol;
    multimap <int, int>::iterator search;
    int i, j;
    
    //Search in the same column. Upward direction
    storeRow = row;
    storeCol = col;
    for(i = storeRow-1; i >= 0; i--){
        search = poppedState.find(i);
        if(search != poppedState.end()){
            if(search->second == storeCol)
                return false;
        }
    }
    
    //Search in the LEFT UPPER diagonal
    storeRow = row;
    storeCol = col;
    for(i = storeRow-1, j = storeCol-1; j >= 0; i--, j--){
        search = poppedState.find(i);
        if(search != poppedState.end()){
            if(search->second == j)
                return false;
        }
    }
    
    //Search in the RIGHT UPPER diagonal
    storeRow = row;
    storeCol = col;
    for(i = storeRow-1, j = storeCol+1; i >= 0; i--, j++){
        search = poppedState.find(i);
        if(search != poppedState.end()){
            if(search->second == j)
                return false;
        }
    }
    
    return true;
}


void bfs(vector < vector <short> > array, int n, int p){
    //cout<<"In BFS function"<<endl;
    
    multimap <int, int> trees;
    multimap <int, int> state;
    
    //cout <<endl<<"array"<<endl;
    for (int i=0; i<array.size(); i++){
        for (int j=0; j<array[i].size(); j++){
            //cout << array[i][j] << " ";
            if(array[i][j] == 2){
                trees.insert(pair <int, int> (i, j));
            }
        }
        //cout <<  endl;
    }
    //cout<<"n: "<<n<<endl<<"p: "<<p<<endl<<endl;
    
    
    queue < multimap <int, int> > q;
    
    state.insert(make_pair(-1,-1));
    q.push(state);
    //cout<<endl<<"Root node is pushed"<<endl;
    
    multimap <int, int> poppedState, toBePushedState;
    multimap <int, int>::iterator itr;
    int row, col;
    int nodePushedFlag;
    //int lizards = 0;
    
    //********************************* NO TREES ***************************************//
    if(trees.empty()){
        while(!q.empty()){
            //cout<<"Queue Size: "<<q.size()<<endl;
            poppedState = q.front();
            q.pop();
            nodePushedFlag = 0;
            
            if(poppedState.size() == p && poppedState.begin()->first != -1){
                //cout<<endl<<"Solution State: "<<endl;
                //printVecPair(poppedState);
                printSolution(poppedState, n);
                return;
            }
            
            //cout<<endl<<"Popped State: "<<endl;
            //printVecPair(poppedState);
            
            //First time then push all the states
            itr = poppedState.begin();
            if(itr->first == -1){
                //cout<<"Pushing states for the first time"<<endl;
                row = 0; //poppedState[0]->first + 1;
                col = 0; //poppedState[0]->second + 1;
                
                //add all the valid state without conflicting with position of trees
                while(col < n){
                    toBePushedState.clear();
                    //cout<<"row: "<<row<<" col: "<<col<<endl;
                    
                    //Push the state into the queue
                    toBePushedState.insert(make_pair(row, col));
                    q.push(toBePushedState);
                    //printVecPair(toBePushedState);
                    //getchar();
                    col++;
                }
            }
            else{
                //cout<<"Pushing for already pushed states"<<endl;
                row = poppedState.rbegin()->first + 1; //row of the last lizard
                
            putInNextRow:
                if(row >= n)
                    continue;
                
                col = 0; //poppedState.rbegin()->second; //col of the last lizard
                
                //add all the valid state without conflicting with position of trees
                while(col < n){
                    toBePushedState = poppedState;
                    //cout<<"row: "<<row<<" col: "<<col<<endl;
                    
                    //Only push if the lizards are not attacking each other
                    if(isValidWoTrees(poppedState, row, col)){
                        //Push the state into the queue
                        toBePushedState.insert(make_pair(row, col));
                        q.push(toBePushedState);
                        nodePushedFlag = 1;
                        //cout<<"Node ToBePushed"<<endl;
                        //printVecPair(toBePushedState);
                        //getchar();
                    }
                    col++;
                }
                
                if(nodePushedFlag == 0 && row < n){
                    //cout<<"Skipped whole row"<<endl;
                    row = poppedState.rbegin()->first + 2;
                    goto putInNextRow;
                }
            }
        }
        
        
    }
    //********************************* With Trees **************************************//
    else{
        //cout<<"Trees: "<<endl;
        //printVecPair(trees);
        pair<ListIterator, ListIterator> allTrees;
        
        while(!q.empty()){
            //cout<<"Queue Size: "<<q.size()<<endl;
            poppedState = q.front();
            q.pop();
            nodePushedFlag = 0;
            
            if(poppedState.size() == p && poppedState.begin()->first != -1){
                //cout<<endl<<"Solution State: "<<endl;
                //printVecPair(poppedState);
                printSolution(poppedState, trees, n);
                return;
            }
            
            //cout<<endl<<"Popped State: "<<endl;
            //printVecPair(poppedState);
            
            //First time then push all the states
            itr = poppedState.begin();
            
            if(itr->first == -1){
                //cout<<"Pushing states for the first time"<<endl;
                row = 0; //poppedState[0]->first + 1;
                
            allRowIsFullOfTrees:
                col = 0; //poppedState[0]->second + 1;
                
                //add all the valid state without conflicting with position of trees
                while(col < n){
                    toBePushedState.clear();
                    //cout<<"row: "<<row<<" col: "<<col<<endl;
                    
                    // Skip the position of a tree
                    allTrees = trees.equal_range(row);
                    for(ListIterator it = allTrees.first; it != allTrees.second; it++){
                        //cout<<it->second<<endl;
                        if(it->second == col){
                            //cout<<"Found a tree in this place"<<endl;
                            col++;
                            continue;
                        }
                    }
                    
                    if(col == n){
                        row = 1;
                        goto allRowIsFullOfTrees;
                        break;
                    }
                    
                    //Push the state into the queue
                    toBePushedState.insert(make_pair(row, col));
                    q.push(toBePushedState);
                    //printVecPair(toBePushedState);
                    //getchar();
                    col++;
                }
            }
            else{
                //cout<<"Pushing for already pushed states"<<endl;
                
                row = poppedState.rbegin()->first; //row of the last lizard
                col = poppedState.rbegin()->second; //col of the last lizard
                
                col++;
                //add all the valid state without conflicting with position of trees
                while(col < n){
                    toBePushedState = poppedState;
                    //cout<<"row: "<<row<<" col: "<<col<<endl;
                    
                    //Only push if the lizards are not attacking each other
                    if(isValid(poppedState, trees, row, col)){
                        //Push the state into the queue
                        //cout<<"Valid State"<<endl;
                        toBePushedState.insert(make_pair(row, col));
                        q.push(toBePushedState);
                        //printVecPair(toBePushedState);
                        //getchar();
                    }
                    col++;
                }
                
            putInNextRowWithTrees:
                row++;
                col = 0;
                if(row >= n)
                    continue;
                
                //add all the valid state without conflicting with position of trees
                while(col < n){
                    toBePushedState = poppedState;
                    //cout<<"row: "<<row<<" col: "<<col<<endl;
                    
                    /*
                     if(trees.find(row)->second == col){
                     cout<<"Found a tree in this place"<<endl;
                     col++;
                     continue;
                     }*/
                    
                    //Only push if the lizards are not attacking each other
                    if(isValid(poppedState, trees, row, col)){
                        //Push the state into the queue
                        toBePushedState.insert(make_pair(row, col));
                        q.push(toBePushedState);
                        nodePushedFlag = 1;
                        //printVecPair(toBePushedState);
                        //getchar();
                    }
                    col++;
                }
                
                if(nodePushedFlag == 0 && row < n){
                    //cout<<"Skipped whole row"<<endl;
                    //row = poppedState.rbegin()->first + 2;
                    goto putInNextRowWithTrees;
                }
                
                
                
            }
            
            
            
        }
        
    }
    
    
    //cout<<"FAIL"<<endl;
    
    outFile.open("output.txt");
    outFile<<"FAIL"<<endl;
    outFile.close();
    
    return;
}





//*********************************************************************************************//
//********************************* D F S *****************************************************//
//*********************************************************************************************//

void printVec(vector <vector <short> > vec, int n){
    
    outFile.open("output.txt");
    //cout<<"OK"<<endl;
    outFile<<"OK"<<endl;

    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++){
            //cout<<vec[i][j]<<" ";
            outFile<<vec[i][j];
        }
        //cout<<endl;
        outFile<<endl;
    }
    outFile.close();
}

bool DFSsolveWithTrees(vector <vector <short> > array, int n, int p, int lizards, int row, int col){
    
    //cout<<"PrintVec(array): "<<endl;
    //printVec(array, n);
    //cout<<"row: "<<row<<" col: "<<col<<" lizards: "<<lizards<<endl<<endl;
    
    if(lizards == p){
        //cout<<endl;
        printVec(array, n);
        //mySolution(array, n);//to store the vector in a file
        return true;
    }
    
    if(col >= n){
        col = 0;
        row++;
        //cout<<"col: "<<col<<" row: "<<row<<endl;
    }
    
    if(row >= n){
        //cout<<"row == n"<<endl;
        return false;
    }
    
    for(int j=col; j<n; j++){
        //cout<<"j: "<<j;
        
        int a = isAttackingLastLizardWithTrees(array, n, row, j);
        //cout<<"a: "<<a<<endl;
        
        //printVec(array, n);
        //getchar();
        
        if(a == false){
            array[row][j] = 1;
            //getchar();
            
            if(DFSsolveWithTrees(array, n, p, lizards+1, row, j+1))
                return true;
            
            array[row][j] = 0; //don't accept this step
        }
        else{
            if(DFSsolveWithTrees(array, n, p, lizards, row, j+1)) // to backtrack the last step
                return true;
            else{
                return false;
            }
            
        }
    }
    
    
    return false;
}


bool DFSsolveNormal(vector <vector <short> > array, int n, int p, int lizards, int row){
    //printVec(array, n);
    //cout<<"row: "<<row<<" lizards: "<<lizards<<endl<<endl;
    
    if(row >= n or lizards == p){
        //cout<<endl;
        printVec(array, n);
        //mySolution(array, n);//to store the vector in a file
        return true;
    }
    
    for(int col=0; col<n; col++){
        //cout<<"here you go"<<endl;
        int a = isAttackingLastLizardWithoutTrees(array, n, row, col);
        if(a == false){
            array[row][col] = 1;
            
            if(DFSsolveNormal(array, n, p, lizards+1, row+1))
                return true;
            
            array[row][col] = 0; //backtrack this step and try another position
            //lizards--;
        }
    }
    
    return false;
}

bool dfs(vector <vector <short> > vec, int n, int p){
    //cout<<"n: "<<n<<" p: "<<p<<endl;
    
    int hasTree = 0;
    for (int i=0; i<vec.size(); i++){
        for (int j=0; j<vec[i].size(); j++){
            //cout<<vec[i][j]<<" ";
            if(vec[i][j] == 2)
                hasTree = 1;
        }
        //cout<<endl;
    }
    //cout<<"hasTree: "<<hasTree<<endl;
    
    if(hasTree){
        if(DFSsolveWithTrees(vec, n, p, 0, 0, 0) == false){
            outFile.open("output.txt");
            //cout<<"FAIL"<<endl;
            outFile<<"FAIL"<<endl;
            outFile.close();
            return false;
        }
        //printVec(vec, n);
        return true;
    }
    else{
        if(p>n){
            outFile.open("output.txt");
            //cout<<"FAIL"<<endl;
            outFile<<"FAIL"<<endl;
            outFile.close();
            return false;
        }
        //cout<<"No trees are present"<<endl;
        if(DFSsolveNormal(vec, n, p, 0, 0) == false){
            outFile.open("output.txt");
            //cout<<"FAIL"<<endl;
            outFile<<"FAIL"<<endl;
            outFile.close();
            return false;
        }
        //printVec(vec1, n);
        return true;
    }
    
}


bool isAttackingLastLizardWithTrees(vector < vector <short> > array, int n, int row, int col){
    //cout<<"In isAttackingLastLizard function.. checking....."<<endl;
    int storei, storej;
    short tempValue;
    
    //printVec(array, n);
    //cout<<"row: "<<row<<"col: "<<col<<endl;
    
    if(array[row][col] == 2)
        return true;
    
    
    //Check column greater than n
    storei = row;
    storej = col - 1;
    while(storej >= 0){
        tempValue = array[storei][storej--];
        if(tempValue == 1){
            //cout<<"Found 1 in a row"<<endl;
            return true;
        }
        else if(tempValue == 2)//Found tree no more local search needed
            break;
    }
    
    //Check column greater than n
    storei = row - 1;
    storej = col;
    while(storei >= 0){
        tempValue = array[storei--][storej];
        if(tempValue == 1){
            //cout<<"Found 1 in a col"<<endl;
            return true;
        }
        else if(tempValue == 2)//Found tree no more local search needed
            break;
    }
    
    //Check diagonal left upper
    storei = row - 1;
    storej = col - 1;
    while(storei >= 0 && storej >= 0){
        tempValue = array[storei--][storej--];
        if(tempValue == 1){
            //cout<<"Found 1 in LEFT UPPER diagonal"<<endl;
            return true;
        }
        else if(tempValue == 2)
            break;
    }
    
    //Check diagonal right upper
    storei = row - 1;
    storej = col + 1;
    while(storei >= 0 && storej <= n-1){
        tempValue = array[storei--][storej++];
        if(tempValue == 1){
            //cout<<"Found 1 in a UPPER diagonal"<<endl;
            return true;
        }
        else if(tempValue == 2)
            break;
    }
    return false;
    
}


bool isAttackingLastLizardWithoutTrees(vector < vector <short> > array, int n, int row, int col){
    //cout<<"In isAttackingLastLizard function.. checking....."<<endl;
    int storei, storej;
    short tempValue;
    
    //cout<<"row: "<<row<<"col: "<<col<<endl;
    
    //Check column greater than n
    storei = row - 1;
    storej = col;
    while(storei >= 0){
        tempValue = array[storei--][storej];
        if(tempValue == 1){
            //cout<<"Found 1 in a col"<<endl;
            return true;
        }
    }
    
    //Check diagonal left upper
    storei = row - 1;
    storej = col - 1;
    while(storei >= 0 && storej >= 0){
        tempValue = array[storei--][storej--];
        if(tempValue == 1){
            //cout<<"Found 1 in LEFT UPPER diagonal"<<endl;
            return true;
        }
    }
    
    //Check diagonal right upper
    storei = row - 1;
    storej = col + 1;
    while(storei >= 0 && storej <= n-1){
        tempValue = array[storei--][storej++];
        if(tempValue == 1){
            //cout<<"Found 1 in a RIGHT UPPER diagonal"<<endl;
            return true;
        }
    }
    return false;
    
}



//*********************************************************************************************//
//********************************* S A *******************************************************//
//*********************************************************************************************//


int calculateNumAttacks(vector <vector <short> > array, int n){
    //cout << "In calculateNumAttacks function" << endl;
    
    int numAttacks = 0;
    short tempValue;
    int storei, storej;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){//flag-to check killing other lizards' condition
            if(array[i][j]==1){
                //cout<<"i: "<<i<<"j: "<<j<<endl;
                
                //Check row lesser than n
                storei = i;
                storej = j + 1;
                while(storej < n){
                    tempValue = array[i][storej++];
                    if(tempValue == 1){
                        //cout<<"Found 1 in the row"<<endl;
                        numAttacks++;
                    }
                    else if(tempValue == 2)//Found tree no more local search needed
                        break;
                }
                
                //Check column lesser than n
                storei = i + 1;
                storej = j;
                while(storei < n){
                    tempValue = array[storei++][j];
                    if(tempValue == 1){
                        //cout<<"Found 1 in the col"<<endl;
                        numAttacks++;
                    }
                    else if(tempValue == 2)//Found tree no more local search needed
                        break;
                }
                
                //Check diagonals lesser than n,n LOWER DIAGONAL
                storei = i + 1;
                storej = j + 1;
                while(storei < n && storej < n){
                    tempValue = array[storei++][storej++];
                    if(tempValue == 1){
                        //cout<<"Found 1 in the LOWER diagonal"<<endl;
                        numAttacks++;
                    }
                    else if(tempValue == 2)
                        break;
                }
                
                // for UPPER DIAGONAL
                storei = i - 1;
                storej = j + 1;
                while(storei >= 0 && storej < n){
                    tempValue = array[storei--][storej++];
                    if(tempValue == 1){
                        //cout<<"Found 1 in the UPPER diagonal"<<endl;
                        numAttacks++;
                    }
                    else if(tempValue == 2)
                        break;
                }
            }
        }
    }
    
    //cout << "numAttacks" << numAttacks << endl;
    
    return numAttacks;
}

int schedule(int time){//or number of iteration
    int temp;
    int y = time;
    
    //Function 1: Linear
    int m = -1;
    int c = 100;
    temp = (y-c)/m;
    
    return temp;
}


bool accept(float p){
    float r = (double)rand() / (double)RAND_MAX;
    
    //cout<<"random: "<<r<<" prob: "<<p<<endl;
    
    if(r <= p)
        return true;
    else
        return false;
}

vector <vector <short> > initialSolution(vector <vector <short> > vec, int n, int lizards, int option){
    vector <vector <short> > array = vec;
    int row, col;
    
    //At random places
    if(option == 1){
        //srand ( time(NULL) );
        for(int i=0; i<lizards; i++){
            row = rand() % n;
            col = rand() % n;
            
            if(array[row][col]!=1 && array[row][col]!=2)
                array[row][col] = 1;
            else
                i--;
            
            /*
            for(int j=0; j<n; j++){
                for(int k=0; k<n; k++){
                    cout<<array[j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
            */
        }
    }
    
    //At diagonals
    else if(option == 2){
        for(int i=0; i<lizards; i++){
            if(array[i][i]!=1 && array[i][i]!=2)
                array[i][i] = 1;
            else{
                row = rand() % n;
                col = rand() % n;
                
                if(array[row][col] != 1 && array[row][col] != 2)
                    array[row][col] = 1;
                else
                    i--;
            }
            
            /*
            for(int j=0; j<n; j++){
                for(int k=0; k<n; k++){
                    cout<<array[j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
            */
        }
    }
    
    //One Lizard in each row
    else if(option == 3){
        if(lizards <= n){
            //cout<<"Here"<<endl;
            for(int i=0; i<lizards; i++){
                col = rand() % n;
                
                if(array[i][col] != 1 && array[i][col] != 2)
                    array[i][col] = 1;
                else
                    i--;
                
                /*
                for(int j=0; j<n; j++){
                    for(int k=0; k<n; k++){
                        cout<<array[j][k]<<" ";
                    }
                    cout<<endl;
                }
                cout<<endl;
                */
            }
        }
        else{
            for(int i=0; i<n; i++){
                col = rand() % n;
                
                if(array[i][col] != 1 && array[i][col] != 2)
                    array[i][col] = 1;
                else
                    i--;
                
                /*
                for(int j=0; j<n; j++){
                    for(int k=0; k<n; k++){
                        cout<<array[j][k]<<" ";
                    }
                    cout<<endl;
                }
                cout<<endl;
                */
            }
            
            int rem = lizards - n;
            for(int i=0; i<rem; i++){
                row = rand() % n;
                col = rand() % n;
                
                if(array[row][col]!=1 && array[row][col]!=2)
                    array[row][col] = 1;
                else
                    i--;
                
                /*
                for(int j=0; j<n; j++){
                    for(int k=0; k<n; k++){
                        cout<<array[j][k]<<" ";
                    }
                    cout<<endl;
                }
                cout<<endl;
                */
            }

            
            
        }
        
        
        

        
        
    }

    return array;
    
}


vector <vector <short> > successor(vector <vector <short> > array, int n, int p){
    //cout<<"In successor function: "<<endl;
    
    //srand ( time(NULL) );
    int liz = rand() % p + 1;
    //cout<<"liz: "<<liz<<endl;
    int i, j;
    int foundTheLizard = 0;
    
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            //cout<<"i: "<<i<<"j: "<<j<<"liz: "<<liz<<endl;
            if(array[i][j] == 1)
                liz--;
            if(liz == 0){
                array[i][j] = 0;
                foundTheLizard = 1;
                break;
            }
        }
        if(foundTheLizard == 1)
            break;
    }
    
    //cout<<"i: "<<i<<"j: "<<j<<endl;
    
    //array[i][j] = 0;//remove the lizard from this position
    
    int newRandomRow, newRandomCol;
    
tryAgain:
    newRandomRow = rand() % n;
    newRandomCol = rand() % n;
    
    if(array[newRandomRow][newRandomCol] != 1 && array[newRandomRow][newRandomCol] != 2)
        array[newRandomRow][newRandomCol] = 1;
    else
        goto tryAgain;
    
    /*
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            cout<<array[i][j]<<" ";
        }
        cout<<endl;
    }
    */
    //getchar();
    return array;
    
}



void sa(vector <vector <short> > array, int n, int p){
    //cout<<"SA algorithm is running"<<endl;
    
    vector <vector <short> > current, next;
    current = initialSolution(array, n, p, 1);
    
    /*
    for(int j=0; j<n; j++){
        for(int k=0; k<n; k++){
            cout<<current[j][k]<<" ";
        }
        cout<<endl;
    }
    */
    
    int hasTree = 0;
    for (int i=0; i<array.size(); i++){
        for (int j=0; j<array[i].size(); j++){
            //cout<<vec[i][j]<<" ";
            if(array[i][j] == 2)
                hasTree = 1;
        }
        //cout<<endl;
    }
    //cout<<"hasTree: "<<hasTree<<endl;
    
    if(!hasTree){
        if(p>n){
            outFile.open("output.txt");
            //cout<<"FAIL"<<endl;
            outFile<<"FAIL"<<endl;
            outFile.close();
            return;
        }
    }
    
    int attacks, oldAttacks, newAttacks;
    float prob, temp;
    
    //temp = 40000;
    //float schedule = 0.99;
    long t = 2;
    
    time_t timer5 = clock();
    //cout<<CLOCKS_PER_SEC<<endl;
    while((clock()-timer5)/CLOCKS_PER_SEC <= 270){
    //for(int t=2; t<17000000; t++){
        temp = 1 / log (t);
        //temp = temp * schedule;
        //cout<<"Temp: "<<temp<<endl;//<<endl<<"t: "<<t
        
        /*if(temp < 0.00000001){
            //if no lizards are attacking then only return
            return current;
        }*/

        //tryAnotherSuccessor:
        next = successor(current, n, p);
        oldAttacks = calculateNumAttacks(current, n);
        //cout<<"oldAttacks: "<<oldAttacks<<endl;
        newAttacks = calculateNumAttacks(next, n);
        //cout<<"newAttacks: "<<newAttacks<<endl;
        //If we found a state with 0 lizards conflicting, return that state
        if(newAttacks == 0){
            outFile.open("output.txt");
            outFile<<"OK"<<endl;
            for (int i=0; i<next.size(); i++){
                for (int j=0; j<next[i].size(); j++){
                    //cout<<next[i][j]<<" ";
                    outFile<<next[i][j];
                }
                //cout<<endl;
                outFile<<endl;
            }
            outFile.close();
            return;
        }
        //attacks = calculateNumAttacks(next, n) - calculateNumAttacks(current, n);
        
        attacks = newAttacks - oldAttacks;
        //cout<<"Difference of attacks: "<<attacks<<endl;
        if(attacks <= 0){
            //cout<<"New State Accepted without anything"<<endl;
            current = next;
        }
        else{
            prob = exp(-attacks/(float)temp);
            if(accept(prob)){
                //cout<<"New State Accepted"<<endl;
                current = next;
            }
            else{
                //cout<<"State Not Accepted"<<endl;
                //continue;
            }
        }
        //getchar();
        t++;
    }
    
    
    outFile.open("output.txt");
    //cout<<"FAILURE"<<endl;
    outFile<<"FAIL"<<endl;
    outFile.close();
    
    return;
    
}



int main(void){
    //clock_t t;
    //t = clock();
    
    ifstream inFile("input.txt");
    if(inFile.is_open()){
        string algo;
        int a;// to call respective function
        
        if(inFile >> algo){
            if(algo=="BFS"){
                a = 1;
                //cout <<endl<< "BFS should run"<<endl;
            }
            else if(algo == "DFS"){
                a = 2;
                //cout << "DFS Algo running"<<endl;
            }
            else if(algo == "SA"){
                a = 3;
                //cout << "SA Algo running"<<endl;
            }
            else{
                //cout << "FAIL"<<endl;
            }
        }
        
        int n;
        if(inFile >> n){
            //cout << "Square Size: " << n << "x" << n <<endl;
        }
        
        int p;
        if(inFile >> p){
            //cout << "No of lizards: " << p <<endl;
        }
        
        vector< vector <short> > vec;
        vector <short> temp_vec;
        //temp_vec.resize(0);
        
        char ch;
        int elementCount=0;
        while(inFile >> ch){
            if(elementCount<n){
                //cout << ch-'0' << " ";
                temp_vec.push_back(ch-'0');
                elementCount++;
            }
            else{
                //cout << endl;
                vec.push_back(temp_vec);
                temp_vec.resize(0);
                //cout << ch-'0' << " ";
                temp_vec.push_back(ch-'0');
                elementCount = 1;
            }
        }
        vec.push_back(temp_vec);
        temp_vec.resize(0);
        
        int noTreesFlag = 0;
        long placesAvailable = 0;
        
        //cout <<endl<<"Full array"<<endl;
        for (int i=0; i<vec.size(); i++){
            for (int j=0; j<vec[i].size(); j++){
                //cout << vec[i][j] << " ";
                if(vec[i][j] != 2){
                    noTreesFlag = 1;
                    placesAvailable++;
                }
            }
            //cout <<  endl;
        }
        
        if(noTreesFlag == 0 || placesAvailable < p){
            outFile.open("output.txt");
            //cout<<"FAILURE"<<endl;
            outFile<<"FAIL"<<endl;
            outFile.close();
            return 0;
        }
        //cout<<isAttacking(vec, n)<<endl;
        
        if(a==1){
            bfs(vec, n, p);
        }
        else if(a==2){
            dfs(vec, n, p);
        }
        else if(a==3){
            vector <vector <short> > resultSA;
            sa(vec, n, p);
        }
        
        
    }
    
    //t = clock() - t;
    //cout << "Time: " << t <<endl<<endl;
    
    return 0;
}
