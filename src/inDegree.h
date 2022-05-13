#ifndef INDEGREE_H
#define INDEGREE_H

#include <vector>
#include <queue>
#include "utils.h"
#include "csr.h"

using namespace std;



vector<pair<int, double>> getInDegreeTopK(const CSR& csr, int topK){
    // int *row_pointer = Utilities::openMMap(csr.getMapRowPtrFilename(), csr.getRowPointerSize());
    MaxHeap<pair<int, double>> scores(topK);

    for (int i = 0; i < csr.n_nodes ; i++){
        // Is last element? then: csr.n_nodes; else: csr.row[i + 1]
        int nextElement = (i == (csr.n_nodes - 1))? csr.index_size : csr.row[i + 1];
        double score = nextElement - csr.row[i];
        auto pair = make_pair(i, score / csr.n_nodes);
        scores.push(pair);
    };

    return (vector<pair<int, double>>) scores;
}

#endif