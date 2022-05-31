#ifndef HITS_H
#define HITS_H

#include <vector>

#include "csr.h"
#include "utils.h"

using namespace std;

int HITS_LIMIT_ITERATION = 200;

vector<pair<double, int>> getHitsTopK(string filename, int topK) {
    bool loop;
    double totalSum;
    int iterations = 0;
    MaxHeap<pair<double, int>> scores(topK);

    // Get transposed csr matrix 
    CSR csr = CSR(filename, true);
    

    // HITS algorithm (power iteration)
    cout << "\t- HITS" << endl;

    // Initial authority scores
    vector<double> authorityScores = vector<double>(csr.n_nodes, 1.0);
    do {
        loop = true;
        totalSum = 0.0;

        vector<double> newAuthorityScores = vector<double>(csr.n_nodes, 0.0);

        // New authority scores (a_new = L^T * h)
        csr.vectorMultiplication(authorityScores, newAuthorityScores);

        // Normalization
        cout << "\t- NORMALIZATION" << endl;
        for (int i = 0; i < csr.n_nodes; i++) {
            totalSum += newAuthorityScores[i];
        }
        for (int i = 0; i < csr.n_nodes; i++) {
            newAuthorityScores[i] = newAuthorityScores[i] / totalSum;
        }

        // Termination conditions
        if (checkTermination(authorityScores, newAuthorityScores)) {
            cout << "\t- Converged after " << iterations << " iterations" << endl;
            loop = false;
        } else if (iterations > HITS_LIMIT_ITERATION) {
            cout << "\t- Forced termination at " << iterations << " iterations" << endl;
            loop = false;
        }

        // Update authorityScores for next iteration
        for (int i = 0; i < csr.n_nodes; i++) {
            authorityScores[i] = newAuthorityScores[i];
        }

        iterations++;
    } while (loop);

    // Find top K nodes using a MaxHeap
    cout << "\t- SORTING RESULTS" << endl;
    for (int i = 0; i < csr.n_nodes; i++) {
        auto pair = make_pair(authorityScores[i], i);
        scores.push(pair);
    }

    return (vector<pair<double, int>>)scores;
}

#endif