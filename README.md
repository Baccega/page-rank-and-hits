# 📃🔍 PageRank and HITS

Optimized implementation of the PageRank algorithm by Larry Page and the HITS algorithm by Jon Kleinberg. 

This script computes the top-k nodes based on the rankings of the two algorithms, adds the in-degree of the node, and plot the Jaccard coefficient between the pairs of nodes.

This project is the assignment for the course **Information Retreival and Web Search 2021/2022**.

See **[Assignment.pdf](Assignment.pdf)** for more details on the assignment. 

The assets are from the **SNAP Datasets** by Jure Leskovec and Andrej Krevl, available [here](http://snap.stanford.edu/data).

## 🔧 Building

```bash
mkdir build
cd build
cmake ..
make
```

## 🕹️ Usage

```
./pagerank-hits [filename] [topK]

Find top-K results of each algorithm in the graph and the Jaccard's coeffiecient.

OPTIONS:

    filename                   The graph to process (default: web-Stanford.txt)
    topK                       Set top-K number (default: 10)
 
```

If you run `./pagerank-hits` without arguments it will run with the default arguments, so it's the same as writing:

```
./pagerank-hits web-Stanford.txt 10
```