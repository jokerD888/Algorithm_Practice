// 118. 杨辉三角
// 模拟
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows);
        for (int i = 0; i < numRows; ++i) {
            res[i].resize(i + 1, 1);
            if (i < 2) continue;
            for (int j = i - 1; j; --j) {
                res[i][j] = res[i - 1][j] + res[i - 1][j - 1];
            }
        }
        return res;
    }
};


// 130. 被围绕的区域
// dfs
class Solution {
public:

    void dfs(vector<vector<char>>& board, int x, int y) {
        int n = board.size(), m = board[0].size();
        static int dire[]{ -1,0,1,0,-1 };
        if (board[x][y] !='O') return;
        if (board[x][y] == 'O') {
            board[x][y] = 'P';
        }
        for (int i = 0; i < 4; ++i) {
            int xx = x + dire[i], yy = y + dire[i+1];
            if (xx >= 0 && xx < n && yy >= 0 && yy < m && board[xx][yy] == 'O')
                dfs(board, xx, yy);
        }
    }
    void solve(vector<vector<char>>& board) {
        int n = board.size(), m = board[0].size();
        for (int i = 0; i < n; ++i) {
            dfs(board, i, 0);
            dfs(board, i, m - 1);
        }
        for (int j = 1; j < m - 1; ++j) {
            dfs(board, 0, j);
            dfs(board, n - 1, j);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (board[i][j] == 'P') board[i][j] = 'O';
                else if (board[i][j] == 'O') board[i][j] = 'X';
            }
        }

    }
};