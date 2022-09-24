// 36. 有效的数独
// 遍历+位运算
// 对于每行每列每个九宫格，我们都可以用一个整数上的位信息来表示
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row[9] = { 0 };
        int col[9] = { 0 };
        int squares[3][3] = { 0 };

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                int k = board[i][j] - '0' - 1;
                if (board[i][j] != '.') {
                    if ((row[i] >> k) & 1 || (col[j] >> k) & 1 || (squares[i / 3][j / 3] >> k) & 1) {
                        return false;
                    } else {
                        row[i] += (1 << k);
                        col[j] += (1 << k);
                        squares[i / 3][j / 3] += (1 << k);
                    }

                }
            }
        }
        return true;
    }
};

//38. 外观数列
class Solution {
public:
    string countAndSay(int n) {
        string s = "1";
        for (int i = 2; i <= n; ++i) {
            int len = s.size();
            int cnt = 0, j = 0;
            string t;
            while (j < len) {
                cnt = 1;
                while (j + 1 < len && s[j + 1] == s[j]) {
                    ++j;
                    ++cnt;
                }
                t += cnt + '0';
                t += s[j];
                ++j;
            }
            s = t;
        }
        return s;
    }
};
