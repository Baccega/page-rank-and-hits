Ho scelto di usare `pair<double, int>` invece della piú intuitiva `pair<int, double>` perché di default il confronto tra pairs utilizza il primo valore, quindi nel mio caso mettendo prima il double (lo score) posso fare i confronti necessari per l'heap nella maniera piú semplice possibile.




```
PageRank - Hits
------
TopK                 <- 20
Damping Factor       <- 0.85
Filename             <- assets/web-NotreDame.txt
------

- PageRank
        - SKIPPING SORTING DATASET
        - COMPUTING CSR START
        - N_NODES: 325729, N_EDGES: 1497134
        - TMP FILES CREATED
        - STOCHASTIZATION
        - PAGERANK
        - Converged after 65 iterations
        - SORTING RESULTS
        - RELEASING MMAP
        - DELETING TMP FILES
        - PageRank top 20 nodes:
          1963       -> 0.00206908
          0          -> 0.00206635
          212843     -> 0.00143804
          10336      -> 0.0018818
          124802     -> 0.00121743
          191267     -> 0.00100891
          1973       -> 0.000872016
          12129      -> 0.0010247
          142732     -> 0.000861411
          32830      -> 0.00100536
          31331      -> 0.000690894
          3451       -> 0.000760987
          140170     -> 0.000535881
          149039     -> 0.000663305
          226950     -> 0.000456993
          81878      -> 0.000511944
          83606      -> 0.000904845
          143218     -> 0.000791845
          12838      -> 0.000516341
          24823      -> 0.000821949
- HITS
        - SKIPPING SORTING DATASET
        - COMPUTING CSR START
        - N_NODES: 325729, N_EDGES: 1497134
        - TMP FILES CREATED
        - Forced termination at 201 iterations
        - SORTING RESULTS
        - RELEASING MMAP
        - DELETING TMP FILES
        - Hits top 20 nodes:
          12129      -> 0.00653519
          199031     -> 0.00216741
          235904     -> 0.00216741
          193592     -> 0.00216253
          199029     -> 0.000736813
          151241     -> 0.00216253
          155590     -> 0.00216253
          151238     -> 0.000735186
          198328     -> 0.00216253
          155587     -> 0.000735185
          236029     -> 0.00072486
          193717     -> 0.00072326
          199030     -> 0.000736847
          236095     -> 0.000724956
          151239     -> 0.000735186
          155588     -> 0.000735183
          155589     -> 0.000735122
          151240     -> 0.000735122
          199028     -> 0.000736813
          235963     -> 0.00072486
- InDegree
        - SKIPPING SORTING DATASET
        - COMPUTING CSR START
        - N_NODES: 325729, N_EDGES: 1497134
        - TMP FILES CREATED
        - RELEASING MMAP
        - DELETING TMP FILES
        - InDegree top 20 nodes:
          12129      -> 0.0329139
          0          -> 0.0233906
          199031     -> 0.0109815
          124802     -> 0.0215701
          31331      -> 0.0132012
          198328     -> 0.0109355
          155590     -> 0.0109385
          12838      -> 0.00665584
          151241     -> 0.0109662
          140170     -> 0.0131367
          235904     -> 0.0109785
          24823      -> 0.00439015
          3451       -> 0.00388667
          191267     -> 0.00720538
          46468      -> 0.00514231
          142732     -> 0.00580544
          143218     -> 0.00532344
          1973       -> 0.00605411
          81878      -> 0.00647164
          193592     -> 0.0109631
- Jaccard
        - PageRank-HITS: 0.025641
        - PageRank-InDegree: 0.481481
        - HITS-InDegree: 0.212121
------
All done!
------
Total time elapsed [s]         -> 14.2354
------
PageRank time elapsed [s]      -> 3.95047
HITS time elapsed [s]          -> 7.4146
InDegree time elapsed [s]      -> 2.87027
Jaccard time elapsed [us]      -> 69.58
```