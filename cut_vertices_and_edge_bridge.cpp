#include <bits/stdc++.h>
using namespace std;

//maximum number of vertices
const int maxn = 100001;

//the number of vertices and edges
int n, m;

//adjacency list
vector <int> adj[maxn];

//edge list
vector <pair<int, int>> edge_list;

//mark if the vertex is visited
int visited[maxn];

void DFS(int u){
    visited[u] = 1;
    for (int i : adj[u]){
        if (!visited[i]){
            DFS(i);
        }
    }
}

//the number of connected components
int connected_components(){
    //the final res
    int res = 0;

    for (int i = 1; i <= n; i++){
        if (!visited[i]){
            res++;
            DFS(i);
        }
    }
    return res;
}

void cut_vertices(int cnt){//cnt is the number of connected components
    
    //list of cut vertices
    vector <int> articulation_points;

    for (int i = 1; i <= n; i++){
        //reset visited
        memset(visited, 0, sizeof(visited));

        //remove i to check i is a cut vertex
        visited[i] = 1;
        int tmp_connected_components = connected_components();
        if (tmp_connected_components > cnt){
            articulation_points.push_back(i);
        }
    }
    cout << articulation_points.size() << endl;
    for (int i : articulation_points){
        cout << i << " ";
    }
    cout << endl;
}

//dfs for edge bridge
void DFS2(int u, int s, int t){
    visited[u] = 1;
    for (int i : adj[u]){
        if ((u == s && i == t) || (u == t && i == s)){
            continue;
        }
        else if (!visited[i]){
            DFS2(i, s, t);
        }
    }
}

//the number of connected components for edge bridge
int connected_components2(int s, int t){
    //the final res
    int res = 0;

    for (int i = 1; i <= n; i++){
        if (!visited[i]){
            res++;
            DFS2(i, s, t);
        }
    }
    return res;
}

void edge_bridge(int cnt){//cnt is the number of connected components
    //list of edge bridge
    vector <pair<int, int>> v;

    for (pair <int, int> edge : edge_list){
        //reset visited
        memset(visited, 0, sizeof(visited));

        //remove s-t edge
        int s = edge.first;
        int t = edge.second;
        int tmp_connected_components = connected_components2(s, t);
        if (tmp_connected_components > cnt){
            v.push_back({s, t});
        }
    }
    cout << v.size() << endl;
    for (pair <int, int> edge : v){
        cout << edge.first << " " << edge.second << endl;
    }
}


int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edge_list.push_back({u, v});
    }
    

    //the number of connected components
    int cnt = connected_components();
    cut_vertices(cnt);
    edge_bridge(cnt);
    return 0;
}