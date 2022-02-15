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

    void dfs1(vector<int>& candidates, int rest, vector<vector<int>>& ans, vector<int>& combine, int index) {
        if (index == candidates.size()) {
            if (rest == 0) {
                ans.emplace_back(combine);
            }
            return;
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> combine;
        dfs(candidates, target, ans, combine, 0);
        return ans;
    }
};


//540. ���������еĵ�һԪ��
//��һ���������������ͬ���������Ϊ0���Ҳ���������˳��
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int ret = 0;
        for (auto n : nums) {
            ret ^= n;
        }
        return ret;
    }
};

��������������������Ϊ���������ַ�
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
      
        int n = nums.size();
        int left = 0, right = nums.size()-1,mid;
        while (1) {
            mid = (right-left) / 2 + left;
            if (mid >= 1 &&  nums[mid] == nums[mid - 1]  ) {
                if ((mid - left) % 2) { //[left..mid)����Ϊ����
                    left = mid+1;
                } else {                 //[left..mid)����Ϊż��
                    right = mid;
                }
            } else if ( mid <= n - 2 && nums[mid] == nums[mid + 1] ) {
                if ((mid - left) % 2) {  //��mid..right]����Ϊ����
                    right=mid-1;
                } else {                  //(left..right]����ż��
                    left = mid;
                }
            } else {
                //mid��Ϊ��һԪ��λ��
                return nums[mid];
            }
        }
        return 0;
    }
};


//������ȫ����Ķ��ֲ���
// ����x�ǵ�һԪ���±꣬��x����ߵ����꣬���nums[y]==nums[y+1],yһ����ż��
//                    ��x���ұߵ����꣬���nums[z]==nums[z+1],zһ��������
// �����±� x ����ͬԪ�صĿ�ʼ�±����ż�Եķֽ磬��˿���ʹ�ö��ֲ��ҵķ���Ѱ���±� x��
// ����������������
//mid Ϊ���� mid-1=mid^1
//mid Ϊż�� mid+1=mid^1
//
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            int mid = (high - low) / 2 + low;
            //��midΪż���Ƚ�mid��mid+1�������˵�����ұߣ��������
            //��midΪ�棬�Ƚ�mid��mid-1,�����˵�����ұߣ����������
            if (nums[mid] == nums[mid ^ 1]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return nums[low];
    }
};

//�����ģ�ż���±�Ķ��ֲ���
//��һԪ�ص��±�xһ����ż����ֻҪ��ż���±��ж�nums[x]==nums[x+1] ��С�߽�
//mid ż mid&1=0;
//mid �� mid&1=1;
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            int mid = (high - low) / 2 + low;
            //ȷ��midһ����ż��
            mid -= mid & 1;
            if (nums[mid] == nums[mid + 1]) {
                low = mid + 2;      //����+2��Ϊ�˽���ʼ��Χ��С����һ��ż��
            } else {
                high = mid;
            }
        }
        return nums[low];
    }
};



//1380. �����е�������
// 
//��һ��ģ��
class Solution {
public:
    vector<int> luckyNumbers(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> ret;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                bool isMin = true, isMax = true;
                for (int k = 0; k < n; k++) {
                    if (matrix[i][k] < matrix[i][j]) {
                        isMin = false;
                        break;
                    }
                }
                if (!isMin) {
                    continue;
                }
                for (int k = 0; k < m; k++) {
                    if (matrix[k][j] > matrix[i][j]) {
                        isMax = false;
                        break;
                    }
                }
                if (isMax) {
                    ret.push_back(matrix[i][j]);
                }
            }
        }
        return ret;
    }
};
//������Ԥ����
//�����ҳ����и�������С����Ԫ�أ�������matrix���鿴�Ƿ����Ҫ��
class Solution {
public:
    vector<int> luckyNumbers(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> row, col;
        vector<int> ret;
        for (int i = 0; i < m; ++i) {
            int minNum = INT_MAX;
            for (int j = 0; j < n; ++j) {
                minNum = min(minNum, matrix[i][j]);
            }
            row.push_back(minNum);
        }
        for (int i = 0; i < n; ++i) {
            int maxNum = INT_MIN;
            for (int j = 0; j < m; ++j) {
                maxNum = max(maxNum, matrix[j][i]);
            }
            col.push_back(maxNum);
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == row[i] && matrix[i][j] == col[j]) {
                    ret.push_back(matrix[i][j]);
                }
            }
        }
        return ret;
    }
};

//��
class Solution {
public:
    vector<int> luckyNumbers(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> row(m,INT_MAX), col(n);//��С��1
        vector<int> ret;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                row[i] = min(row[i], matrix[i][j]);
                col[j] = max(col[j], matrix[i][j]);
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == row[i] && matrix[i][j] == col[j]) {
                    ret.push_back(matrix[i][j]);
                }
            }
        }
        return ret;
    }
};

