#include <bits/stdc++.h>
using namespace std;

int row, col;
int grid[1001][1001] = {};
int dx[4] = {-1, 0, 0, 1};
int dj[4] = {0, -1, 1, 0};

void DFS(int i, int j){
    grid[i][j] = 0;
    for (int k = 0; k < 4; k++){
        int newi = i + dx[k];
        int newj = j + dj[k];
        if (newi >= 1 && newi <= row && newj >= 1 && newj <= col && grid[newi][newj])   DFS(newi, newj);
    }
}

void BFS(int i, int j){
    grid[i][j] = 0;
    queue <pair<int, int>> q;
    q.push({i, j});
    while (!q.empty()){
        pair <int, int> v = q.front();
        cout << v.first << " " << v.second << endl;
        q.pop();
        for (int k = 0; k < 4; k++){
            int newi = v.first + dx[k];
            int newj = v.second + dj[k];
            if (newi >= 1 && newi <= row && newj >= 1 && newj <= col && grid[newi][newj]){
                grid[newi][newj] = 0;
                q.push({newi, newj});
            }
        }

    }
}

int connectedComponent(){
    int cnt = 0;
    for (int i = 1; i <= row; i++){
        for (int j = 1; j <= col; j++){
            if (grid[i][j]){
                cnt++;
                cout << "thanh phan lien thong thu " << cnt << ":\n";
                BFS(i, j);
            }
        }
    }
    return cnt;
}


int main(){
    cin >> row >> col;
    for (int i = 1; i <= row; i++){
        for (int j = 1; j <= col; j++){
            cin >> grid[i][j];
        }
    }
    cout << connectedComponent();
}