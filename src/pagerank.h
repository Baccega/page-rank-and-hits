#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>

#include "csr.h"

using namespace std;

float DAMPING_FACTOR = 0.85;
int LIMIT_ITERATION = 1000;

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
    bool loop;
    MaxHeap<pair<double, int>> scores(topK);

    // Normalize, making the matrix stochastic
    cout << "\t- STOCHASTIZATION" << endl;
    stochastization(csr);

    // PageRank algorithm
    cout << "\t- PAGERANK" << endl;

    // Initial probability distribution
    vector<double> p = vector<double>(csr.n_nodes, 1.0 / csr.n_nodes);
    do {
        loop = true;
        int currentRow = 0;
        int currentIndex = 0;

        vector<double> p_new = vector<double>(csr.n_nodes, 0.0);
        // Populate the new probability distribution (p_new = p)
        for (int i = 0; i < csr.n_nodes; i++) {
            bool isLastElement = (i == (csr.n_nodes - 1));
            currentRow = isLastElement ? csr.n_edges - csr.row[i] : csr.row[i + 1] - csr.row[i];
            for (int j = 0; j < currentRow; j++) {
                p_new[csr.index[currentIndex]] += csr.values[currentIndex] * p[i];
                currentIndex++;
            }
        }
        // (p * M)
        for (int i = 0; i < csr.n_nodes; i++) {
            p_new[i] = DAMPING_FACTOR * p_new[i] + ((1.0 - DAMPING_FACTOR) / csr.n_nodes);
        }

        // Termination conditions
        if (checkTermination(p, p_new)) {
            cout << "\t- Converged after " << iterations << " iterations" << endl;
            loop = false;
        } else if (iterations > LIMIT_ITERATION) {
            cout << "\t- Forced termination at " << iterations << " iterations" << endl;
            loop = false;
        }

        // Update p for next iteration
        for (int i = 0; i < csr.n_nodes; i++) {
            p[i] = p_new[i];
        }

        iterations++;
    } while (loop);

    // Find top K nodes using a MaxHeap
    cout << "\t- SORTING RESULTS" << endl;
    for (int i = 0; i < csr.n_nodes; i++) {
        auto pair = make_pair(p[i], i + 1);
        cout << "\t- PAIR MADE " << i << ": " << pair.first << endl;
        scores.push(pair);
    }

    return (vector<pair<double, int>>)scores;
}

#endif