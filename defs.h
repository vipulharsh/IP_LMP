#ifndef __TRIE_H__
#define __TRIE_H__

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <cstdio>
#include <assert.h>
#include <string.h>
#include <climits>
using namespace std;

#define NCHARS 256
#define CHAROFFSET 0

extern set<std::string> allInterfaces;

/** General Utility functions **/

//convert decimal string to binary
string DecToBin(string dec);

//convert binary string to decimal
string BinToDec(string bin);

//add dots after every byte in a binary IP address
string addDots(string binIP);

//Converts binary IP address into decimal IP addresses 
//adds dots
string BinToDecIP(string ip_v);

//Converts decimal IP address into binary strings
//removes dots
string DecToBinIP(string ip_v);

//get interface from a string of the form ip:interface
string getInterface(string routingEntry);

//get IP from a string of the form ip:interface
string getIP(string routingEntry);

//add characters at the end
string pad_suffix(string s, char c, int len);

/* End of utility function declarations */


//Trie
class trie {
   public:
      int num;
      short numsub;
      trie *sub[NCHARS];
      trie **parent;
      //parent interface --> routing table
      map<string, map<string, string> > FibEntries;
      vector<char> chars;
      trie(trie **par=NULL, char *start=NULL, char *end=NULL): parent(par),
      chars(start,end), numsub(0), sub(), num(0) {}
      trie(trie **par, vector<char>::iterator start, vector<char>::iterator end): 
         parent(par), chars(start,end), numsub(0), sub(), num(0) {}

      //add a string to the trie
      void add(char *start, char *end);

      //prints the trie tree structure, invoke at root with indent=0
      void print (int indent);

      //prints all strings present in the trie, invoke at root with prefix=""
      void printAllStrings(string prefix);

      //returns set of all interfaces present in all strings in the trie
      set<string> getAllInterfaces();

      //returns the compressed set of forwarding longest IP prefix match entries
      map<string, string> getMinFibEntries();

private:
      void getAllInterfaces(string prefix);
      map<string, string> getMinFibEntries(string interface, string prefix);
};

#endif
