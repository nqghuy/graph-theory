#include <bits/stdc++.h>

using namespace std;
#define ll long long

//the max number of destination
const int maxn = 1000001;

//the maximum cost
const ll INF = 1e18;

//the number of destination, flight, shortest paths respectively
int n, m, k;

//adjacency list
vector <pair<int, int>> adj[maxn];

//find shortest paths
vector <ll> shortest_path[maxn];

//find k shortest paths from 1 to n
void dijkstra()
{
    priority_queue<pair<ll, int>, vector <pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0, 1});
    while (!pq.empty()){
        //retrieving from heap
        pair <ll, int> top = pq.top();
        int currentDes = top.second;
        ll dist = top.first;

        //pop from the queue
        pq.pop();

        //rejecting if outdated information
        if (dist > shortest_path[currentDes][k - 1])    continue;
        
        //visit neighbor
        for (pair<int, int> flight : adj[currentDes]){
            int nextDes = flight.first;
            int cost = flight.second;

            //if find short path
            if (shortest_path[nextDes][k - 1] > dist + cost){
                shortest_path[nextDes][k - 1] = dist + cost;
                
                //push new path
                pq.push({dist + cost, nextDes});
                
                //update shortest paths
                sort(shortest_path[nextDes].begin(), shortest_path[nextDes].end());
            }
        }
    }
    for (ll i : shortest_path[n]){
        cout << i << " ";
    }
}
int main(){
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    for (int i = 1; i <= n; i++){
        shortest_path[i].assign(k, INF);
    }
    dijkstra();
    return 0;
}