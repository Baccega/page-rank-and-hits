#include <chrono>
#include <iostream>
#include <vector>

#include "csr.h"
#include "hits.h"
#include "inDegree.h"
#include "pagerank.h"
#include "utils.h"

using namespace std;

int main(int argc, char *argv[]) {
    int topk = 10;
    string filename = "assets/web-Stanford.txt";

    if (argc != 1) {
        filename = argv[1];
        topk = atoi(argv[2]);
    }
    cout << "PageRank - Hits" << endl
         << "------" << endl;
    printFancy("TopK", topk, 15);
    printFancy("Filename", filename, 15);
    cout << "------" << endl
         << endl;

    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    // Do PageRank
    cout << "- PageRank" << endl;

    vector<pair<double, int>> pageRankTopK = getPageRankTopK(filename, topk);

    auto endPageRank = std::chrono::high_resolution_clock::now();

    cout << "\t- PageRank top 5 nodes:" << endl;
    printFancy(pageRankTopK[0].second, pageRankTopK[0].first, 10, true);
    printFancy(pageRankTopK[1].second, pageRankTopK[1].first, 10, true);
    printFancy(pageRankTopK[2].second, pageRankTopK[2].first, 10, true);
    printFancy(pageRankTopK[3].second, pageRankTopK[2].first, 10, true);
    printFancy(pageRankTopK[4].second, pageRankTopK[2].first, 10, true);

    // Do HITS
    cout << "- HITS" << endl;

    auto endHits = std::chrono::high_resolution_clock::now();

    // Do In Degree
    cout << "- InDegree" << endl;

    vector<pair<double, int>> inDegreeTopK = getInDegreeTopK(filename, topk);

    cout << "\t- InDegree top 5 nodes:" << endl;
    printFancy(inDegreeTopK[0].second, inDegreeTopK[0].first, 10, true);
    printFancy(inDegreeTopK[1].second, inDegreeTopK[1].first, 10, true);
    printFancy(inDegreeTopK[2].second, inDegreeTopK[2].first, 10, true);
    printFancy(inDegreeTopK[3].second, inDegreeTopK[2].first, 10, true);
    printFancy(inDegreeTopK[4].second, inDegreeTopK[2].first, 10, true);

    auto endInDegree = std::chrono::high_resolution_clock::now();

    // Do Jaccard
    cout << "- Jaccard" << endl;

//     cout << "\t- PageRank-HITS: " << jaccard(pageRankTopK, hitsTopK) << endl;
    cout << "\t- PageRank-InDegree: " << jaccard(pageRankTopK, inDegreeTopK) << endl;
//     cout << "\t- HITS-InDegree: " << jaccard(hitsTopK, inDegreeTopK) << endl;

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsedTotal = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    auto elapsedPageRank = std::chrono::duration_cast<std::chrono::nanoseconds>(endPageRank - begin).count();
    auto elapsedHits = std::chrono::duration_cast<std::chrono::nanoseconds>(endHits - endPageRank).count();
    auto elapsedInDegree = std::chrono::duration_cast<std::chrono::nanoseconds>(endInDegree - endHits).count();
    auto elapsedJaccard = std::chrono::duration_cast<std::chrono::nanoseconds>(end - endInDegree).count();

    cout << "All done!" << endl
         << "------" << endl;

    printFancy("Total time elapsed [ns]", elapsedTotal, 40, true);
    printFancy("PageRank time elapsed [ns]", elapsedPageRank, 40, true);
    printFancy("HITS time elapsed [ns]", elapsedHits, 40, true);
    printFancy("InDegree time elapsed [ns]", elapsedInDegree, 40, true);
    printFancy("Jaccard time elapsed [ns]", elapsedJaccard, 40, true);

    return 0;
}