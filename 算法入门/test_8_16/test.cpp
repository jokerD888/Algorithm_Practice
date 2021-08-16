#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<vector>
#include<queue>
#include<stack>
//BFS/DFS


//733. 图像渲染
//DFS
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor)
    {
        if (image[sr][sc] == newColor)
            return image;
        int oldColor = image[sr][sc];
        image[sr][sc] = newColor;

        if (sr - 1 >= 0 && sc >= 0 && image[sr - 1][sc] == oldColor)
        {
            floodFill(image, sr - 1, sc, newColor);
        }
        if (sr + 1 >= 0 && sr + 1 < image.size() && sc >= 0 && image[sr + 1][sc] == oldColor)
        {
            floodFill(image, sr + 1, sc, newColor);
        }
        if (sr >= 0 && sc - 1 >= 0 && image[sr][sc - 1] == oldColor)
        {
            floodFill(image, sr, sc - 1, newColor);
        }
        if (sr >= 0 && sc + 1 >= 0 && sc + 1 < image[0].size() && image[sr][sc + 1] == oldColor)
        {
            floodFill(image, sr, sc + 1, newColor);
        }
        return image;
    }
};
//或
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor)
    {
        if (image[sr][sc] == newColor)
            return image;
        helper(image, sr, sc, newColor, image[sr][sc]);
        return image;
    }
    void helper(vector<vector<int>> image, int sr, int sc, int newColor, int oldColor)
    {
        if (sr < 0 || sc < 0 || sr == image.size() || sc == image[0].size()
            || image[sr][sc] != oldColor)
            return;
        helper(image, sr - 1, sc, newColor, oldColor);
        helper(image, sr + 1, sc, newColor, oldColor);
        helper(image, sr, sc - 1, newColor, oldColor);
        helper(image, sr, sc + 1, newColor, oldColor);
    }
};

//BFS官解
//借助队列实现广度优先遍历
class Solution 
{
public:
    const int dx[4] = { 1, 0, 0, -1 };//两个数组,便于上下左右移动
    const int dy[4] = { 0, 1, -1, 0 };
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int currColor = image[sr][sc];
        if (currColor == newColor) return image; 
        int n = image.size(), m = image[0].size();
        queue<pair<int, int>> que;
        que.emplace(sr, sc);
        image[sr][sc] = newColor;
        while (!que.empty()) 
        {
            int x = que.front().first, y = que.front().second;
            que.pop();
            for (int i = 0; i < 4; i++) {
                int mx = x + dx[i], my = y + dy[i];
                if (mx >= 0 && mx < n && my >= 0 && my < m && image[mx][my] == currColor) {
                    que.emplace(mx, my);
                    image[mx][my] = newColor;
                }
            }
        }
        return image;
    }
};


//695. 岛屿的最大面积
//DFS
class Solution {
public:
    const int dx[4] = { 1, 0, 0, -1 };//两个数组,便于上下左右移动
    const int dy[4] = { 0, 1, -1, 0 };
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxArea = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            int j = 0;
            for (; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    maxArea = max(maxArea, helper(grid, i, j));
                }
            }
        }
        return maxArea;
    }

    int helper(vector<vector<int>>& grid, int x, int y)
    {
        int num = 1, n = grid.size(), m = grid[0].size();
        grid[x][y] = 0;
        for (int i = 0; i < 4; i++)
        {
            int mx = x + dx[i], my = y + dy[i];
            if (mx >= 0 && mx < n && my >= 0 && my < m && grid[mx][my] == 1)
            {

                num += helper(grid, mx, my);
            }
        }
        return num;
    }
};

//BFS
//以队中连续弹出的个数即为最大土地个数
class Solution {
public:
    const int dx[4] = { 1, 0, 0, -1 };//两个数组,便于上下左右移动
    const int dy[4] = { 0, 1, -1, 0 };
    int maxAreaOfIsland(vector<vector<int>>& grid)
    {
        int maxArea = 0, n = grid.size(), m = grid[0].size();
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++)
        {
            int j = 0;
            for (; j < m; j++)
            {
                if (grid[i][j] == 1)
                {
                    int num = 0;
                    q.emplace(i, j);
                    grid[i][j] = 0;
                    while (!q.empty())
                    {
                        int x = q.front().first, y = q.front().second;
                        q.pop();
                        num++;
                        for (int i = 0; i < 4; i++) 
                        {
                            int mx = x + dx[i], my = y + dy[i];
                            if (mx >= 0 && mx < n && my >= 0 && my < m && grid[mx][my] == 1) 
                            {
                                q.emplace(mx, my);
                                grid[mx][my] = 0;
                            }
                        }
                    }
                    maxArea = max(maxArea, num);
                }

            }
        }
        return maxArea;

    }
};


//官解DFS/BFS与上类似
//解法3
//DFS+栈
//与法一类似，不同的是用栈来表示函数的递归
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) 
    {
        int ans = 0;
        for (int i = 0; i != grid.size(); ++i) 
        {
            for (int j = 0; j != grid[0].size(); ++j) 
            {
                int cur = 0;
                stack<int> stacki;
                stack<int> stackj;
                stacki.push(i);
                stackj.push(j);
                while (!stacki.empty()) 
                {
                    int cur_i = stacki.top(), cur_j = stackj.top();
                    stacki.pop();
                    stackj.pop();
                    if (cur_i < 0 || cur_j < 0 || cur_i == grid.size() || cur_j == grid[0].size() || grid[cur_i][cur_j] != 1) 
                    {
                        continue;
                    }
                    ++cur;
                    grid[cur_i][cur_j] = 0;
                    int di[4] = { 0, 0, 1, -1 };
                    int dj[4] = { 1, -1, 0, 0 };
                    for (int index = 0; index != 4; ++index) 
                    {
                        int next_i = cur_i + di[index], next_j = cur_j + dj[index];
                        stacki.push(next_i);
                        stackj.push(next_j);
                    }
                }
                ans = max(ans, cur);
            }
        }
        return ans;
    }
};
