#include <bits/stdc++.h>
using namespace std;

void BFS(vector<int> adj[], int visited[], int vertex){
    queue <int> outVertex;
    outVertex.push(vertex);
    visited[vertex] = 1;
    while (!outVertex.empty()){
        int currentVer = outVertex.front();
        outVertex.pop();
        //cout << currentVer << " ";
        for (int x : adj[currentVer]){
            if (!visited[x]){
                outVertex.push(x);
                visited[x] = 1;
            }
        }
    }
}


void DFS(vector <int> adj[], int visited[], int vertex){
    visited[vertex] = 1;
    cout << vertex << " ";
    for (int x : adj[vertex]){
        if (!visited[x]){
            DFS(adj, visited, x);
        }
    }
}

int connectedComponent(vector <int> adj[], int visited[], int n){
    int cnt = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 1; i <= n; i++){
        if (!visited[i]){
            cnt++;
            DFS(adj, visited, i);
            cout << endl;
        }
    }
    return cnt;
}

int main(){
    //n is the number of vertices
    //m is the number of edge
    int n, m;
    cin >> n >> m;
    //adjacency list
    vector <int> adj[20];
    for (int i = 0; i < m; i++){
        int startVer, endVer;
        cin >> startVer >> endVer;
        adj[startVer].push_back(endVer);

        //if not directed graph
        adj[endVer].push_back(startVer);
    }
    int visited[20] = {};
    cout << connectedComponent(adj, visited, n);
}