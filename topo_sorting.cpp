#include <bits/stdc++.h>
using namespace std;
//min vertex is 0
//n is the number of vertices, m is the number of edges
int n, m;

//adjacency list
vector <int> adj[20];

//mark if this vertex is visited
int visited[20] = {};

//topological list
vector <int> topo;

void DFS(int u){
    visited[u] = 1;
    for (int x : adj[u]){
        if (!visited[x]){
            DFS(x);
        }
    }
    topo.push_back(u);
}

void out_topo_list(){
    for (int i = 0; i < n; i++){
        if (!visited[i])    DFS(i);
    }
    reverse(topo.begin(), topo.end());
    for (int i : topo){
        cout << i << " ";
    }
}

//kahn algorithm
queue <int> topo2;
int incomingEdges[20] = {};
void kahn(){
    for (int i = 0; i < n; i++){
        if (incomingEdges[i] == 0){
            topo2.push(i);
        }
    }
    while (!topo2.empty()){
        int currentVer = topo2.front();
        cout << currentVer << " ";
        topo2.pop();
        for (int i : adj[currentVer]){
            incomingEdges[i]--;
            if (incomingEdges[i] == 0){
                topo2.push(i);
            }
        }
    }
}

int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int startVer, endVer;
        cin >> startVer >> endVer;
        adj[startVer].push_back(endVer);
        incomingEdges[endVer]++;
    }
    kahn();
}