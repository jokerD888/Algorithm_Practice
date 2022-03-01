
////剑指 Offer II 077. 链表排序
//struct ListNode {
//	int val;
//	ListNode* next;
//	ListNode() : val(0), next(nullptr) {}
//	ListNode(int x) : val(x), next(nullptr) {}
//	ListNode(int x, ListNode* next) : val(x), next(next) {}
//
//};
//class Solution {
//public:
//	ListNode* sortList(ListNode* head) {
//		multimap<int, ListNode*> m;
//		ListNode* cur = head;
//		while (cur != nullptr) {
//			m.insert({ cur->val,cur });
//			cur = cur->next;
//		}
//		ListNode* ret = new ListNode(0);
//		cur = ret;
//		for (auto kv : m) {
//			cur->next = kv.second;
//			cur = cur->next;
//		}
//		cur->next = nullptr;
//		return ret->next;
//	}
//};

////713. 乘积小于K的子数组
////法一：依次枚举起点，扩大滑动窗口（超时）
//class Solution {
//public:
//
//	int numSubarrayProductLessThanK(vector<int>& nums, int k) {
//		int begin = 0, end = 0;
//		int ret = 0;
//		for (int i = 0; i < nums.size(); ++i) {
//			begin = i;
//			int cur = 1;
//			for (int end = begin; end < nums.size();++end) {
//				cur *= nums[end];
//				if (cur < k) {
//					++ret;
//				} else {
//					break;
//				}
//			}
//		}
//		return ret;
//	}
//};
//
//
////法二：二分查找
////要求连续的子数组，那么若起点固定，不断向右扩展，乘积越大，符合二分查找有序要求
////由于连续的乘积，极为容易溢出，进行log来避免，并利用前缀和来表示乘积
//class Solution {
//public:
//	int numSubarrayProductLessThanK(vector<int>& nums, int k) {
//		if (k == 0) {
//			return 0;
//		}
//		double logk = log(k);
//		vector<double> prefix(nums.size() + 1);
//		for (int i = 0; i < nums.size(); ++i) {
//			prefix[i + 1] = prefix[i] + log(nums[i]);
//		}
//
//		int ans = 0;
//		for (int i = 0; i < prefix.size(); ++i) {
//			//每次固定一个起点
//			int low = i + 1, high = prefix.size();
//			while (low < high) {
//				int mid = (high - low) / 2 + low;
//				if (prefix[mid] < prefix[i] + logk - 1e-9) {
//					low = mid + 1;
//				} else {
//					high = mid;
//				}
//			}
//			//low-1是最后一个小于k的
//			//此时end=low-1 begin=i+1, 之间共有end-begin+1个元素即low-i-1
//			//所以以begin为固定起点，到end共有low-i+1个字数组
//			ans += low - i - 1;
//		}
//		return ans;
//	}
//};


//法三：滑动窗口(双指针）
class Solution {
public:
	int numSubarrayProductLessThanK(vector<int>& nums, int k) {
		if (k < 1) {
			return 0;
		}
		int ans = 0, left = 0;
		int64_t prod = 1;
		for (int right = 0; right < nums.size(); ++right) {
			//累乘，固定right
			prod *= nums[right];
			//找出最小的left
			while (left<=right && prod >= k) {	//lefe<=right是为了防止nums中多1，且k也为1的情况，如{1，1，1} 1
				prod /= nums[left++];
			}
			ans += right - left + 1;
		}
		return ans;
	}
};
