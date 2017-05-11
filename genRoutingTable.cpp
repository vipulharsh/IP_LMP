#include <iostream>
#include "Graph.h"



int main(){

     Graph G;
     G.input();
     G.assign_IPs();
     //G.printIPs();
     G.findInterfaces();
     return 0;
}
