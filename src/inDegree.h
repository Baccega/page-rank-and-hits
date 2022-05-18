#ifndef INDEGREE_H
#define INDEGREE_H

#include <vector>
#include <map>
#include <string>
#include <queue>
#include "utils.h"
#include "csr.h"

using namespace std;

vector<pair<double, int>> getOutDegreeTopK(const CSR& csr, int topK){
    MaxHeap<pair<double, int>> scores(topK);

    for (int i = 0; i < csr.n_nodes ; i++){
        // Is last element? then: csr.n_edges; else: csr.row[i + 1]
        int nextElement = (i == (csr.n_nodes - 1))? csr.n_edges : csr.row[i + 1];
        double score = nextElement - csr.row[i];
        auto pair = make_pair(score / csr.n_nodes, i );
        scores.push(pair);
    };

    return (vector<pair<double, int>>) scores;
}

vector<pair<double, int>> getInDegreeTopK(const CSR& csr, int topK){
    MaxHeap<pair<double, int>> scores(topK);
    map<int, int> tmpMap;

    for (int i = 0; i < csr.n_edges ; i++){
        if(!tmpMap[csr.row[i]]){
            tmpMap[csr.row[i]] = 0;
        }
        tmpMap[csr.row[i]]++;
    };

    for (auto iter = tmpMap.begin(); iter != tmpMap.end(); iter++)
    {
        double score = (*iter).second / csr.n_nodes;
        auto pair = make_pair(score, (*iter).first );
        scores.push(pair);
    }

    return (vector<pair<double, int>>) scores;
}

#endif