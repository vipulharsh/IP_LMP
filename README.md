# IP_LMP
Computes optimal number of longest matching prefix forwarding rules corresponding to (IP, output port) type forwarding entries.

Compile: make

Run a small test program: make test

Sample run:

    ./genRoutingTable < graph1.edgelist > routingEntries.out

    ./IP_lmp < routingEntries.out



Description of programs:

    (a) IP_longest_match_prefix.cpp: Program to compute the compressed set of longest prefix match forwarding rules. A sample input file (IP_lmp_small1.in) has been provided. 

    (b) genRoutingTable.cpp: Assigns IP addresses to nodes in a graph in a BFS order, then outputs a set of (IP address, output port) type forwarding entries at node 0. The output port is decided as per the next hop in the shortest path to the destination. The output of this program can be fed to the program above.

    (c) trie.cpp: Implementation of a trie data structure. It also implements a dynamic programming algorithm to find the optimal number of entries.

    (d) utils.cpp: General utility functions for IP addresses string parsing

Contact: For any questions, send email to vipulharsh.iit@gmail.com
