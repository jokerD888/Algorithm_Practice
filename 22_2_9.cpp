//1405. 最长快乐字符串
//因不能有三个相同的字母连续出现，故尽可能优先使用当前数量最多的字母，
//因为最后同一种字母剩余的越多，越容易出现字母连续相同的情况。
//依次从当前数量最多的字母开始尝试，如果发现加入当前字母会导致出现三个连续相同字母，
//则跳过当前字母，直到我们找到可以添加的字母为止。
//如果尝试所有的字母都无法添加，则直接退出，此时构成的字符串即为最长的快乐字符串。
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        string res;
        vector<pair<int, char>> arr = { {a, 'a'}, {b, 'b'}, {c, 'c'} };

        while (true) {
            //按字母数量排降序
            sort(arr.begin(), arr.end(), [](const pair<int, char>& p1, const pair<int, char>& p2) {
                return p1.first > p2.first;
                });
            bool hasNext = false;
            for (auto& [freq, ch] : arr) {
                int m = res.size();
                //字母用光
                if (freq <= 0) {    
                    break;
                }
                //三个连续相同的字母
                if (m >= 2 && res[m - 2] == ch && res[m - 1] == ch) {
                    continue;
                }
                hasNext = true;
                res.push_back(ch);
                freq--;
                break;
            }
            //剩下的所有字母都无法再添加
            if (!hasNext) {
                break;
            }
        }

        return res;
    }
};


//或类似
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        // greedy
        string ans;
        while (a + b + c > 0) {
            char choose = '-';
            int chlen = 0;
            int xsize = ans.size();
            //一下三个if是选出多字母那一组
            if (a > chlen && (xsize < 2 || ans[xsize - 1] != 'a' || ans[xsize - 2] != 'a')) {
                chlen = a;
                choose = 'a';
            }
            if (b > chlen && (xsize < 2 || ans[xsize - 1] != 'b' || ans[xsize - 2] != 'b')) {
                chlen = b;
                choose = 'b';
            }
            if (c > chlen && (xsize < 2 || ans[xsize - 1] != 'c' || ans[xsize - 2] != 'c')) {
                chlen = c;
                choose = 'c';
            }
            if (choose == '-') break;   //没得选择，退出
            ans+=choose;      //添加上最多字母的字母
            if (choose == 'a') a--;
            else if (choose == 'b') b--;
            else if (choose == 'c') c--;
        }
        return ans;
    }
};


//47. 全排列 II
//对于有重复元素求全排列，需要注意的是怎么避免出现重复的排列结果
//例如： 1 1 1 2 有三个相同的1，三个1分别标号a,b,c，要想得出不重复的全部排列，就要对相同数组出现的顺序做出约束
//如：不论哪个1在哪里，最终三个1的出现顺序都得是a,b,c（只要规定一个固定顺序即可）
//假设用a,b,c代替三个1 得排列     a,b,c,2     2,a,b,c     a,2,b,c     a,b,2,c     
//即                            1,1,1,2      2,1,1,1     1,2,1,1     1,1,2,1
//我们选择对原数组排序，保证相同的数字都相邻，然后每次填入的数一定是这个数所在重复数集合中「从左往右第一个未被填过的数字」
class Solution {
    vector<int> vis;

public:
    void backtrack(vector<int>& nums, vector<vector<int>>& ans, int idx, vector<int>& perm) {
        if (idx == nums.size()) {
            ans.emplace_back(perm);
            return;
        }
        for (int i = 0; i < (int)nums.size(); ++i) {
            //若nums中这个位置的数字选过  跳过这个位置的数字
            //或 这个数字之前相同的数字还未被选过，为了保证选取的顺序  跳过这个位置的顺序
            if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
                continue;
            }
            perm.emplace_back(nums[i]);
            vis[i] = 1;
            backtrack(nums, ans, idx + 1, perm);
            vis[i] = 0;     //回溯
            perm.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> perm;
        vis.resize(nums.size());
        sort(nums.begin(), nums.end()); //排序，用于约束选取顺序
        backtrack(nums, ans, 0, perm);
        return ans;
    }
};

