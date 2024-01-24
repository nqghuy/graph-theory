#include <bits/stdc++.h>

using namespace std;

//maximum number of vertices
const int maxn = 100001;

//maximum distance
const long long INF = 1e18;
// the numer of vertices and edges respectively
int n, m;

//the parent of each vertex
int parent[maxn];


//adjacency list
vector <pair<int, int>> adj[maxn];

void showPath(int u){
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
    //distance from source vertex to each vertex
    long long d[maxn];

    //set the distance from source to other vertices is infinity
    for (int i = 1; i <= n; i++){
        d[i] = INF;
    }
    d[startVer] = 0;
    
    //choose the vertex is unmarked and the distance is smallest
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    pq.push({d[startVer], startVer});
    while (!pq.empty()){
        //next vertex
        pair<int, int> top = pq.top();

        //pop from queue
        pq.pop();
        int current_vertex = top.second;
        long long d_current_vertex = top.first;
        
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
    //start point
    parent[startVer] = -1;

    // show distance and path
    for (int i = 1; i <= n; i++){
        cout << d[i] << ": ";
        showPath(i);
        cout << endl;
    }
}


int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    dijkstra(1);
    
    return 0;
}