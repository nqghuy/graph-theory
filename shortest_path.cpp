#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
//maximum number of vertices
const int maxn = 100001;
 
//maximum distance
const long long INF = 1e18;
// the numer of vertices and edges respectively
int n, m;
 
//the parent of each vertex
int parent[maxn];
 
//distance from source vertex to each vertex
ll d[maxn];
 
//adjacency list
vector <pair<int, int>> adj[maxn];
 
void showPath(int u){
    //if no found path
    if (parent[u] == -1){
        cout << -1 ;
        return;
    }
    vector <int> path;
    while (u != -1){
        path.push_back(u);
        u = parent[u];
    }
    for (int i = path.size() - 1; i >= 0; i--){
        cout << path[i] << " ";
    }
}
 
//find min distance to other distances
void dijkstra(int startVer){
    //set all vertex with no parent
    memset(parent, -1, sizeof(parent));

    //set the distance from source to other vertices is infinity
    for (int i = 1; i <= n; i++){
        d[i] = INF;
    }
    d[startVer] = 0;
 
    //choose the vertex is unmarked and the distance is smallest
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
 
    pq.push({d[startVer], startVer});
    while (!pq.empty()){
        //retrieving from heap
        pair<int, int> top = pq.top();
        int current_vertex = top.second;
        ll d_current_vertex = top.first;

        //pop from queue
        pq.pop();
        
        //if the vertex is visited
        if (d_current_vertex > d[current_vertex])   continue;
 
        for (pair<int, int> edge : adj[current_vertex]){
            int adjacencyVertex = edge.first;
            int weight = edge.second;
 
            //relaxation
            if (d[adjacencyVertex] > d[current_vertex] + weight){
 
                //update new distance
                d[adjacencyVertex] = min(d[adjacencyVertex], d[current_vertex] + weight);
 
                //push into queue
                pq.push({d[adjacencyVertex], adjacencyVertex});
 
                //set parent
                parent[adjacencyVertex] = current_vertex;
            }
        }
    }
    // show path
    showPath(n);
}
 
int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dijkstra(1);
 
    return 0;
}