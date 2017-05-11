#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "defs.h"

using namespace std;


int main(){
    int n;
    cin>>n;
    trie *trieroot;
    int iplength = -1;
    for(int i=0; i<n; i++){
        string ip_v;
        cin>>ip_v;
        string ip = getIP(ip_v); 
        string iface = getInterface(ip_v);
        ip = DecToBinIP(ip);
        string fib = ip + ":" + DecToBin(iface);
        char *cstr = new char[fib.length()+1];
        strcpy(cstr, fib.c_str());
        int len = fib.length()+1;
        if(i==0){
            trieroot = new trie(&trieroot, cstr, cstr+len);
            iplength = ip.length();
        }
        else
            trieroot->add(cstr, cstr+len);

        //!Sanity check on IP addresses
        if(ip.length() != iplength){
            cout<<"IPs are not of the same length...aborting"<<endl;
            abort();
        }
    }
    //trieroot->print(0);
    //trieroot->printAllStrings("");
    set<string> interfaces = trieroot->getAllInterfaces();
    map<string, string> fibentries = trieroot->getMinFibEntries();
    for(auto it: fibentries){
        int prefix_len = it.first.length();
        string ip_prefix = pad_suffix(it.first, '0', iplength);
        ip_prefix = BinToDecIP(ip_prefix);
        cout<<ip_prefix <<"/"<<prefix_len<<" : "<<BinToDec(it.second)<<endl;
    }
    return 0;
}
