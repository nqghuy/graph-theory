#include <bits/stdc++.h>
using namespace std;
/*
directed graph
input
9 10
1 2
1 3
1 5
2 4
3 6
3 7
5 8
6 7
8 9
9 3
output
1 2 4 3 6 7 9 8 5
*/

void DFS(int visited[], vector <int> adj[], int vertex){
    visited[vertex] = 1;
    cout << vertex << " ";
    for (int i : adj[vertex]){
        if (!visited[i]){
            DFS(visited, adj, i);
        }
    } 
}
int main(){
    // n is number of vertex
    // m is number of edge
    int n, m;
    cin >> n >> m;

    //adjacency list
    vector <int> adj[n + 1];
    
    for (int i = 0; i < m; i++){
        int startVer, endVer;
        cin >> startVer >> endVer;
        adj[startVer].push_back(endVer);
        // adj[endVer].push_back(startVer);
    }

    //mark if this vertex is visited
    int visited[n + 1] = {};

    DFS(visited, adj, 1);
}
