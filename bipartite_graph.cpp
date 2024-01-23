#include <bits/stdc++.h>
using namespace std;

//maximum number of vertices
const int maxn = 1000;

//the number of vertices and edges
int n, m;

//adjacency list
vector<int> adj[maxn];

//the color of vertex (white means the vertex is not colored)
enum status{
    white = -1,
    red,
    blue
};

//status of each vertex
int color[maxn];

bool BFS(int u){
    //vertex u is used 
    color[u] = red;

    queue <int> q;
    q.push(u);

    while(!q.empty()){
        //next vertex
        int v = q.front();
        q.pop();

        for (int i : adj[v]){
            if (color[i] == white){
                color[i] = 1 - color[v];//res => blue; blue => red
                q.push(i);
            }
            //conflict
            else if (color[i] == color[v]){
                return false;
            }
        }
    }
    return true;
}

bool DFS(int u){
    for (int i : adj[u]){
        if (color[i] == white){
            color[i] = 1 - color[u];
            if (!DFS(i))    return false;
        }
        else if (color[i] == color[u]) return false;
    }
    return true;
}

int main(){
    //input
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    //mark all vertices is not used
    memset(color, white, sizeof(color));

    bool check = true;
    for (int i = 1; i <= n; i++){
        if (color[i] == white){
            if (!DFS(i)){
                check = false;
                break;
            }
        }
    }
    if (check)  cout << "the graph is bipartite\n";
    else cout << "the graph is not bipartite\n";
    return 0;
}