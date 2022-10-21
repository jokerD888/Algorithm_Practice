// 350. 两个数组的交集 II

// 数据范围为0到1000，可以计数统计,若数据范围较大，可以使用哈希表
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        int N = nums1.size(), M = nums2.size();
        int cnt1[1010]{ 0 }, cnt2[1010]{ 0 };
        for (int i = 0; i < N; ++i) ++cnt1[nums1[i]];
        for (int i = 0; i < M; ++i) ++cnt2[nums2[i]];
        vector<int> res;
        for (int i = 0; i < 1010; ++i)
            for (int j = 0; j < min(cnt1[i], cnt2[i]); ++j)
                res.push_back(i);
        return res;
    }
};
// 哈希表
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        //为了降低空间复杂度，首先遍历较短的数组并在哈希表中记录每个数字以及对应出现的次数，然后遍历较长的数组得到交集。
        if (nums1.size() > nums2.size()) {
            return intersect(nums2, nums1);
        }
        unordered_map <int, int> m;
        for (int num : nums1) {
            ++m[num];
        }
        vector<int> intersection;
        for (int num : nums2) {
            if (m.count(num)) {
                intersection.push_back(num);
                --m[num];
                if (m[num] == 0) {
                    m.erase(num);
                }
            }
        }
        return intersection;
    }
};

// 若给定的数组已排好序
// 双指针
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        int N = nums1.size(), M = nums2.size();
        int i = 0, j = 0;
        vector<int> res;
        while (i < N && j < M) {
            if (nums1[i] == nums2[j]) {
                res.push_back(nums1[i]);
                ++i, ++j;
            }else if (nums1[i] < nums2[j]) 
                ++i;
            else
                ++j;
        }
        return res;
    }
};

// 如果 nums2 的元素存储在磁盘上，内存是有限的，并且你不能一次加载所有的元素到内存中，
// 那么使用方法一，即哈希表的做法，因为这做法中关系到查询操作，每次读取一部分即可



// 328. 奇偶链表
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* evenhead = even;
        
        while (true)
        {
            if(!even->next) break;
            odd->next = even->next;
            odd = odd->next;

            if(!odd->next) break;
            even->next = odd->next;
            even = even->next;
        }
        even->next = nullptr;
        odd->next = evenhead;
        return head;
    }
};

// 或
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        ListNode* evenHead = head->next;
        ListNode* odd = head;
        ListNode* even = evenHead;
        while (even != nullptr && even->next != nullptr) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
        return head;
    }
};
