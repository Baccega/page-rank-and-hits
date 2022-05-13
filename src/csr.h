#ifndef CSR_H
#define CSR_H

#include <iostream>
#include <vector>

using namespace std;

class CSR {      
  public:        
    // int* index;  
    // int* row;  
    int index [6] = { 0, 2, 0, 1, 1, 2 };
    int row [3] = { 0, 2, 4 };
    int index_size;  
    int row_size;     // Same as n_nodes  
    int n_nodes;  
 
    CSR(string filename) {
      n_nodes = 3;
      row_size = 3;

      index_size = 6;

    }

    ~CSR() {
      n_nodes = 0;
    }


};

#endif