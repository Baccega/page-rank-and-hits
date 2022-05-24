#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>

#include "csr.h"

using namespace std;

vector<pair<double, int>> getPageRankTopK(const CSR& csr, int topK) {
    int iterations = 0;
    MaxHeap<pair<double, int>> scores(topK);

    // TODO Fix dangling nodes

    // TODO Normalize, making the matrix stochastic



    // TODO Teleportation matrix 



    // Markov matrix
    // TODO Final Matrix after removing dangling nodes and adding teleportation


    // Initial probability distribution
    vector<double> probabilityDistribution = vector<double>(csr.n_nodes, 1.0 / csr.n_nodes);

    // TODO Doing pagerank

    cout << "Converged after " << iterations << " iterations" << endl;

    // Find top K nodes using a MaxHeap 
    for (int i = 0; i < csr.n_nodes; i++)
    {
        auto pair = make_pair(probabilityDistribution[i], i);
        scores.push(pair);
    }
    
    return (vector<pair<double, int>>) scores;
}

#endif