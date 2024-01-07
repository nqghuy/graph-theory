#include <bits/stdc++.h>
using namespace std;
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

void DFS2(int u, int cnt){
    visited[u] = 1;
    scc[cnt].push_back(u);
    for (int v : transpose_adj[u]){
        if (!visited[v]){
            DFS2(v, cnt);
        }
    }
}

void show_scc(){
    //create a topo sorting list
    DFS(1);

    //the order of scc
    int cnt = 0;

    //reset visited
    memset(visited, 0, sizeof(visited));

    //push each vertex in each scc
    while (!topo.empty()){
        int v = topo.top();
        topo.pop();
        if (!visited[v]){
            DFS2(v, cnt);
            cnt++;
        }
    }

    //show scc
    for (int i = 0; i < cnt; i++){
        for (int k : scc[i]){
            cout << k << " ";
        }
        cout << endl;
    }
}