
////��ָ Offer II 077. ��������
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

////713. �˻�С��K��������
////��һ������ö����㣬���󻬶����ڣ���ʱ��
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
////���������ֲ���
////Ҫ�������������飬��ô�����̶�������������չ���˻�Խ�󣬷��϶��ֲ�������Ҫ��
////���������ĳ˻�����Ϊ�������������log�����⣬������ǰ׺������ʾ�˻�
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
//			//ÿ�ι̶�һ�����
//			int low = i + 1, high = prefix.size();
//			while (low < high) {
//				int mid = (high - low) / 2 + low;
//				if (prefix[mid] < prefix[i] + logk - 1e-9) {
//					low = mid + 1;
//				} else {
//					high = mid;
//				}
//			}
//			//low-1�����һ��С��k��
//			//��ʱend=low-1 begin=i+1, ֮�乲��end-begin+1��Ԫ�ؼ�low-i-1
//			//������beginΪ�̶���㣬��end����low-i+1��������
//			ans += low - i - 1;
//		}
//		return ans;
//	}
//};


//��������������(˫ָ�룩
class Solution {
public:
	int numSubarrayProductLessThanK(vector<int>& nums, int k) {
		if (k < 1) {
			return 0;
		}
		int ans = 0, left = 0;
		int64_t prod = 1;
		for (int right = 0; right < nums.size(); ++right) {
			//�۳ˣ��̶�right
			prod *= nums[right];
			//�ҳ���С��left
			while (left<=right && prod >= k) {	//lefe<=right��Ϊ�˷�ֹnums�ж�1����kҲΪ1���������{1��1��1} 1
				prod /= nums[left++];
			}
			ans += right - left + 1;
		}
		return ans;
	}
};
