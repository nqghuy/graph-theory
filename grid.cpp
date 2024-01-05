#include <bits/stdc++.h>
using namespace std;

int row, col;
char grid[1001][1001] = {};
int dx[4] = {-1, 0, 0, 1};
int dj[4] = {0, -1, 1, 0};

map <pair<int, int>, char> mp;
map <pair <int, int>, pair <int, int>> parent;


bool BFS(int i1, int j1, int i2, int j2){
    //mark [i,j] is visited
    grid[i1][j1] = 'x';

    //queue for visited vertex
    queue <pair<int, int>> q;

    q.push({i1, j1});
    while (!q.empty()){
        pair <int, int> v = q.front();
        q.pop();
        for (int k = 0; k < 4; k++){
            //new cordinate
            int newi = v.first + dx[k];
            int newj = v.second + dj[k];
            
            if (newi >= 1 && newi <= row && newj >= 1 && newj <= col && grid[newi][newj] != 'x'){//if satisfy the condition
                //v is parent of [newi, newj]
                parent[{newi, newj}] = {v.first, v.second};

                //save the direction
                if (newi == v.first){
                    if (newj < v.second){
                        mp[{newi, newj}] = 'L';
                    }
                    else mp[{newi, newj}] = 'R';
                }
                else if(newi < v.first){
                    mp[{newi, newj}] = 'U';
                }
                else mp[{newi, newj}] = 'D';

                //mark [newi, newj] is visited
                grid[newi][newj] = 'x';

                //if B is found
                if (newi == i2 && newj == j2){
                    return true;
                }
                
                //push visited [newi, newj] into queue
                q.push({newi, newj});
            }
        }
    }
    return false;
}

void path(int i1, int j1, int i2, int j2){
    if (!BFS(i1, j1, i2, j2)){
        cout << "no path\n";
        return;
    }
    //start point
    mp[{i1, j1}] = 'S';
    parent[{i1, j1}] = {-1, -1};

    //contain path
    vector <char> path;
    while (i2 != -1 && j2 != -1){
        path.push_back(mp[{i2, j2}]);
        int tmp = i2;
        i2 = parent[{i2, j2}].first;
        j2 = parent[{tmp, j2}].second;
    }

    for (int i = path.size() - 1; i >= 0; i--){
        cout << path[i] << " ";
    }
}

int main(){
    cin >> row >> col;
    int i1, j1, i2, j2;
    memset(grid, 'x', sizeof(grid));
    for (int i = 1; i <= row; i++){
        for (int j = 1; j <= col; j++){
            cin >> grid[i][j];
            if (grid[i][j] == 'A') {
                i1 = i;
                j1 = j;
            }
            if (grid[i][j] == 'B'){
                i2 = i;
                j2 = j;
            }
        }
    }
    path(i1, j1, i2, j2);
}