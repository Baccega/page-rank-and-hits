#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>

#include "csr.h"

using namespace std;

int PAGERANK_LIMIT_ITERATION = 1000;

void stochastization(CSR& csr) {
    vector<int> outDegrees = vector<int>(csr.n_nodes, 0);
    int currentIndex = 0;

    for (int i = 0; i < csr.n_nodes; i++) {
        if (csr.row[i + 1] != 0) {
            bool isLastElement = (i == (csr.n_nodes - 1));
            int nextElement = isLastElement ? csr.n_edges : csr.row[i + 1];
            outDegrees[i] = nextElement - csr.row[i];
        }
    };

    for (int i = 0; i < csr.n_nodes; i++) {
        bool isLastElement = (i == (csr.n_nodes - 1));
        int nextElement = isLastElement ? csr.n_edges : csr.row[i + 1];
        int rowElement = nextElement - csr.row[i];

        for (int j = 0; j < rowElement; j++){
            csr.values[currentIndex] = csr.values[currentIndex] / outDegrees[i];
            currentIndex++;
        }
        
    };

}

vector<pair<double, int>> getPageRankTopK(string filename, int topK, double dampingFactor) {
    CSR csr = CSR(filename);
    int iterations = 0;
    bool loop;
    MaxHeap<pair<double, int>> scores(topK);

    // Normalize, making the matrix stochastic
    cout << "\t- STOCHASTIZATION" << endl;
    stochastization(csr);

    // PageRank algorithm (power iteration)
    cout << "\t- PAGERANK" << endl;

    // Initial probability distribution
    vector<double> p = vector<double>(csr.n_nodes, 1.0 / csr.n_nodes);
    do {
        loop = true;

        vector<double> p_new = vector<double>(csr.n_nodes, 0.0);

        csr.vectorTransposedMultiplication(p, p_new);

        // (p_new = d * (A^T * p) + (1 - d) / N )
        for (int i = 0; i < csr.n_nodes; i++) {
            p_new[i] = dampingFactor * p_new[i] + (1.0 - dampingFactor) / csr.n_nodes;
        }

        // Termination conditions
        if (checkTermination(p, p_new)) {
            cout << "\t- Converged after " << iterations << " iterations" << endl;
            loop = false;
        } else if (iterations > PAGERANK_LIMIT_ITERATION) {
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
        auto pair = make_pair(p[i], i);
        scores.push(pair);
    }

    return (vector<pair<double, int>>)scores;
}

#endif