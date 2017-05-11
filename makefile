SHELL = /bin/bash

CC=g++ -O3 --std=c++11

all:  genRoutingTable IP_lmp

#Computes longest matching prefixes from IP addresses and interfaces
IP_lmp:  IP_longest_match_prefix.cpp utils.o trie.o
		$(CC) trie.o utils.o -o IP_lmp IP_longest_match_prefix.cpp 

#Computes IP addresses and their interfaces, which can be fed
#               as input to IP_lmp
genRoutingTable: genRoutingTable.cpp Graph.h 
		$(CC) -o genRoutingTable genRoutingTable.cpp 

trie.o: trie.cpp defs.h
		$(CC) -c trie.cpp

utils.o: utils.cpp defs.h
		$(CC) -c utils.cpp

test: IP_lmp
		./IP_lmp < IP_lmp_small1.in

clean:
	rm -f genRoutingTable IP_lmp trie.o utils.o
