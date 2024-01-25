#include <bits/stdc++.h>
using namespace std;

#define ll long long

//the maximum number of vertices
const int maxn = 1000001;

//the maximum distance is infinity
const ll INF = 1e18;

//the number of vertices and edges
int n, m;

//adjacency list {destination, cost}
vector <pair<int, int>> adj[maxn];

//the distance with coupon
ll d1[maxn];

//the distance without coupon
ll d2[maxn];

ll dijkstra()
{
    //set all distance = inf
    for (int i = 1; i <= n; i++){
        d1[i] = INF;
        d2[i] = INF;
    }
    d1[1] = 0;
    d2[1] = 0;

    //{cost, destination, coupon}
    priority_queue<tuple<ll, int, bool>, vector <tuple<ll, int, bool>>, greater<tuple<ll, int, bool>>> pq;
    pq.push({0, 1, true});
    while (!pq.empty())
    {
        auto it = pq.top();
        pq.pop();

        //information of current destination
        ll cost = get<0>(it);
        int currentDes = get<1>(it);
        bool coupon = get<2>(it);

        //found smaller path befor
        if (coupon == true && cost > d1[currentDes])    continue;
        if (coupon == false && cost > d2[currentDes])   continue;

        for (auto flight : adj[currentDes])
        {
            //adjacency destination
            int nextDes = flight.first;
            int weight = flight.second;

            //if not use coupon before
            if (coupon == true)
            {   
                //relaxation
                if (d1[nextDes] > cost + weight)
                {
                    d1[nextDes] = cost + weight;
                    pq.push({d1[nextDes], nextDes, true});
                }
                if (d2[nextDes] > cost + weight / 2)
                {
                    d2[nextDes] = cost + weight / 2;
                    pq.push({d2[nextDes], nextDes, false});
                }
            }
            //if use coupon before
            else if (coupon == false)
            {
                //before
                if (d2[nextDes] > cost + weight)
                {
                    d2[nextDes] = cost + weight;
                    pq.push({d2[nextDes], nextDes, false});
                }
            }
        }
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << d1[i] << " " << d2[i] << endl;
    // }
    return d2[n];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    cout << dijkstra();
}