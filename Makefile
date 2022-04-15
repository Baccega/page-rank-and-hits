
output: main.o hits.o pagerank.o
	g++ main.o hits.o pagerank.o -o output

main.o: src/main.cpp
	g++ -c src/main.cpp

hits.o: src/hits.cpp src/hits.h
	g++ -c src/hits.cpp

pagerank.o: src/pagerank.cpp src/pagerank.h
	g++ -c src/pagerank.cpp

clean: 
	rm *.o output
