#ifndef CSR_H
#define CSR_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "utils.h"

using namespace std;

class CSR {
   public:
    int *index;
    int *row;
    vector<double> values;
    int csrIndexFileSize;
    int csrRowFileSize;
    int n_nodes;
    int n_edges;
    string mainFilename;
    string sortedFilename;
    string csrRowFilename;
    string csrIndexFilename;

    CSR(string filename, bool transposed = false) {
        mainFilename = "../" + filename;
        if (transposed) {
            sortedFilename = regex_replace(mainFilename, std::regex(".txt"), "-transposed-sorted.txt");
        } else {
            sortedFilename = regex_replace(mainFilename, std::regex(".txt"), "-sorted.txt");
        }
        csrRowFilename = regex_replace(mainFilename, std::regex(".txt"), "-csr-row.txt");
        csrIndexFilename = regex_replace(mainFilename, std::regex(".txt"), "-csr-index.txt");

        if (!fileExists(sortedFilename)) {
            cout << "\t- SORTING DATASET" << endl;
            sortDataset(mainFilename, sortedFilename, transposed);
        } else {
            cout << "\t- SKIPPING SORTING DATASET" << endl;
        }

        int fromNode, toNode;
        int currentRow = 0;
        int elemRow = 0;
        int currentElem = 0;
        int tempRow;

        cout << "\t- COMPUTING CSR START" << endl;

        FILE *mainFile = parseFile(sortedFilename);

        values = vector<double>();

        FILE *indexFile = fopen(csrIndexFilename.c_str(), "w+");
        FILE *rowFile = fopen(csrRowFilename.c_str(), "w+");

        tempRow = 0;
        fwrite(&tempRow, sizeof(int), 1, rowFile);

        while (fscanf(mainFile, "%d%d", &fromNode, &toNode) != EOF) {
            if (fromNode > currentRow) {
                currentElem = currentElem + elemRow;
                for (int k = currentRow + 1; k <= fromNode; k++) {
                    fwrite(&currentElem, sizeof(int), 1, rowFile);
                }
                elemRow = 0;
                currentRow = fromNode;
            }
            values.push_back(1.0);
            csrIndexFileSize++;
            fwrite(&toNode, sizeof(int), 1, indexFile);
            elemRow++;
        }
        currentElem = currentElem + elemRow;
        for (int k = currentRow + 1; k <= n_nodes; k++) {
            fwrite(&currentElem, sizeof(int), 1, rowFile);
        }

        fclose(rowFile);
        fclose(indexFile);
        fclose(mainFile);

        cout << "\t- TMP FILES CREATED" << endl;
        csrRowFileSize = n_nodes + 1;

        // Initialize mmap
        row = openMMap(csrRowFilename, csrRowFileSize);
        index = openMMap(csrIndexFilename, csrIndexFileSize);
    }

    ~CSR() {
        // Release mmap
        cout << "\t- RELEASING MMAP" << endl;
        closeMMap(row, csrRowFileSize);
        closeMMap(index, csrIndexFileSize);
        // Deleting tmp files
        cout << "\t- DELETING TMP FILES" << endl;
        remove(csrRowFilename.c_str());
        remove(csrIndexFilename.c_str());
    }

    void vectorMultiplication(const std::vector<double> &vector, std::vector<double> &destVector) {
        for (int i = 0; i < n_nodes; i++) {
            int start = row[i];
            bool isLastElement = (i == (n_nodes - 1));
            int end = isLastElement ? n_edges : row[i + 1];
            for (int j = start; j < end; j++) {
                destVector[i] += values[j] * vector[index[j]];
            }
        }
    }

    void vectorTransposedMultiplication(const std::vector<double> &vector, std::vector<double> &destVector) {
        for (int i = 0; i < n_nodes; i++) {
            int start = row[i];
            bool isLastElement = (i == (n_nodes - 1));
            int end = isLastElement ? n_edges : row[i + 1];
            for (int j = start; j < end; j++) {
                destVector[index[j]] += values[j] * vector[i];
            }
        }
    }

   private:
    FILE *parseFile(const string &filenameVal) {
        FILE *f = nullptr;
        char character = '#';
        char str[100];

        f = fopen(filenameVal.c_str(), "r");

        if (f == NULL) {
            cout << "Error opening file" << endl;
            exit(1);
        }

        character = getc(f);
        while (character == '#') {
            fgets(str, 100 - 1, f);
            sscanf(str, "%*s %d %*s %d", &n_nodes, &n_edges);
            character = getc(f);
        }
        ungetc(character, f);

        cout << "\t- N_NODES: " << n_nodes << ", N_EDGES: " << n_edges << endl;

        return f;
    }

    int *openMMap(const string &mapFilename, const int &mapPointerSize) {
        int file_row = open(mapFilename.c_str(), O_RDONLY);
        int *pointer = (int *)mmap(0, mapPointerSize * sizeof(int), PROT_READ, MAP_SHARED, file_row, 0);
        close(file_row);
        if (pointer == MAP_FAILED) {
            cerr << "Error with the mapping of the file" << endl;
            exit(1);
        }
        return pointer;
    }

    void closeMMap(int *pointer, int pointerSize) {
        if (munmap(pointer, pointerSize * sizeof(int)) == -1) {
            cerr << "Error un-mmapping the file" << endl;
            exit(1);
        }
    }

    void sortDataset(string mainFilename, string sortedFilename, bool transposed) {
        int fromNode = 0, toNode = 0;
        vector<pair<int, int>> edges = vector<pair<int, int>>();

        auto dest = ofstream(sortedFilename);
        char character;
        char str[100];
        string header;

        FILE *file = fopen(mainFilename.c_str(), "r");

        character = getc(file);
        while (character == '#') {
            fgets(str, 100 - 1, file);
            header += "#" + string(str);
            character = getc(file);
        }
        ungetc(character, file);

        dest << header; 

        while (!feof(file)) {
            fscanf(file, "%d%d", &fromNode, &toNode);
            if (transposed) {
                edges.push_back(pair<int, int>(toNode, fromNode));
            } else {
                edges.push_back(pair<int, int>(fromNode, toNode));
            }
        }
        fclose(file);

        std::sort(edges.begin(), edges.end());
        for (const auto &edge : edges) {
            dest << get<0>(edge) << "   " << get<1>(edge) << endl;
        }
        dest.close();
    }
};

#endif