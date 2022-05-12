#ifndef CSR_H
#define CSR_H

#include <iostream>
#include <vector>

using namespace std;

class CSR {      
  public:        
    int* value;
    int* index;  
    int* row;  
    int value_size;
    int index_size;  
    int row_size;  
    int N_NODES;  

    CSR(string filename) {
      N_NODES = 10;
    }

    ~CSR() {
      N_NODES = 0;
    }


};

#endif