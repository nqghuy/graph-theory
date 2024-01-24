#include <bits/stdc++.h>

using namespace std;

//maximum number of vertices
const int maxn = 100001;

// the numer of vertices and edges respectively
int n, m;

//the parent of each vertex
int parent[maxn];

//distance from source vertex to each vertex
int d[maxn];

//marked if the vertex is visited
bool visited[maxn];

//adjacency list
vector <pair<int, int>> adj[maxn];

//find min distance to other distances
void dijkstra(int startVer){
    //set the distance from source to other vertices is infinity
    for (int i = 1; i <= n; i++){
        d[i] = INT_MAX;
    }
    d[startVer] = 0;
    
    //choose the vertex is unmarked and the distance is smallest
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({d[startVer], startVer});
    while (!pq.empty()){
        //next vertex
        pair<int, int> top = pq.top();

        //pop from queue
        pq.pop();
        int current_vertex = top.second;
        int d_current_vertex = top.first;

        if(visited[current_vertex])    continue;
        visited[current_vertex] = true;

        for (pair<int, int> edge : adj[current_vertex]){
            int adjacencyVertex = edge.first;
            int weight = edge.second;

            //relaxation
            d[adjacencyVertex] = min(d[adjacencyVertex], d[current_vertex] + weight);
            pq.push({d[adjacencyVertex], adjacencyVertex});
        }
    }
    for (int i = 1; i <= n; i++){
        cout << d[i] << endl;
    }
}


int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    int startVer;
    cin >> startVer;
    dijkstra(startVer);

    return 0;
}