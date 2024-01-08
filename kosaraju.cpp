#include <bits/stdc++.h>
using namespace std;
/*
step 1: create a stack(like topo sorting) by dfs
step 2: create tranpose graph
step 3: pop vertex in stack and use dfs to list strongly connected component
O(2*(V + E))
*/

//n, m is the number of vertices and edges respectively
int n, m;

//mark if the vertex is visited
int visited[20] = {};

//adjacency list
vector <int> adj[20];

//transpose adjacency list
vector <int> transpose_adj[20];

//list of strong connected component
vector <int> scc[20];

//stack of sorting topo
stack <int> topo;

void DFS(int u);

void DFS2(int u);

void show_scc();

int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int startVer, endVer;
        cin >> startVer >> endVer;
        adj[startVer].push_back(endVer);
        transpose_adj[endVer].push_back(startVer);
    }

    show_scc();
}

void DFS(int u){
    visited[u] = 1;
    for (int v : adj[u]){
        if (!visited[v]){
            DFS(v);
        }
    }    
    topo.push(u);
}

void DFS2(int u){
    visited[u] = 1;
    cout << u << " ";
    for (int v : transpose_adj[u]){
        if (!visited[v]){
            DFS2(v);
        }
    }
}

void show_scc(){
    //create a topo sorting list
    for (int i = 1; i <= n; i++){
        if (!visited[i]){
            DFS(i);
        }
    }

    //reset visited
    memset(visited, 0, sizeof(visited));

    //push each vertex in each scc
    while (!topo.empty()){
        int v = topo.top();
        topo.pop();
        if (!visited[v]){
            DFS2(v);
            cout << endl;
        }
    }
}