#ifndef HITS_H
#define HITS_H

vector<pair<double, int>> getHitsTopK(string filename, int topK) {
    CSR csr = CSR(filename);
    MaxHeap<pair<double, int>> scores(topK);

    

    return (vector<pair<double, int>>)scores;
}

#endif