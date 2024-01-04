#include <bits/stdc++.h>
using namespace std;
// n is the numbers of vertices, m is the number of edges
int n, m;

//adjacency list
vector <int> adj[20];

//mark if this vertex is visited or not
int visited[20] = {};

int parent[20] = {};

void BFS(int u){
    visited[u] = 1;
    queue <int> q;
    q.push(u);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for (int x : adj[v]){
            if (!visited[x]){
                visited[x] = 1;
                q.push(x);
                parent[x] = v;
            }   
        }
    }
}

void DFS(int x){
    visited[x] = 1;
    for (int i : adj[x]){
        if (!visited[i]){
            parent[i] = x;
            DFS(i);
        }
    }

}

void path(int x, int y){
    vector <int> v;
    BFS(x);
    parent[x] = -1;
    if (visited[y] == 0){
        cout << "no path\n";
        return;
    }
    while (y != -1){
        v.push_back(y);
        y = parent[y];
    }
    for (int i = v.size() - 1; i >= 0; i--){
        cout << v[i] << " ";
    }
}

int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int startVer, endVer;
        cin >> startVer >> endVer;
        //undirected graph
        adj[startVer].push_back(endVer);
        adj[endVer].push_back(startVer);
    }

    //s is start vertex, e is end vertex
    int s, e;
    cin >> s >> e;
    path (s, e);
}