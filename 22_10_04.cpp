// 134. 加油站
// 明显我们可以得知，若x到不了y+1（但能到y),那么从x到y的任一点都不可能到达y+1.
// 因为从其中任一点出发的话，相当于从0开始加油，而如果从x出发到该点则不一定是从0开始加油，可能还有剩余的油。
// 既然不从0开始都到不了y+1，那么从0开始就更不可能到达y+1了...
// 所以枚举每个可能的位置，每次遇到不合法位置后，就从不合法的位置重新开始，每个位置最多只会遍历两次，时间O(N)
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int rest = 0;
        int N = gas.size();
        for (int i = 0; i < N; ++i) {   // 枚举每个可能的位置
            int j = i;
            while (rest >= 0) {
                if (j != i && j % N == i) return i;
                rest += gas[j % N];
                rest -= cost[j % N];
                ++j;
            }
            rest = 0;
            i = j - 1;
        }
        return -1;
    }
};

// 140. 单词拆分 II
// 暴力
class Solution {
public:
    unordered_set<string> hs;
    vector<string> res;
    void dfs(string& s, int start, string path) {
        if (start == s.size()) {
            path.pop_back();
            res.push_back(path);
        }
        for (int i = start + 1; i <= s.size(); ++i) {
            if (hs.count(s.substr(start, i - start))) {
                dfs(s, i, path + s.substr(start, i - start) + ' ');
            }
        }
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        for (auto& s : wordDict) {
            hs.insert(s);
        }
        dfs(s, 0, "");
        return res;
    }
};
// 记忆化优化
class Solution {
private:
    unordered_map<int, vector<string>> ans;
    unordered_set<string> wordSet;

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        wordSet = unordered_set(wordDict.begin(), wordDict.end());
        dfs(s, 0);
        return ans[0];
    }

    void dfs(const string& s, int index) {
        if (!ans.count(index)) {
            if (index == s.size()) {
                ans[index] = { "" };
                return;
            }
            ans[index] = {};
            for (int i = index + 1; i <= s.size(); ++i) {
                string word = s.substr(index, i - index);
                if (wordSet.count(word)) {
                    dfs(s, i);
                    for (const string& succ : ans[i]) {
                        ans[index].push_back(succ.empty() ? word : word + " " + succ);
                    }
                }
            }
        }
    }
};
