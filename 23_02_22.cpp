
// 1140. 石子游戏 II

// 暴力，超时24/92
class Solution {
public:
    int M = 1;
    // dfs(pos,m)表示前pos堆已经拿完，目前M=m,返回{可以获得的最大收益，最大收益对应的堆数}
    pair<int, int> dfs(vector<int>& piles, int pos, int m) {
        if (pos >= piles.size()) return { 0,piles.size() };
        int max_value = 0, idx = 0;
        for (int i = 1; i <= 2 * m; ++i) {
            // t记录当前选择拿i堆，造成的最大收益
            int t = 0;
            for (int j = pos; j < piles.size() && j < pos + i; ++j) {
                t += piles[j];
            }
            // 轮到对手dfs了，对手必然会使得其自身收益最大，p为对手最大收益对应的堆数
            int p = dfs(piles, pos + i, max(m, i)).second;
            // 对手拿完了，自己再拿
            t += dfs(piles, pos + i + p, max(max(m, i), p)).first;
            if (t > max_value) {
                max_value = t;
                idx = i;
            }
        }
        return { max_value,idx };


    }

    int stoneGameII(vector<int> piles) {
        return dfs(piles, 0, 1).first;
    }
};

// 缓存

// 上法中，我们可以预处理出前缀和来加速，同时发现会有很多递归过程是重复的,可以使用缓存
// 时间O(N^3） 缓存规模为N*N，枚举选择最大为N
class Solution {
public:
    typedef pair<int, int> PII;
    // dfs(pos,m)表示前pos堆已经拿完，目前M=m,返回{可以获得的最大收益，最大收益对应的堆数}
    PII dfs(vector<int>& piles, int pos, int m, vector<int>& prefix, vector<vector<PII>>& cache) {
        int n = piles.size();

        if (pos >= n) return { 0,n };
        if (cache[pos][m].first != -1) return cache[pos][m];

        int max_value = 0, idx = 0;
        for (int i = 1; i <= 2 * m; ++i) {
            // t记录当前选择拿i堆，造成的最大收益
            int t = 0;
            t += prefix[min(pos + i, n)] - prefix[pos];

            // 轮到对手dfs了，对手必然会使得其自身收益最大，p为对手最大收益对应的堆数
            int p = dfs(piles, pos + i, max(m, i), prefix, cache).second;
            // 对手拿完了，自己再拿
            t += dfs(piles, pos + i + p, max(max(m, i), p), prefix, cache).first;
            if (t > max_value) {
                max_value = t;
                idx = i;
            }
        }
        cache[pos][m] = { max_value,idx };
        return { max_value,idx };


    }

    int stoneGameII(vector<int> piles) {
        int n = piles.size();
        vector<int> prefix(n + 1);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + piles[i];
        }
        vector<vector<PII>> cache(n + 1, vector<PII>(n + 1, { -1 ,0 }));
        return dfs(piles, 0, 1, prefix, cache).first;
    }
};

// 上法改dp,虽然结构简单了，但时间上比缓存要慢些，因为m每次都从1~n
class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MIN));
        // 按照回溯过程，自底向上
        for (int i = n; i >= 0; i--) {      // pos
            for (int m = 1; m <= n; m++) {      // M
                if (i == n) {
                    dp[i][m] = 0;
                } else {
                    int sum = 0;        // 累加和
                    for (int x = 1; x <= 2 * m; x++) {  // 选择
                        if (i + x > n) {
                            break;
                        }
                        sum += piles[i + x - 1];
                        dp[i][m] = max(dp[i][m], sum - dp[i + x][min(n, max(m, x))]);
                    }
                }
            }
        }
        return (dp[0][1] + accumulate(piles.begin(), piles.end(), 0)) / 2;
    }
};


// 148. 排序链表
// 有序表map,时间O(NlogN) 空间O(NlogN)
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
class Solution {
public:

    ListNode* sortList(ListNode* head) {
        
        multimap <int, ListNode*> mp;
        ListNode* cur = head;
        while (cur) {
            mp.insert({ cur->val,cur });
        }
        
    }
};

// 进阶：时间O(NlogN) 空间O(1)
// 归并排序,自底向上，即要避免递归的空间消耗
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr) return head;
        int length = 0;

        ListNode* node = head;
        while (node) {
            length++;
            node = node->next;
        }

        ListNode* dummy = new ListNode(0,head);
        for (int sub_length = 1; sub_length < length; sub_length<<=1) {
            ListNode* prev = dummy, * cur = dummy->next;
            while (cur) {
                // 分离两条长度为sub_length的链表
                ListNode* h1 = cur;
                for (int i = 1; i < sub_length && cur->next; ++i) { // 注意这里是<，即循环sub_length次
                    cur = cur->next;
                }
                    
                ListNode* h2 = cur->next;       // 第二条
                cur->next = nullptr;            // 第一条断尾
                cur = h2;               // 直到第二条头
                for (int i = 1; i < sub_length && cur && cur->next; ++i) {
                    cur = cur->next;
                }

                ListNode* next = nullptr;       // 下一对的头
                if (cur) {
                    next = cur->next;
                    cur->next = nullptr;
                }

                ListNode* merged = merge(h1, h2);
                prev->next = merged;
                // 找合并的尾
                while (prev->next) {
                    prev = prev->next;
                }
                cur = next;
            }
        }
        return dummy->next;
    }
    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy, * temp1 = head1, * temp2 = head2;
        while (temp1 && temp2) {
            if (temp1->val <= temp2->val) {
                cur->next = temp1;
                temp1 = temp1->next;
            } else {
                cur->next = temp2;
                temp2 = temp2->next;
            }
            cur = cur->next;
        }
        if (temp1) {
            cur->next = temp1;
        } else if(temp2) {
            cur->next = temp2;
        }
        return dummy->next;
    }
};