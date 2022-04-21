#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iomanip>

using namespace std;

template<typename T1,typename T2> void printFancy(T1 firstArg,T2 secondArg, const int& width, bool reversed = false){
    auto arrow = (reversed)? " => " : " <= "; 
    
    cout << left << setw(width) << setfill(' ') << firstArg;
    cout << arrow << secondArg << endl;
}

#endif