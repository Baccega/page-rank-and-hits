#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "csr.h"
#include "hits.h"
#include "inDegree.h"
#include "pagerank.h"
#include "utils.h"

using namespace std;

int main(int argc, char *argv[]) {
    int topK = 20;
	float dampingFactor = 0.85;
    string filename = "assets/web-NotreDame.txt";

    if (argc != 1) {
        filename = argv[1];
        topK = atoi(argv[2]);
        dampingFactor = atoi(argv[3]);
    }
    cout << "PageRank - Hits" << endl
         << "------" << endl;
    printFancy("TopK", topK, 20);
    printFancy("Damping Factor", dampingFactor, 20);
    printFancy("Filename", filename, 20);
    cout << "------" << endl
         << endl;

    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    // Do PageRank
    cout << "- PageRank" << endl;

    vector<pair<double, int>> pageRankTopK = getPageRankTopK(filename, topK, dampingFactor);

    auto endPageRank = std::chrono::high_resolution_clock::now();

    cout << "\t- PageRank top " << topK << " nodes:" << endl;
    for (int i = 0; i < topK; i++) {
        printFancy(pageRankTopK[i].second, pageRankTopK[i].first, 10, true, "\t  ");
    }

    // Do HITS
    cout << "- HITS" << endl;

    vector<pair<double, int>> hitsTopK = getHitsTopK(filename, topK);

    auto endHits = std::chrono::high_resolution_clock::now();

    cout << "\t- Hits top " << topK << " nodes:" << endl;
    for (int i = 0; i < topK; i++) {
        printFancy(hitsTopK[i].second, hitsTopK[i].first, 10, true, "\t  ");
    }

    // Do In Degree
    cout << "- InDegree" << endl;

    vector<pair<double, int>> inDegreeTopK = getInDegreeTopK(filename, topK);

    cout << "\t- InDegree top " << topK << " nodes:" << endl;
    for (int i = 0; i < topK; i++) {
        printFancy(inDegreeTopK[i].second, inDegreeTopK[i].first, 10, true, "\t  ");
    }

    auto endInDegree = std::chrono::high_resolution_clock::now();

    // Do Jaccard
    cout << "- Jaccard" << endl;

    cout << "\t- PageRank-HITS: " << jaccard(pageRankTopK, hitsTopK) << endl;
    cout << "\t- PageRank-InDegree: " << jaccard(pageRankTopK, inDegreeTopK) << endl;
    cout << "\t- HITS-InDegree: " << jaccard(hitsTopK, inDegreeTopK) << endl;

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsedTotal = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    auto elapsedPageRank = std::chrono::duration_cast<std::chrono::nanoseconds>(endPageRank - begin).count();
    auto elapsedHits = std::chrono::duration_cast<std::chrono::nanoseconds>(endHits - endPageRank).count();
    auto elapsedInDegree = std::chrono::duration_cast<std::chrono::nanoseconds>(endInDegree - endHits).count();
    auto elapsedJaccard = std::chrono::duration_cast<std::chrono::nanoseconds>(end - endInDegree).count();

    cout << "------" << endl
         << "All done!" << endl
         << "------" << endl;

    printFancy("Total time elapsed [s]", (double)elapsedTotal / 100000000, 30, true);
    cout << "------" << endl;
    printFancy("PageRank time elapsed [s]", (double)elapsedPageRank / 100000000, 30, true);
    printFancy("HITS time elapsed [s]", (double)elapsedHits / 100000000, 30, true);
    printFancy("InDegree time elapsed [s]", (double)elapsedInDegree / 100000000, 30, true);
    printFancy("Jaccard time elapsed [us]", (double)elapsedJaccard / 100, 30, true);

    return 0;
}