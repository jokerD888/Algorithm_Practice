//BFS/DFS
#include<iostream>
using namespace std;
#include<limits>
#include<vector>
#include<queue>

class Solution
{
private:
    static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dist(m, vector<int>(n,INT_MAX));
        queue<pair<int, int>> q;
        // �����е� 0 ��ӽ���ʼ������
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    //q.emplace(i, j);
                    q.push({ i,j });
                    dist[i][j] = 0;
                }
            }
        }

        // �����������
        while (!q.empty())
        {
            auto [i, j] = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d)
            {
                int ni = i + dirs[d][0];
                int nj = j + dirs[d][1];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && dist[i][j]+1<dist[ni][nj])
                {
                    dist[ni][nj] = dist[i][j] + 1;
                    q.emplace(ni, nj);
                }
            }
        }

        return dist;
    }
};

//�ٽ�
//BFS�����ҳ�����0����ӣ����Ը���0Ϊ�����������������ܲ鿴������+1������0���ܵ�1Ϊ��������ɢ����������
class Solution
{
private:
    static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) 
    {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dist(m, vector<int>(n));
        vector<vector<int>> seen(m, vector<int>(n));
        queue<pair<int, int>> q;
        // �����е� 0 ��ӽ���ʼ������
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    q.emplace(i, j);
                    seen[i][j] = 1;
                }
            }
        }

        // �����������
        while (!q.empty()) 
        {
            auto [i, j] = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d) 
            {
                int ni = i + dirs[d][0];
                int nj = j + dirs[d][1];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && !seen[ni][nj]) 
                {
                    dist[ni][nj] = dist[i][j] + 1;
                    q.emplace(ni, nj);
                    seen[ni][nj] = 1;
                }
            }
        }

        return dist;
    }
};


//DP
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // ��ʼ����̬�滮�����飬���еľ���ֵ������Ϊһ���ܴ����
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX / 2));
        // ��� (i, j) ��Ԫ��Ϊ 0����ô����Ϊ 0
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                }
            }
        }
        // ֻ�� ˮƽ�����ƶ� �� ��ֱ�����ƶ���ע�⶯̬�滮�ļ���˳��
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                }
                if (j - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }
        // ֻ�� ˮƽ�����ƶ� �� ��ֱ�����ƶ���ע�⶯̬�滮�ļ���˳��
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i + 1 < m) {
                    dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                }
                if (j + 1 < n) {
                    dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
                }
            }
        }
        return dist;
    }
};

//���õ�����
class Solution 
{
private:
    static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
public:
    int orangesRotting(vector<vector<int>>& grid)
    {
        int row = grid.size(), col = grid[0].size();
        queue<pair<int, int>> q;
        int time = 0;
        // �����е� 2 ��ӽ���ʼ������
        for (int i = 0; i < row; ++i) 
        {
            for (int j = 0; j < col; ++j) 
            {
                if (grid[i][j] == 2) 
                {
                    q.push({ i,j });
                }
            }
        }
        if (!q.empty())
        {
            bool noGood = true;
            for (int i = 0; i < row; i++)
            {
                if (find(grid[i].begin(), grid[i].end(), 1) != grid[i].end())//������û��1��ֱ�ӷ���0
                {
                    noGood = false;
                    break;
                }
            }
            if (noGood)
                return 0;
        }
        else if (q.empty())
        {
            for (int i = 0; i < row; i++)//������û�л����ӵ��к����ӣ�����-1
            {
                if (find(grid[i].begin(), grid[i].end(), 1) != grid[i].end())
                    return -1;
            }
            return 0;//������ֻ�пո񷵻�0
        }
        // �����������
        while (!q.empty())
        {
            bool isPush = false;
            int n = q.size();
            for (int k = 0; k < n; k++)
            {

                auto [i, j] = q.front();
                q.pop();
                for (int d = 0; d < 4; ++d)
                {
                    int ni = i + dirs[d][0];
                    int nj = j + dirs[d][1];
                    if (ni >= 0 && ni < row && nj >= 0 && nj < col && grid[ni][nj] == 1)
                    {
                        grid[ni][nj] = 2;
                        q.emplace(ni, nj);
                        isPush = true;
                    }
                }
            }
            if (isPush)
                time++;
        }
        for (int i = 0; i < row; i++)
        {
            if (find(grid[i].begin(), grid[i].end(), 1) != grid[i].end())
                return -1;
        }
       
        return time;  
    }
};

//�ٽ�BFS��������
class Solution {
    int cnt;
    int dis[10][10];
    int dir_x[4] = { 0, 1, 0, -1 };
    int dir_y[4] = { 1, 0, -1, 0 };
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int, int> >Q;
        memset(dis, -1, sizeof(dis));
        cnt = 0;
        int n = (int)grid.size(), m = (int)grid[0].size(), ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 2) {
                    Q.push(make_pair(i, j));
                    dis[i][j] = 0;
                }
                else if (grid[i][j] == 1) cnt += 1;
            }
        }
        while (!Q.empty()) {
            pair<int, int> x = Q.front(); Q.pop();
            for (int i = 0; i < 4; ++i) {
                int tx = x.first + dir_x[i];
                int ty = x.second + dir_y[i];
                if (tx < 0 || tx >= n || ty < 0 || ty >= m || ~dis[tx][ty] || !grid[tx][ty]) continue;
                dis[tx][ty] = dis[x.first][x.second] + 1;
                Q.push(make_pair(tx, ty));
                if (grid[tx][ty] == 1) {
                    cnt -= 1;
                    ans = dis[tx][ty];
                    if (!cnt) break;
                }
            }
        }
        return cnt ? -1 : ans;
    }
};


