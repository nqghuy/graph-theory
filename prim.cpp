#include <bits/stdc++.h>
using namespace std;

//max number of edge
const int maxn = 1000;

//max weight
const int MAX_WEIGHT = 1e9 + 7;
struct edge{
    int u, v;
    int weight;
};

//the number of vertices and edges respectively
int n, m;

//mark the parent of each vertex
int parent[maxn];

//mark the min weight
int minWeight[maxn];

//adjacency list with weight
vector <pair<int, int>> adj [maxn];

//mark the vertex is used, true if the vertex is in Vmst and false if the vertex is in V
bool used[maxn];

//choose the next edge with an edge in V and the other in Vmst
priority_queue <pair <int, int>, vector<pair<int, int>>, greater<pair<int, int>>> nextEdge;//weight first

//find minimun spanning tree and print the tree
int prim();

int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;

        //weight first 
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
    cout << prim();
}

int prim(){
    //mark all edges is not used
    memset(used, false, sizeof(used));
    memset(parent, 0, sizeof(parent));
    for (int i = 0; i < maxn; i++){
        minWeight[i] = MAX_WEIGHT;
    }

    //push the first vertex
    nextEdge.push({0, 1});
    //the minimum spanning tree
    int min_d = 0;

    //show the tree
    vector <edge> tree;

    while (tree.size() != n){
        //take the next vertex
        pair <int, int> top = nextEdge.top();
        nextEdge.pop();
        int weight = top.first;
        int currentVertex = top.second;

        //check if current vertex is used
        if (used[currentVertex])    continue;

        //mark chosen vertex is used
        used[currentVertex] = true;

        //add up size of d
        min_d += weight;

        //push next vertex into the tree
        tree.push_back({parent[currentVertex], currentVertex, minWeight[currentVertex]});

        for (pair <int, int> adjEdge : adj[currentVertex]){
            int weight = adjEdge.first;
            int u = adjEdge.second;

            //push u into priority queue if there is an edge with smaller weight
            if (!used[u] && weight < minWeight[u]){
                nextEdge.push({weight, u});
                minWeight[u] = weight;
                parent[u] = currentVertex;
            }
        }
        
    }
    //the first edge is not printed
    for (int i = 1; i < tree.size(); i++){
        cout << tree[i].u << " " << tree[i].v << " " << tree[i].weight << endl;
    }
    return min_d;
}