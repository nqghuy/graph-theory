#include <bits/stdc++.h>

using namespace std;

//g has euler cycle if all vertices have even degrees

// maximum number of vertices
const int maxn = 100001;

//the number of vertices and edges
int n, m;

//adjacency list
set <int> adj[maxn];

//vertex degree
int degree[maxn];

void euler_cycle(int startVertex)
{
    stack <int> st;
    st.push(startVertex);

    //show euler cycle or path
    vector <int> cycle;

    while (!st.empty()){
        int v = st.top();
        //if current vertex has no adjacency vertex
        if (adj[v].empty()){
            st.pop();
            cycle.push_back(v);
        }
        else{
            int adjacencyVer = *adj[v].begin();
            
            //delete edge x-y
            adj[adjacencyVer].erase(v);
            adj[v].erase(adjacencyVer);

            //push next vertex into stack
            st.push(adjacencyVer);
        }
    }
    for (int i : cycle){
        cout << i << " ";
    }
}

void path_cycle(){
    int startVertex;
    for (int i : degree){
        if (i & 1){
            startVertex = i;
            break;
        }
    }
    euler_cycle(startVertex);

}

int main(){
    //undirected graph
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
        degree[u]++;
        degree[v]++;
    }
    int startVertex;
    cin >> startVertex;
    path_cycle();

    // euler_cycle(startVertex);
    return 0;
}