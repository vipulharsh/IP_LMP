#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include "defs.h"

using namespace std;

string DecToBin(string dec){
    int num = atoi(dec.c_str());
    string ret = std::bitset<8>(num).to_string(); 
    return ret;
}

string BinToDec(string bin){
    int num = std::stoi(bin, nullptr, 2);
    string ret = to_string(num); 
    return ret;
}

string addDots(string binIP){
    int curr=8;
    int len = binIP.length();
    string::iterator sit = binIP.begin();    
    while(curr<len){
        binIP.insert(sit + 8, '.');
        sit+=9;
        curr += 8;
    }
    return binIP;
}

string BinToDecIP(string ip_v){
    ip_v = addDots(ip_v);
    string ret = "", byte;
    size_t prev = 0;
    size_t pos = ip_v.find_first_of('.');
    bool dot = false;
    while(pos!=string::npos){
        byte = ip_v.substr(prev, pos-prev);
        if(dot) ret += '.';
        dot = true;
        ret += BinToDec(byte);
        prev = pos+1;
        pos = ip_v.find_first_of('.', prev);
    }
    if(dot) ret += '.';
    ret += BinToDec(ip_v.substr(prev));
    return ret;
}

string DecToBinIP(string ip_v){
    string ret = "", byte;
    size_t prev = 0;
    size_t pos = ip_v.find_first_of('.');
    while(pos!=string::npos){
        byte = ip_v.substr(prev, pos-prev);
        ret += DecToBin(byte);
        prev = pos+1;
        pos = ip_v.find_first_of('.', prev);
    }
    ret += DecToBin(ip_v.substr(prev));
    return ret;

}

string getInterface(string routingEntry){
    size_t pos = routingEntry.find_first_of(':');
    return string(routingEntry.begin()+pos+1, routingEntry.end());
}


string getIP(string routingEntry){
    size_t pos = routingEntry.find_first_of(':');
    pos = (pos==string::npos? routingEntry.length():pos);
    return string(routingEntry.begin(), routingEntry.begin()+pos);

}

string pad_suffix(string s, char c, int len){
    int strlen = s.length();
    for(int i=strlen; i<len; i++)
        s+=c;
    return s;
}
