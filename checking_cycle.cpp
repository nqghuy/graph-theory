#include <bits/stdc++.h>
using namespace std;
//n, m is the number of vertices and edges respectively
int n, m;

//adjacency list
vector <int> adj[20];

//mark if vertex is visited
int visited[20] = {};

//mark the parent of the vertex
int parent[20];


//check if there is a cycle in undirected graph
int first, last; //the start and vertex of the cycle 


//check cycle in undirected graph by dfs
bool DFS(int u);

//show cycle with dfs 
void show_cycle();

//check cycle in undirected graph by bfs(not show cycle)
bool BFS(int u);

//check cycle in directed graph by dfs
//status of vertex
enum status{
    white = 0, //vertex is not visited
    gray, // vertex is visited but not finished
    black // vertex is completely visited
};
int color[20] = {};

bool DFS2(int u);

//check cycle in directed graph by kahn algorithm
int incomingEdges[20];
bool kahn();

int main(){
    cin >> n >> m;
    //input is edge list
    for (int i = 0; i < m; i++){
        int startVer, endVer;
        cin >> startVer >> endVer;
        adj[startVer].push_back(endVer);
        incomingEdges[endVer]++;
        //undirected graph
        // adj[endVer].push_back(startVer);
    }

    //the first vertex is 1
    bool ok = false;
    if (kahn()) cout << "yes\n";
    else cout << "no\n";
    
    return 0;
}

bool DFS(int u){
    visited[u] = 1;
    for (int i : adj[u]){
        if (!visited[i]){
            parent[i] = u;
            if (DFS(i)) return true;
        }
        //if vertex i is visited and not the parent of u => i u is reverse edge
        else if (i != parent[u])    {
            first = i;
            last = u;
            return true;
        }
    }
    return false;
}

void show_cycle(){
    int tmp = last;
    vector <int> v;
    v.push_back(first);
    while (tmp != first){
        v.push_back(tmp);
        tmp = parent[tmp];
    }
    v.push_back(tmp);
    reverse(v.begin(), v.end());
    for (int i : v){
        cout << i << " " ;
    }
    cout << endl;
}


bool BFS(int u){
    visited[u] = 1;
    queue <int> q;
    q.push(u);
    while (!q.empty()){
        int v = q.front();
        q.pop();
        for (int i : adj[v]){
            if (!visited[i]){
                visited[i] = 1;
                parent[i] = v;
                q.push(i);
            }
            else if (i != parent[v]){
                return true;
                break;
            }
        }
    }
    return false;
}

bool DFS2(int u){
    color[u] = gray;
    for (int v : adj[u]){
        if (color[v] == white){
            parent[v] = u;
            if (DFS2(v)) return true;
        }
        else if (color[v] == gray){
            first = v;
            last = u;
            return true;
        }
    }
    color[u] = black;
    return false;
}

bool kahn(){
    queue <int> q;
    int cnt = 0;
    for (int i = 1; i <= n; i++){
        if (incomingEdges[i] == 0){
            q.push(i);
        }
    }
    while (!q.empty()){
        cnt++;
        int v = q.front();
        q.pop();
        for (int i : adj[v]){
            incomingEdges[i]--;
            if (incomingEdges[i] == 0){
                q.push(i);
            }
        }
    }
    return cnt != n;
}