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
    memset(minWeight, MAX_WEIGHT, sizeof(minWeight));
    memset(parent, 0, sizeof(parent));

    //push the first vertex
    nextEdge.push({0, 1});

    //the minimum spanning tree
    int min_d = 0;

    //show the tree
    vector <pair<int, int>> tree;

    while (tree.size() != n){
        //take the next vertex
        pair <int, int> infor = nextEdge.top();
        nextEdge.pop();
        int weight = infor.first;
        int currentVertex = infor.second;

        if (!used[currentVertex]){
            //mark chosen vertex is used
            used[currentVertex] = true;

            //add up size of d
            min_d += weight;

            //push next vertex into the tree
            tree.push_back({currentVertex, minWeight[currentVertex]});

            for (pair <int, int> adjEdge : adj[currentVertex]){
                int weight = adjEdge.first;
                int u = adjEdge.second;
                if (!used[u]){
                    nextEdge.push({weight, u});
                    if (weight < minWeight[u]){
                        minWeight[u] = weight;
                        parent[u] = currentVertex;
                    }
                }
            }
        }
        
    }
    for (int i = 0; i < tree.size(); i++){
        cout << parent[tree[i].first] << " " << tree[i].first << " " << tree[i].second << endl;
    }
    return min_d;
}