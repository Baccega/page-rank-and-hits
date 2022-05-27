#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>

#include "csr.h"

using namespace std;

float DAMPING_FACTOR = 0.85;

void stochastization(CSR& csr) {
    vector<int> outDegrees = vector<int>(csr.n_nodes, 0);

    for (int i = 0; i < csr.n_nodes; i++) {
        bool isLastElement = (i == (csr.n_nodes - 1));
        int nextElement = isLastElement ? csr.n_edges : csr.row[i + 1];
        outDegrees[i] = nextElement - csr.row[i];
    };

    for (int i = 0; i < csr.n_nodes; i++) {
        if (outDegrees[i] != 0) {
            csr.values[i] = csr.values[i] / outDegrees[i];
        }
    }
}

vector<pair<double, int>> getPageRankTopK(string filename, int topK) {
    CSR csr = CSR(filename);
    int iterations = 0;
    bool loop = false;
    MaxHeap<pair<double, int>> scores(topK);

    // Normalize, making the matrix stochastic
    cout << "\t- STOCHASTIZATION" << endl;
    stochastization(csr);

    // PageRank algorithm
    vector<double> probabilityDistribution = vector<double>(csr.n_nodes, csr.n_nodes);
    do {
        loop = false;
        int rowElement = 0;
        int currentCol = 0;
        vector<double> newProbabilityDistribution = vector<double>(csr.n_nodes, 0.0);

        for (int i = 0; i < csr.n_nodes; i++) {
            bool isLastElement = (i == (csr.n_nodes - 1));
            rowElement = isLastElement ? csr.n_edges - csr.row[i] : csr.row[i + 1] - csr.row[i];
            for (int j = 0; j < rowElement; j++) {
                newProbabilityDistribution[csr.index[currentCol]] += csr.values[currentCol] * probabilityDistribution[i];
                currentCol++;
            }
        }
        for (int i = 0; i < csr.n_nodes; i++) {
            newProbabilityDistribution[i] = (DAMPING_FACTOR * newProbabilityDistribution[i] + (1.0 - DAMPING_FACTOR)) / csr.n_nodes;
        }

        if (checkTermination(probabilityDistribution, newProbabilityDistribution)) {
            loop = true;
        }

        for (int i = 0; i < csr.n_nodes; i++) {
            probabilityDistribution[i] = newProbabilityDistribution[i];
        }

        iterations++;
    } while (loop);

    cout << "\t- Converged after " << iterations << " iterations" << endl;

    // Find top K nodes using a MaxHeap
    for (int i = 0; i < csr.n_nodes; i++) {
        auto pair = make_pair(probabilityDistribution[i], i + 1);
        scores.push(pair);
    }

    return (vector<pair<double, int>>)scores;
}

#endif