#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iomanip>

using namespace std;

template<typename T> void printFancy(string header,T t, const int& width){
    cout << left << setw(width) << setfill(' ') << t;
    cout << "<= " <<header << endl;
}

#endif