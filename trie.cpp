#include "defs.h"

set<std::string> allInterfaces;

void trie::add(char *start, char *end) {
    vector<char>::iterator itr;
    //cout<<"Adding "<<end-start<<" characters"<<endl;
    for (itr=chars.begin(); itr!=chars.end() && start!=end && *start==*itr;
            itr++, start++);
    if (start==end){
        assert(itr==chars.end());
        return; //full match; string has repeated
    }
    if (itr==chars.end()){ //has to be an intermediate trie
        if (numsub==0){
            printf("Shouldn't come here --------\n");
            abort();
            chars.insert(itr,start,end);
        }
        else {
            trie **p = sub+((*start)-CHAROFFSET);
            if (*p==NULL) {
                *p = new trie (p,start,end);
                numsub++;
            }
            else
                (*p)->add(start,end);
        }
    }
    else {
        trie *p = new trie(parent,chars.begin(),itr);
        trie **xpar = p->sub+((*start)-CHAROFFSET);
        chars.erase(chars.begin(),itr);
        p->sub[chars[0]-CHAROFFSET] = this;
        (*parent) = p;
        parent = &(p->sub[chars[0]-CHAROFFSET]);
        *xpar = new trie(xpar,start,end);
        p->numsub = 2;
    }
}

void trie::print (int indent) {
    int i;
    for (i=0; i<indent; i++) printf(" ");
    printf("[%.*s] %d\n", (int)chars.size(),&chars[0],(int)chars.size());
    for (int i=0; i<NCHARS; i++){
        if (sub[i] != NULL)
            sub[i]->print(indent+chars.size());
    }
}

void trie::printAllStrings(string prefix){
    for(char c: chars)
        prefix += c;
    for (int i=0; i<NCHARS; i++){
        if (sub[i] != NULL)
            sub[i]->printAllStrings(prefix);
    }
    if(numsub==0)
        cout<<getIP(prefix)<<" "<<getInterface(prefix)<<endl;
}

set<string> trie::getAllInterfaces(){
    allInterfaces.clear();
    getAllInterfaces(""); 
    allInterfaces.insert("");
    return allInterfaces;
}

void trie::getAllInterfaces(string prefix){
    for(char c: chars)
        prefix += c;
    for (int i=0; i<NCHARS; i++){
        if (sub[i] != NULL){
            sub[i]->getAllInterfaces(prefix);
        }
    }
    if(numsub==0)
        allInterfaces.insert(getInterface(prefix));
}

map<string, string> trie::getMinFibEntries(){
    //populate allInterfaces
    if(allInterfaces.empty()){
        getAllInterfaces(""); 
        allInterfaces.insert("");
    }
    //invoke DP 
    return getMinFibEntries("", "");
}

map<string, string> trie::getMinFibEntries(string interface, string prefix){
    //check if we have it stored in the dp
    if(FibEntries.find(interface) != FibEntries.end())
        return FibEntries[interface];

    for(char c: chars){
        prefix += c;
    }
    //cout<<"prefix: "<<prefix<<" : "<<"interface: "<<interface<<" computing "<<endl;
    map<string, string> optRoutingTable; 
    int optsize = INT_MAX;
    for(string iface: allInterfaces){
        map<string, string> routingTable; 
        for (int i=0; i<NCHARS; i++){
            if (sub[i] != NULL){
                map<string, string> res = sub[i]->getMinFibEntries(iface, prefix);
                routingTable.insert(res.begin(), res.end());
            }
        }
        if(iface != interface){
            routingTable[getIP(prefix)] =  iface;
        }
        if(routingTable.size() < optsize){
            optRoutingTable = routingTable;
            optsize = routingTable.size();
        }
    }
    if(numsub == 0 && getInterface(prefix) != interface){
        //cout<<"Adding routing entry: "<<getIP(prefix)<<" : "<<getInterface(prefix)<<endl;
        optRoutingTable[getIP(prefix)] = getInterface(prefix);
    }
    FibEntries[interface] = optRoutingTable;
    return optRoutingTable;
}
