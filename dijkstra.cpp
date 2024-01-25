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
 
//contains weight of edge between 2 edges
map<pair<int, int>, int> mp;
 
//adjacency list
vector <pair<int, int>> adj[maxn];
 
//not used coupon
long long d1[maxn];
 
//used coupon
long long d2[maxn];
 
//prepare to use coupon
long long d3[maxn];
 
struct flight{
    long long cost1, cost2, cost3;
    int destination;
 
    bool operator > (const flight& another) const
    {
        return this->cost1 > another.cost1;
    }
    bool operator == (const flight& another) const
    {
        return cost1 == another.cost1;
    }
};
 
 
//find min distance to other distances
void dijkstra(int startVer){
    bool visited[maxn];
 
    //set the distance from source to other vertices is infinity
    for (int i = 1; i <= n; i++){
        d1[i] = INF;
        d2[i] = INF;
        d3[i] = INF;
    }
    //choose the vertex is unmarked and the distance is smallest
    priority_queue<flight, vector<flight>, greater<flight>> pq;
    d1[1] = 0;
    d2[1] = 0;
    d3[1] = 0;
    pq.push({0, 0, 0, startVer});
    while (!pq.empty()){
        //next flight
        flight f = pq.top();
 
        //pop from queue
        pq.pop();
        long long d1_f = f.cost1;
        long long d2_f = f.cost2;
        long long d3_f = f.cost3;
        int currentDes = f.destination;
        
        //if the vertex is visited
        if (d1_f > d1[currentDes] || d2_f > d2[currentDes] || d3_f > d3[currentDes])    continue;
 
        for (pair<int, int> edge : adj[currentDes]){
            int nextDes = edge.first;
            int cost = edge.second;
            long long tmp_d1 = d1[nextDes];
            long long tmp_d2 = d2[nextDes];
            long long tmp_d3 = d3[nextDes];

            d1[nextDes] = min(d1[nextDes], d1[currentDes] + cost);
            d2[nextDes] = min(d2[nextDes],min(d2[currentDes], d3[currentDes]) + cost);
            d3[nextDes] = min(d3[nextDes], d1[currentDes] + cost / 2);
 
            if (tmp_d1 != d1[nextDes] || tmp_d2 != d2[nextDes] || tmp_d3 != d3[nextDes])
            pq.push({d1[nextDes], d2[nextDes], d3[nextDes], nextDes});
        }
    }
    cout << min({d1[n], d2[n], d3[n]});
    // for (int i = 1; i <= n; i++){
    //     cout << d1[i] << " " << d2[i] << " " << d3[i] << endl;
    // }
}
 
 
int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        mp[{u, v}] = w;
    }
 
    dijkstra(1);
    
    return 0;
}