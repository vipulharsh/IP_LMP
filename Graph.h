#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <bitset>
#include <set>
using namespace std;


typedef pair<int, int> PII;

class Graph{
public:
   int N;
   vector<vector<int> > edges;
   vector<int> partition;
   bool* visited;
   string* ip_addr;
   int* prev_hop;
   string* interface;
   Graph(){}
   void input(){
      vector<PII> edges_logs;
      set<int> vertices;
      int a, b;
      while(cin>>a>>b){
        vertices.insert(a);
        vertices.insert(b);
        edges_logs.push_back(PII(a, b)); 
      }
      N = vertices.size();
      edges.resize(N);
      partition.resize(N);
      visited = new bool[N];
      ip_addr = new string[N];
      prev_hop = new int[N];
      interface = new string[N];
      for(PII e: edges_logs){
         a = e.first, b = e.second;
         edges[a].push_back(b);
         edges[b].push_back(a);
      }
   }
   void assign_IPs(){
      string IP_org = "10.121.78.";
      fill(visited, visited+N, false);
      queue<int> bfsQ; 
      bfsQ.push(0);
      visited[0] = true;
      prev_hop[0] = 0;
      int counter = 0;
      while(!bfsQ.empty()){
        int node = bfsQ.front();
        bfsQ.pop();
        for(int nbr: edges[node]){
           if(!visited[nbr]){
               bfsQ.push(nbr);
               visited[nbr] = true;
               prev_hop[nbr] = node;
           }
        }
        ip_addr[node] = IP_org + to_string(counter);
        counter++;
      }
   }

   void printIPs(){
        for(int i=0; i<N; i++){
            cout<<i<<": "<<ip_addr[i]<<endl;
        }
   }


   int findNbrIndex(int node, int nbr){
        for(int i=0; i<edges[node].size(); i++)
            if(edges[node][i] == nbr) return i;
        cout<<"Should never have come here .... "<<endl;
        exit(0);
   }

   void findInterfaces(){
       for(int i=1; i<N; i++){
           int curr = i;
           while(prev_hop[curr] != 0){
               curr = prev_hop[curr];
           }
           int iface = findNbrIndex(0, curr);
           interface[i] = to_string(iface);
       }
       cout<<N-1<<endl;
       for(int i=1; i<N; i++){
           cout<<ip_addr[i]<<":"<<interface[i]<<endl;
       }
   }

};
