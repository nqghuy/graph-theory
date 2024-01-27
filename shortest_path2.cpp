#include <bits/stdc++.h>

using namespace std;
#define ll long long

//the maximum number of vertices
const int maxn = 30001;

//the number of vertices, edges, forbidden triplets
int n, m, k;

//adjacency list
vector <int> adj[maxn];

//forbidden triplets corresponding
set <tuple<int, int, int>> triplets;

//{dist, parent}
set <pair<int, int>> parent[maxn];

//mark if parent-current is visited
map<pair<int, int>, bool> visited;

//shortest path from 1 -> n
vector <int> path;

//create path
void create_path(int dist, int u)
{   
    //push into the path
    path.push_back(u);

    //the begin destination
    if (u == 1 && dist == 0)    return;

    //find parent of u
    for (auto it : parent[u]){
        if (it.first == dist){

            //continue find path through parent of u
            create_path(dist - 1, it.second);
            return;
        }
    }
}

void dijkstra(){

    //{distance, {parent, vertex}}
    priority_queue < pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq; 
    
    //start queue
    pq.push({0, {-1, 1}});

    while (!pq.empty())
    {
        //retriving from heap
        int dist = pq.top().first;
        pair<int, int> top = pq.top().second;
        int par = top.first;
        int currentVer = top.second;

        //pop from the queue
        pq.pop();

        //reject if outdated information
        if (visited[{par, currentVer}])   continue;

        visited[{par,currentVer}] = true;

        for (int neighbour : adj[currentVer]){
            //if visit forbidden triplets
            if (triplets.find({par, currentVer, neighbour}) != triplets.end()) continue;

            //if find last destination
            if (neighbour == n){
                parent[n].insert({dist + 1, currentVer});
                create_path(dist + 1, n);
                return;
            }
            
            //reject outdated information
            if(!visited[{currentVer, neighbour}]) {
                pq.push({dist + 1, {currentVer, neighbour}});
                parent[neighbour].insert({dist + 1, currentVer});
            }
        }
    }
}

int main(){
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < k; i++){
        int u, v, x;
        cin >> u >> v >> x;
        triplets.insert({u, v, x});
    }
    dijkstra();
    //if no found path
    if (parent[n].size() == 0){
        cout << -1;
        return 0;
    }

    //print path
    cout << path.size() - 1 << endl;
    for (int i = path.size() - 1; i >= 0; i--){
        cout << path[i] << " " ;
    }
    return 0;
}