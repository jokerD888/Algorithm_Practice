// 212. 单词搜索 II
//
// 暴力，超时
class Solution {
public:
    unordered_set<string> res;
    void dfs(vector<vector<char>>& board, int r, int c, string& s) {
        if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] == 'A') return;
        s += board[r][c];
        res.insert(s);

        board[r][c] = 'A';
        static int dire[]{ -1,0,1,0,-1 };
        for (int i = 0; i < 4; ++i) {
            int x = r + dire[i], y = c + dire[i + 1];
            dfs(board, x, y, s);
        }
        board[r][c] = s.back();
        s.pop_back();

    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        unordered_map<char, vector<string>> mp;
        for (auto s : words) {
            mp[s[0]].push_back(s);
        }
        int N = board.size(), M = board[0].size();
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (mp.count(board[i][j])) {
                    string s;
                    dfs(board, i, j, s);
                }
            }
        }
        vector<string> ans;
        for (auto s : words) {
            if (res.count(s)) {
                ans.push_back(s);
            }
        }
        return ans;
    }

};


// 前缀树优化
class Solution {
public:
    class TrieNode {
    public:
        TrieNode* nexts[26];
        int pass;       // 经过的次数
        bool end;       // 是否以该位置结束

        TrieNode() : pass(0), end(false) {
            for (int i = 0; i < 26; ++i) {
                nexts[i] = nullptr;             // 置空
            }
        }
        ~TrieNode() { 
            for (int i = 0; i < 26; ++i)
                if (nexts[i]) delete nexts[i];
        }
    };
    void insert(TrieNode* head, string& s) {        // 前缀树插入节点
        head->pass++;                       
        int len = s.size(), index = 0;
        TrieNode* node = head;

        for (int i = 0; i < len; ++i) {
            index = s[i] - 'a';
            if (node->nexts[index] == nullptr) {        // 没后续的路，新建
                node->nexts[index] = new TrieNode();
            }
            node = node->nexts[index];      // 往下走
            node->pass++;
        }
        node->end = true;       // 以该位置结尾
    }
    vector<string> res;
    int dfs(vector<vector<char>>& board, int r, int c, string& path, TrieNode* cur) {
        // 无效路径
        if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] == 'A') return 0;
        // 不是想要的字符 或 该路径以收集完毕
        int index = board[r][c] - 'a';
        if (cur->nexts[index] == nullptr || cur->nexts[index]->pass == 0) return 0;

        path += board[r][c];

        cur = cur->nexts[index];    // 来到相应的节点
        board[r][c] = 'A';          // 标记，防止成环
        int fix = 0;        // 从该位置出发，后续一定搞定了多少个答案

        if (cur->end) {     // 该位置是一个字符串的终点
            res.push_back(path);
            cur->end = false;
            ++fix;      // 注意这点，别忘了
        }

        static int dire[]{ -1,0,1,0,-1 };
        for (int i = 0; i < 4; ++i) {
            int x = r + dire[i], y = c + dire[i + 1];
            fix += dfs(board, x, y, path, cur);
        }
        board[r][c] = path.back();  // 回溯
        path.pop_back();    
        cur->pass -= fix;
        return fix;

    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* head = new TrieNode;
        for (auto& s : words) {
            insert(head, s);
        }

        int N = board.size(), M = board[0].size();
        string path;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                dfs(board, i, j, path, head);
            }
        }

        return res;
    }

};


// 1790. 仅执行一次字符串交换能否使两个字符串相等
class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        int N = s1.size();
        for (int i = 0; i < N; ++i) {
            if (s1[i] != s2[i]) {
                int j = i + 1;
                while (j < N && (s1[j] != s2[i] || s1[i] != s2[j])) ++j;
                if (j == N) return false;
                swap(s1[i], s1[j]);
                break;
            }
        }
        return s1 == s2;
    }
};
