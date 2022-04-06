//55. ��Ծ��Ϸ
// ̰��
class Solution {
public:
	bool canJump(vector<int>& nums) {
		int n = nums.size();
		int pass = n - 1;
		for (int i = n - 2; i >= 0; --i) {

			if (nums[i] + i >= pass) {
				pass = i;
			}
		}
		if (nums[0] >= pass)
			return true;
		return false;
	}
};

// ��
class Solution {
public:
	bool canJump(vector<int>& nums) {
		int n = nums.size();
		int rightmost = 0;
		for (int i = 0; i < n; ++i) {
			if (i <= rightmost) {
				rightmost = max(rightmost, i + nums[i]);
				if (rightmost >= n - 1) {
					return true;
				}
			}
		}
		return false;
	}
};


// 23. �ϲ�K����������
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};
// ��һ����������ϲ�
class Solution {
public:
	ListNode* mergeLink(ListNode* a, ListNode* b) {
		if (!a || !b) return a ? a : b;
		ListNode head, * tail = &head, * aptr = a, * bptr = b;
		while (aptr && bptr) {
			if (aptr->val < bptr->val) {
				tail->next = aptr; aptr = aptr->next;
			} else {
				tail->next = bptr; bptr = bptr->next;
			}
			tail = tail->next;
		}
		tail->next = aptr ? aptr : bptr;
		return head.next;
	}
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		ListNode* ans = nullptr;
		for (size_t i = 0; i < lists.size(); ++i) {
			ans = mergeLink(ans, lists[i]);
		}
		return ans;
	}
};
// ʱ��O��k^2*n)


// ����:���κϲ�
class Solution {
public:

	ListNode* mergeLink(ListNode* a, ListNode* b) {
		if (!a || !b) return a ? a : b;
		ListNode head, * tail = &head, * aptr = a, * bptr = b;
		while (aptr && bptr) {
			if (aptr->val < bptr->val) {
				tail->next = aptr; aptr = aptr->next;
			} else {
				tail->next = bptr; bptr = bptr->next;
			}
			tail = tail->next;
		}
		tail->next = aptr ? aptr : bptr;
		return head.next;
	}
	ListNode* merge(vector<ListNode*>& lists, int L, int R) {
		if(L == R) return lists[L];
		//if (L > R) return nullptr;	// listsΪ�յ���������һ��ʼû���жϣ���������Ҫ�ж�
		int mid = (L + R) >> 1;
		return mergeLink(merge(lists, L, mid), merge(lists, mid + 1, R));
	}
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.size() == 0) return nullptr;
		return merge(lists, 0, lists.size() - 1);
	}
};
// ʱ�� O��kn*logk)
// �ռ� O(logK��ջ�ռ�

//  ���������ȶ���
class Solution {
public:
	struct Status {
		int val;
		ListNode* ptr;
		bool operator < (const Status& rhs) const {
			return val > rhs.val;
		}
	};

	priority_queue <Status> q;

	ListNode* mergeKLists(vector<ListNode*>& lists) {
		for (auto node : lists) {
			if (node) q.push({ node->val, node });
		}
		ListNode head, * tail = &head;
		while (!q.empty()) {
			auto f = q.top(); q.pop();
			tail->next = f.ptr;
			tail = tail->next;
			if (f.ptr->next) q.push({ f.ptr->next->val, f.ptr->next });
		}
		return head.next;
	}
};


//128. ���������
// ��ϣ��
class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_set<int> num_set;
		for (const int& num : nums) {
			num_set.insert(num);
		}

		int longestStreak = 0;

		for (const int& num : num_set) {
			if (!num_set.count(num - 1)) {
				int currentNum = num;
				int currentStreak = 1;

				while (num_set.count(currentNum + 1)) {
					currentNum += 1;
					currentStreak += 1;
				}

				longestStreak = max(longestStreak, currentStreak);
			}
		}

		return longestStreak;
	}
};

// ʱ��O��N)
// �ռ�O��N��
