#ifndef INDEGREE_H
#define INDEGREE_H

#include <vector>
#include <queue>
#include "csr.h"

using namespace std;

vector<pair<int, double>> getInDegreeTopK(CSR csr, int topK)
{

    // int *row_pointer = Utilities::openMMap(csr.getMapRowPtrFilename(), csr.getRowPointerSize());
    double score = 0.0;

    MaxHeap<pair<int, double>> scores(topK);

    for (int i = 0; i < csr.N_NODES; i++){
        score = csr.row[i + 1] - csr.row[i];
        auto pair = make_pair(i, score / csr.N_NODES);
        scores.push(pair);
    };

    return (vector<pair<int, double>>) scores;
}

#endif