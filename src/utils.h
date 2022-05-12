#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iomanip>

using namespace std;

template <typename T1, typename T2>
void printFancy(T1 firstArg, T2 secondArg, const int &width, bool reversed = false)
{
    auto arrow = (reversed) ? " => " : " <= ";

    cout << left << setw(width) << setfill(' ') << firstArg;
    cout << arrow << secondArg << endl;
}

template <class T>
class MaxHeap{
    vector<T> _data;
    int _maxSize;
    int _size;

    int parent(int i){
        return (i - 1) / 2;
    }

    void heapify(int i, bool downward = false){
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = 0;
        if (l < size() && _data[l] > _data[i])
            largest = l;
        else
            largest = i;

        if (r < size() && _data[r] > _data[largest])
            largest = r;

        if (largest != i)
        {
            std::swap(_data[largest], _data[i]);
            if (!downward)
                heapify(parent(i));
            else
                heapify(largest, true);
        }
    }

public:
    MaxHeap(int maxSize) { // Constructor with parameters
      _maxSize = maxSize;
      _data = vector<T>(maxSize);
      _size = 0;
    }

    void push(T &d){
        if (_size == fixed_size)
        {
            // min elements in a max heap lies at leaves only.
            auto minItr = std::min_element(begin(_data) + _size / 2, end(_data));
            auto minPos{minItr - _data.begin()};
            auto min{*minItr};

            if (d > min)
            {
                _data.at(minPos) = d;
                if (_data[parent(minPos)] > d)
                {
                    // this is unlikely to happen in our case? as this position is  a leaf?
                    heapify(minPos, true);
                }
                else
                    heapify(parent(minPos));
            }

            return;
        }

        _data.at(_size++) = d;
        std::push_heap(_data.begin(), _data.begin() + _size);
    }

    T pop(){
        T d = _data.front();
        std::pop_heap(_data.begin(), _data.begin() + _size);
        _size--;
        return d;
    }

    T top(){
        return _data.front();
    }

    int size() const{
        return _size;
    }

    explicit operator vector<T>() const { 
        return _data;
    }
};


#endif