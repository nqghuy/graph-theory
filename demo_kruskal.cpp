#include <bits/stdc++.h>
using namespace std;

struct edge{
    int u, v;
    int weight;
};

//cmp for sorting edge
bool cmp(edge, edge);

//the number of vertices and edges respectively
int n, m;

//mark the parent of each vertex
int parent[50];

//size of set
int size[50];

//each vertex is a set
void make_set();

//find the leader of the set
int find(int);

//union 2 set
bool Union (int, int);

int main(){
    cin >> n >> m;
    make_set();
    vector <edge> edge_list;
    for (int i = 0; i < m; i++){
        int startVer, endVer, weight;
        cin >> startVer >> endVer >> weight;
        edge tmp{startVer, endVer, weight};
        edge_list.push_back(tmp);
    }
    sort(edge_list.begin(), edge_list.end(), cmp);

    //to know about the number of used vertices
    vector <edge> MST;

    //sum of weight in MST
    int min_d = 0;

    for (edge x : edge_list){
        //the spanning tree has all vertices and cannot be spanned if the number of edges is equal to the number of vertices - 1
        if (MST.size() == n -1)    break;

        //not create cycle
        if (Union(x.u, x.v)){
            MST.push_back(x);
            Union(x.u, x.v);
            min_d += x.weight;
        }
    }
    //the graph is not connected
    if (MST.size() != n - 1){
        cout << "the graph is not connected\n";
    }
    else {
        for (edge x : MST){
            cout << x.u << " " << x.v << " " << x.weight << endl;
        }
        cout << min_d;
    }
}

bool cmp(edge a, edge b){
    return a.weight < b.weight;
}

void make_set(){
    for (int i = 1; i <= n; i++){
        parent[i] = i;
        size[i] = 1;
    }
}

int find(int v){
    if (v == parent[v]) return v;

    //path compression
    parent[v] = find(parent[v]);

    return parent[v];
}

bool Union(int a, int b){
    // the parent(leader) of a and b
    a = find (a);
    b = find (b);

    //a and b is not in a set
    if (a != b){
        if (size[a] < size[b])  swap(a, b);
        
        //parent of smaller size vertex is larger size vertex
        parent[b] = a;

        //add up size
        size[a] += size[b];
        
        return true;
    }
    return false;
}