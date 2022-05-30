#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

#include "csr.h"

using namespace std;

double TERMINATION_THRESHOLD = 0.0000001;

bool fileExists(string filename) {
    FILE *file = fopen(filename.c_str(), "r");
    if (file) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

template <typename T1, typename T2>
void printFancy(T1 firstArg, T2 secondArg, const int &width, bool reversed = false, string prefix = "") {
    auto arrow = (reversed) ? " -> " : " <- ";

    cout << prefix << left << setw(width) << setfill(' ') << firstArg;
    cout << arrow << secondArg << endl;
}

bool checkTermination(vector<double> &p1, vector<double> &p2, double terminationThreshold = TERMINATION_THRESHOLD) {
    double err = 0.0;

    for (size_t i = 0; i < p1.size(); i++) {
        err += fabs(p1[i] - p2[i]);
    }

    return err < terminationThreshold;
}

double jaccard(const vector<pair<double, int>> &topK1, const vector<pair<double, int>> &topK2) {
    double sum = 0.0;
    double topK = topK1.size();

    if (topK2.size() != topK1.size()) {
        cout << " --- ERROR --- " << endl;
        return 0.0;
    }

    for (int i = 0; i < topK; i++) {
        for (int j = 0; j < topK; j++) {
            if (topK1[i].second == topK2[j].second) {
                sum += 1.0;
            }
        }
    }

    return sum / (topK * 2 - sum);
}

template <class T>
class MaxHeap {
    vector<T> _data;
    int _maxSize;
    int _size;

    int parent(int i) {
        return (i - 1) / 2;
    }

    void heapify(int i, bool downward = false) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = 0;
        if (l < size() && _data[l] > _data[i])
            largest = l;
        else
            largest = i;

        if (r < size() && _data[r] > _data[largest])
            largest = r;

        if (largest != i) {
            std::swap(_data[largest], _data[i]);
            if (!downward)
                heapify(parent(i));
            else
                heapify(largest, true);
        }
    }

   public:
    MaxHeap(int maxSize) {  // Constructor with parameters
        _maxSize = maxSize;
        _data = vector<T>(maxSize);
        _size = 0;
    }

    void push(T &d) {
        if (_size == _maxSize) {
            // min elements in a max heap lies at leaves only.
            auto minItr = min_element(begin(_data) + _size / 2, end(_data));
            auto minPos{minItr - _data.begin()};
            auto min{*minItr};

            if (d > min) {
                _data.at(minPos) = d;
                if (_data[parent(minPos)] > d) {
                    // this is unlikely to happen in our case? as this position is  a leaf?
                    heapify(minPos, true);
                } else
                    heapify(parent(minPos));
            }

            return;
        }

        _data.at(_size++) = d;
        std::push_heap(_data.begin(), _data.begin() + _size);
    }

    T pop() {
        T d = _data.front();
        std::pop_heap(_data.begin(), _data.begin() + _size);
        _size--;
        return d;
    }

    T top() {
        return _data.front();
    }

    int size() const {
        return _size;
    }

    explicit operator vector<T>() const {
        return _data;
    }
};

#endif