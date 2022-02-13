//1189. ������ ���������
//��һ�����ù�ϣ��ͳ��ballon���ʳ��ָ������ҳ���С�������ؼ���
class Solution {
public:
    int maxNumberOfBalloons(string text) {
        map<char, int> m = { {'b',0},{'a',0},{'l',0},{'o',0},{'n',0}, };
        string k("balon");
        for (auto c : text) {
            if(k.find(c)!=k.npos)
                ++m[c];
        }
        //��balloon���ظ�����
        m['l'] /= 2;    
        m['o'] /= 2;
        int ret = INT_MAX;
        for (auto kv : m) {
            ret = min(ret, kv.second);
        }
        return ret;
    }
};
//��
class Solution {
public:
    int maxNumberOfBalloons(string text) {
        vector<int> cnt(5);
        for (auto& ch : text) {
            if (ch == 'b') {
                cnt[0]++;
            } else if (ch == 'a') {
                cnt[1]++;
            } else if (ch == 'l') {
                cnt[2]++;
            } else if (ch == 'o') {
                cnt[3]++;
            } else if (ch == 'n') {
                cnt[4]++;
            }
        }
        cnt[2] /= 2;
        cnt[3] /= 2;
        return *min_element(cnt.begin(), cnt.end());
    }
};

//39. ����ܺ�
//�ݹ����
//����ÿ�����֣�����ѡ���Σ�ֱ����Ӵ��ڵ���target�����˳���ǰ·������
class Solution {
public:
    void dfs(vector<int>& candidates, int target, vector<vector<int>>& ans, vector<int>& combine, int idx) {
        if (idx == candidates.size()) {
            return;
        }
        if (target == 0) {
            ans.emplace_back(combine);
            return;
        }

        // ֱ������
        dfs(candidates, target, ans, combine, idx + 1);
        // ѡ��ǰ��
        if (target - candidates[idx] >= 0) {
            combine.emplace_back(candidates[idx]);
            dfs(candidates, target - candidates[idx], ans, combine, idx);
            combine.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> combine;
        dfs(candidates, target, ans, combine, 0);
        return ans;
    }
};


