
// 2341. 数组能形成多少数对
// 简单题，直接做
class Solution {
public:
    vector<int> numberOfPairs(vector<int>& nums) {
        vector<int> a(101);
        int x = 0, y = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (++a[nums[i]] == 2) {
                ++x;
                a[nums[i]] = 0;
            }
        }
        for (int i = 0; i < 101; ++i) {
            if (a[i]) ++y;
        }
        return { x,y };
    }
};



// 1138. 字母板上的路径
// 本题并不难，只需要根据target遍历，每次从一个点找打令一个点，由于路径不限，所以可以根据两个点的坐标来判断方向
// 但字母'z'单独一个，所以需要特殊处理，可以发现，不论是到达'z'还是从'z'出发，都要经过上面的字母u,所以可以将'z'变换到'u'
class Solution {
public:
    string get_path(int a, int b) {
        if (a == b) {
            return "!";
        }
        string res;

        if (a == 25) {
            res += 'U';
            a=20;
        }
        bool flag = false;
        if (b == 25) {
            flag = true;
            b=20;
        }

        int xa = a / 5, ya = a % 5;
        int xb = b / 5, yb = b % 5;

        if (yb > ya) {
            for (int i = 0; i < yb - ya; ++i) res += 'R';
        } else if (yb < ya) {
            for (int i = 0; i < ya - yb; ++i) res += 'L';
        }

        if (xb > xa) {
            for (int i = 0; i < xb - xa; ++i) res += 'D';
        } else if (xb < xa) {
            for (int i = 0; i < xa - xb; ++i) res += 'U';
        }
        
        if (flag) res += 'D';
        res += '!';
        return res;

    }
    string alphabetBoardPath(string target) {
        string res;
        int cur = 0;
        for (auto c : target) {
            int t = c - 'a';
            res+= get_path(cur, t);
            cur = t;
        }
        return res;
    }
};