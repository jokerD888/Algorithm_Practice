//1405. ������ַ���
//������������ͬ����ĸ�������֣��ʾ���������ʹ�õ�ǰ����������ĸ��
//��Ϊ���ͬһ����ĸʣ���Խ�࣬Խ���׳�����ĸ������ͬ�������
//���δӵ�ǰ����������ĸ��ʼ���ԣ�������ּ��뵱ǰ��ĸ�ᵼ�³�������������ͬ��ĸ��
//��������ǰ��ĸ��ֱ�������ҵ�������ӵ���ĸΪֹ��
//����������е���ĸ���޷���ӣ���ֱ���˳�����ʱ���ɵ��ַ�����Ϊ��Ŀ����ַ�����
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        string res;
        vector<pair<int, char>> arr = { {a, 'a'}, {b, 'b'}, {c, 'c'} };

        while (true) {
            //����ĸ�����Ž���
            sort(arr.begin(), arr.end(), [](const pair<int, char>& p1, const pair<int, char>& p2) {
                return p1.first > p2.first;
                });
            bool hasNext = false;
            for (auto& [freq, ch] : arr) {
                int m = res.size();
                //��ĸ�ù�
                if (freq <= 0) {    
                    break;
                }
                //����������ͬ����ĸ
                if (m >= 2 && res[m - 2] == ch && res[m - 1] == ch) {
                    continue;
                }
                hasNext = true;
                res.push_back(ch);
                freq--;
                break;
            }
            //ʣ�µ�������ĸ���޷������
            if (!hasNext) {
                break;
            }
        }

        return res;
    }
};


//������
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        // greedy
        string ans;
        while (a + b + c > 0) {
            char choose = '-';
            int chlen = 0;
            int xsize = ans.size();
            //һ������if��ѡ������ĸ��һ��
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
            if (choose == '-') break;   //û��ѡ���˳�
            ans+=choose;      //����������ĸ����ĸ
            if (choose == 'a') a--;
            else if (choose == 'b') b--;
            else if (choose == 'c') c--;
        }
        return ans;
    }
};


//47. ȫ���� II
//�������ظ�Ԫ����ȫ���У���Ҫע�������ô��������ظ������н��
//���磺 1 1 1 2 ��������ͬ��1������1�ֱ���a,b,c��Ҫ��ó����ظ���ȫ�����У���Ҫ����ͬ������ֵ�˳������Լ��
//�磺�����ĸ�1�������������1�ĳ���˳�򶼵���a,b,c��ֻҪ�涨һ���̶�˳�򼴿ɣ�
//������a,b,c��������1 ������     a,b,c,2     2,a,b,c     a,2,b,c     a,b,2,c     
//��                            1,1,1,2      2,1,1,1     1,2,1,1     1,1,2,1
//����ѡ���ԭ�������򣬱�֤��ͬ�����ֶ����ڣ�Ȼ��ÿ���������һ��������������ظ��������С��������ҵ�һ��δ����������֡�
class Solution {
    vector<int> vis;

public:
    void backtrack(vector<int>& nums, vector<vector<int>>& ans, int idx, vector<int>& perm) {
        if (idx == nums.size()) {
            ans.emplace_back(perm);
            return;
        }
        for (int i = 0; i < (int)nums.size(); ++i) {
            //��nums�����λ�õ�����ѡ��  �������λ�õ�����
            //�� �������֮ǰ��ͬ�����ֻ�δ��ѡ����Ϊ�˱�֤ѡȡ��˳��  �������λ�õ�˳��
            if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
                continue;
            }
            perm.emplace_back(nums[i]);
            vis[i] = 1;
            backtrack(nums, ans, idx + 1, perm);
            vis[i] = 0;     //����
            perm.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> perm;
        vis.resize(nums.size());
        sort(nums.begin(), nums.end()); //��������Լ��ѡȡ˳��
        backtrack(nums, ans, 0, perm);
        return ans;
    }
};

