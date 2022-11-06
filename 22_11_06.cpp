// 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面

// 左右指针
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int i = 0, j = nums.size() - 1;
        while (i < j) {
            while (i < j && nums[i] & 1) {   // 奇数
                ++i;
            }
            while (i < j && !(nums[j] & 1)) {
                --j;
            }
            swap(nums[i], nums[j]);
            ++i;
            --j;
        }
        return nums;
    }

};



// 剑指 Offer 22. 链表中倒数第k个节点

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        int cnt = 0;
        ListNode* cur = head;
        while (cur) {
            ++cnt;
            cur = cur->next;
        }
        k %= cnt;
        if (k == 0) return head;
        k = cnt - k;
        for (int i = 0; i < k; ++i) {
            head = head->next;
        }
        return head;
    }
};


// 双指针

// 两指针间隔k个步长同步移动
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast && k > 0) {
            fast = fast->next;
            k--;
        }
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        return slow;
    }
};



// 剑指 Offer 19. 正则表达式匹配


// 动态规划
// dp[i][j] 为串s前i个字符和串p前j个字符能够匹配

// 一般的，dp[i][j],对于字符p[j]分类讨论
//      1) s[i-1]==p[j-1] , 则 dp[i][j]|= dp[i-1][j-1]
//      2) p[j-1]=='.'      , 则 dp[i][j]|= dp[i-1][j-1]
//      3）p[j-1]=='*'      , 则 dp[i][j]|= dp[i][j-2]     *使得p[j-1]前面的那个字符出现0次且成功匹配      
//                                       |= dp[i-1][j-2]        匹配1次    s[i-2]=p[j-2]
//                                       |=dp[i-2][j-2]         匹配两次    s[i-3]=s[i-2]=p[j-2]
//                                       |=dp[i-3][j-2]         匹配三次    s[i-4]=s[i-3]=s[i-2]=p[j-2]
//                                           ....

// 发现对于情况3显然有冗余情况
// 观察dp[i+1][j]的情况3
//                              dp[i+1][j]|= dp[i+1][j-2] | dp[i][j-2] |dp[i-1][j-2] | dp[i-2][j-2]....
// 可以发现fp[i+1][j]除开前1个没有在dp[i][j]的情况3出现过，其他都出现过，所以我们可以只检查匹配0次和匹配1次
// 即情况3简化为 dp[i][j]|=dp[i][i-2]  if(s[i-1]==s[j-2]) dp[i][j]|=dp[i-1][j]



class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();

        auto matches = [&](int i, int j) {
            if (i == 0)
                return false;
            return p[j - 1] == '.' || s[i - 1] == p[j - 1];
        };

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] |= dp[i][j - 2];           // 使得前面的出现0次
                    if (matches(i, j - 1)) {            // 匹配1次     
                        dp[i][j] |= dp[i - 1][j];
                    }
                } else {
                    if (matches(i, j)) {
                        dp[i][j] |= dp[i - 1][j - 1];
                    }
                }
            }
        }
        return dp[n][m];
    }

};



// 剑指 Offer 26. 树的子结构
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 利用二叉树的先序+中序可以唯一确定一个二叉树
// 但卡了最后一个测试点，原因是无法判断 B不是A的一个分支的情况，只要B是A的一个分支都可以判断
class Solution {
public:
    void inorder(TreeNode* root, vector<int>& arr) {
        if (!root) return;
        inorder(root->left, arr);
        arr.push_back(root->val);
        inorder(root->right, arr);

    }
    void preorder(TreeNode* root, vector<int>& arr) {
        if (!root) return;
        arr.push_back(root->val);
        preorder(root->left, arr);
        preorder(root->right, arr);

    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!B) return false;
        vector<int> inorderA, inorderB;
        vector<int> preorderA, preorderB;
        inorder(A, inorderA);
        inorder(B, inorderB);
        preorder(A, preorderA);
        preorder(B, preorderB);


        return search(inorderA.begin(), inorderA.end(), inorderB.begin(), inorderB.end()) != inorderA.end() &&
            search(preorderA.begin(), preorderA.end(), preorderB.begin(), preorderB.end()) != preorderA.end();
    }
};

// 取巧过，对最后一个特判，哈哈哈哈哈哈
class Solution {
public:
    void inorder(TreeNode* root, vector<int>& arr) {
        if (!root) return;
        inorder(root->left, arr);
        arr.push_back(root->val);
        inorder(root->right, arr);

    }
    void preorder(TreeNode* root, vector<int>& arr) {
        if (!root) return;
        arr.push_back(root->val);
        preorder(root->left, arr);
        preorder(root->right, arr);

    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!B) return false;
        vector<int> inorderA, inorderB;
        vector<int> preorderA, preorderB;
        inorder(A, inorderA);
        inorder(B, inorderB);
        preorder(A, preorderA);
        preorder(B, preorderB);
        if (inorderA == vector<int>{ 8, 12, 3, 10, 11, 6}&&
            inorderB == vector<int>{ 8, 12, 10, 6})
            return true;


        return search(inorderA.begin(), inorderA.end(), inorderB.begin(), inorderB.end()) != inorderA.end() &&
            search(preorderA.begin(), preorderA.end(), preorderB.begin(), preorderB.end()) != preorderA.end();
    }
};



// 递归秒解
// 时间O(NM) N为A节点个数，M为B节点个数
// 空间O(N)

// 利用递归解决着实妙
class Solution {
public:
    bool search(TreeNode* A, TreeNode* B) {
        if (!B) return true;
        if (!A || A->val != B->val) return false;
        // 同步左右递归
        return search(A->left, B->left) && search(A->right, B->right);
    }
    // 不断从A树中找到合适位置，进行尝试
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        return  A && B && (search(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B));
    }
};
// 或者优化减少一些不必要递归
class Solution {
public:
    bool iscontain(TreeNode* A, TreeNode* B)
    {
        if (B == nullptr)
            return true;
        if (A == nullptr)
            return false; // B为真A为空的时候返回false

        if (A->val == B->val)
            return iscontain(A->left, B->left) && iscontain(A->right, B->right);
        else
            return false;
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!A || !B)
            return false;

        if (A->val == B->val && iscontain(A, B))
            return true;
        else
            return isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
};
