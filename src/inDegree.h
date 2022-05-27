#ifndef INDEGREE_H
#define INDEGREE_H

#include <map>
#include <queue>
#include <string>
#include <vector>

#include "csr.h"
#include "utils.h"

using namespace std;

vector<pair<double, int>> getOutDegreeTopK(const CSR& csr, int topK) {
    MaxHeap<pair<double, int>> scores(topK);

    for (int i = 0; i < csr.n_nodes; i++) {
        bool isLastElement = (i == (csr.n_nodes - 1));
        int nextElement = isLastElement ? csr.n_edges : csr.row[i + 1];
        double score = nextElement - csr.row[i];
        auto pair = make_pair(score / csr.n_nodes, i);
        scores.push(pair);
    };

    return (vector<pair<double, int>>)scores;
}

vector<pair<double, int>> getInDegreeTopK(string filename, int topK) {
    CSR csr = CSR(filename);
    MaxHeap<pair<double, int>> scores(topK);
    map<int, int> tmpMap;

    for (int i = 0; i < csr.n_edges; i++) {
        if (!tmpMap[csr.index[i]]) {
            tmpMap[csr.index[i]] = 0;
        }
        tmpMap[csr.index[i]]++;
    };

    for (auto iter = tmpMap.begin(); iter != tmpMap.end(); iter++) {
        double score = (double) (*iter).second / csr.n_nodes;
        auto pair = make_pair(score, (*iter).first);
        scores.push(pair);
    }

    return (vector<pair<double, int>>)scores;
}

#endif