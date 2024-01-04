#include <bits/stdc++.h>
using namespace std;
/*
directed graph
input 
10 11
1 2
1 3
1 10
2 4
3 5
3 6
5 8
5 10
6 7
7 3
8 9
output: 1 2 3 10 4 5 6 8 7 9
*/
void BFS(vector<int> adj[], int visited[], int vertex){
    queue <int> outVertex;
    outVertex.push(vertex);
    visited[vertex] = 1;
    while (!outVertex.empty()){
        int currentVer = outVertex.front();
        outVertex.pop();
        cout << currentVer << " ";
        for (int x : adj[currentVer]){
            if (!visited[x]){
                outVertex.push(x);
                visited[x] = 1;
            }
        }
    }
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
        // adj[endVer].push_back(startVer);
    }
    int visited[20] = {};
    BFS(adj, visited, 1);
}