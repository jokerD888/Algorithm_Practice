//2006. ��ľ���ֵΪ K ��������Ŀ
//��һ����ֵ��Χ��С��ֱ�Ӽ�¼���ֳ��ִ��������μ��k��������arr[i]��arr[i+k]�Ƿ񶼲�Ϊ0
class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
        int arr[101] = { 0 };
        for (auto n : nums) {
            ++arr[n];
        }
        int ret = 0;
        for (int i = 0; i < 101-k; ++i) {
            if (arr[i] && arr[i + k]) {
                ret =ret+ arr[i] * arr[i + k];
            }
        }
        return ret;
    }
};

//����������
class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
        int res = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (abs(nums[i] - nums[j]) == k) {
                    ++res;
                }
            }
        }
        return res;
    }
};


//1447. ������
//��һ�����Լ��+���
class Solution {
    int measure(int x, int y)
    {
        int z = y;
        while (y)
        {			
            z = x % y;      
            x = y;          
            y = z;
        }
        return x;
    }
public:   
    vector<string> simplifiedFractions(int n) {
        vector<string> ret;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                if (measure(i,j)!=1) {
                    continue;
                }
                ret.push_back(to_string(j) + "/" + to_string(i));
            }
        }
        return ret;
    }
};
//��ʹ�ÿ�gcd
class Solution {
public:
    vector<string> simplifiedFractions(int n) {
        vector<string> ret;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                if (gcd(i, j) != 1) {
                    continue;
                }
                ret.push_back(to_string(j) + "/" + to_string(i));
            }
        }
        return ret;
    }
};


//1984. ѧ����������С��ֵ
//����+˫ָ��
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int L=0, R=k-1;
        int ret = INT_MAX;
        for (; R < nums.size(); ++L, ++R) {
            ret = min(ret, nums[R] - nums[L]);
        }
        return ret;
    }
};
