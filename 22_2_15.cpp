//39. 组合总和
//递归回溯
//对于每个数字，可以选择多次，直到相加大于等于target，则退出当前路径搜索
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

        // 直接跳过
        dfs(candidates, target, ans, combine, idx + 1);
        // 选择当前数
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


//540. 有序数组中的单一元素
//法一：利用异或，两个相同的数异或完为0，且不限制异或的顺序
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

法二：依题意给定数组必为奇数，二分法
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
      
        int n = nums.size();
        int left = 0, right = nums.size()-1,mid;
        while (1) {
            mid = (right-left) / 2 + left;
            if (mid >= 1 &&  nums[mid] == nums[mid - 1]  ) {
                if ((mid - left) % 2) { //[left..mid)个数为奇数
                    left = mid+1;
                } else {                 //[left..mid)个数为偶数
                    right = mid;
                }
            } else if ( mid <= n - 2 && nums[mid] == nums[mid + 1] ) {
                if ((mid - left) % 2) {  //（mid..right]个数为奇数
                    right=mid-1;
                } else {                  //(left..right]个数偶数
                    left = mid;
                }
            } else {
                //mid即为单一元素位置
                return nums[mid];
            }
        }
        return 0;
    }
};


//法三：全数组的二分查找
// 假设x是单一元素下标，则x的左边的坐标，如果nums[y]==nums[y+1],y一定是偶数
//                    则x的右边的坐标，如果nums[z]==nums[z+1],z一定是奇数
// 由于下标 x 是相同元素的开始下标的奇偶性的分界，因此可以使用二分查找的方法寻找下标 x。
// 利用以下异或的特性
//mid 为奇数 mid-1=mid^1
//mid 为偶数 mid+1=mid^1
//
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            int mid = (high - low) / 2 + low;
            //若mid为偶，比较mid和mid+1，若相等说明在右边，否则左边
            //若mid为奇，比较mid和mid-1,若相等说明在右边，否则在左边
            if (nums[mid] == nums[mid ^ 1]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return nums[low];
    }
};

//方法四：偶数下标的二分查找
//单一元素的下标x一定是偶数，只要在偶数下标判断nums[x]==nums[x+1] 缩小边界
//mid 偶 mid&1=0;
//mid 奇 mid&1=1;
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            int mid = (high - low) / 2 + low;
            //确保mid一定是偶数
            mid -= mid & 1;
            if (nums[mid] == nums[mid + 1]) {
                low = mid + 2;      //这里+2是为了将开始范围缩小到下一个偶数
            } else {
                high = mid;
            }
        }
        return nums[low];
    }
};



//1380. 矩阵中的幸运数
// 
//法一：模拟
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
//法二：预处理
//各自找出各行各列中最小最大的元素，随后遍历matrix，查看是否符合要求
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

//或
class Solution {
public:
    vector<int> luckyNumbers(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> row(m,INT_MAX), col(n);//最小是1
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

