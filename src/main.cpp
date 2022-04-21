#include <iostream>
#include <chrono>
#include "hits.h"
#include "pagerank.h"
#include "utils.h"

using namespace std;


int main(int argc, char *argv[]){
    int topk = 10;
    string filename = "web-Stanford.txt";
    
    if(argc != 1){
        filename = argv[1];
        topk = atoi(argv[2]);
    }
    cout << "PageRank - Hits" << endl << "------" << endl;
    printFancy("TopK", topk, 25);
    printFancy("Filename", filename, 25);
    cout << "------" << endl << endl;

    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    // Generate transposed graph if required
    cout << "- Generating transposed graph" << endl;

    auto endTransposed = std::chrono::high_resolution_clock::now();

    // Do PageRank
    cout << "- PageRank" << endl;

    auto endPageRank = std::chrono::high_resolution_clock::now();

    // Do HITS
    cout << "- HITS" << endl;

    auto endHits = std::chrono::high_resolution_clock::now();
    
    // Do In Degree
    cout << "- InDegree" << endl;

    auto endInDegree = std::chrono::high_resolution_clock::now();
    
    // Do Jaccard
    cout << "- Jaccard" << endl << endl;
    

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsedTotal = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    auto elapsedGraph = std::chrono::duration_cast<std::chrono::nanoseconds>(endTransposed - begin).count();
    auto elapsedPageRank = std::chrono::duration_cast<std::chrono::nanoseconds>(endPageRank - endTransposed).count();
    auto elapsedHits = std::chrono::duration_cast<std::chrono::nanoseconds>(endHits - endPageRank).count();
    auto elapsedInDegree = std::chrono::duration_cast<std::chrono::nanoseconds>(endInDegree - endHits).count();
    auto elapsedJaccard = std::chrono::duration_cast<std::chrono::nanoseconds>(end - endInDegree).count();

    cout << "All done!" << endl << "------" << endl; 
    
    printFancy("Total time elapsed [ns]", elapsedTotal, 8);
    printFancy("Transposed graph time elapsed [ns]", elapsedGraph, 8);
    printFancy("PageRank time elapsed [ns]", elapsedPageRank, 8);
    printFancy("HITS time elapsed [ns]", elapsedHits, 8);
    printFancy("InDegree time elapsed [ns]", elapsedInDegree, 8);
    printFancy("Jaccard time elapsed [ns]", elapsedJaccard, 8);

    return 0;
}