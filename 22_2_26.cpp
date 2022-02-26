//153. 寻找旋转排序数组中的最小值
//二分
class Solution {
public:
	int findMin(vector<int>& nums) {
		int low = 0;
		int high = nums.size() - 1;
		while (low < high) {
			int pivot = low + (high - low) / 2;
			if (nums[pivot] < nums[high]) {
				//最小的在左半边
				//pivot可能是最小的
				high = pivot;
			} else {
				//最小的在右半边
				low = pivot + 1;
			}
		}
		return nums[low];
	}
};


//162. 寻找峰值
//法一:寻找最大值
//最大值一定是峰值
class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		return max_element(nums.begin(), nums.end()) - nums.begin();
	}
};


//法二：爬坡迭代
//如果我们从一个位置开始，不断地向高处走，那么最终一定可以到达一个峰值位置。
class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		int n = nums.size();
		int idx = rand() % n;

		// 辅助函数，输入下标 i，返回一个二元组 (0/1, nums[i])
		// 方便处理 nums[-1] 以及 nums[n] 的边界情况
		auto get = [&](int i) -> pair<int, int> {
			if (i == -1 || i == n) {
				//用first为0来表示两边负无穷的情况
				return { 0, 0 };
			}
			return { 1, nums[i] };
		};
		// nums[idx-1]<nums[idx]<nums[idx+1]不成立的话
		while (!(get(idx - 1) < get(idx) && get(idx) > get(idx + 1))) {
			if (get(idx) < get(idx + 1)) {
				//上升，往右走
				++idx;
			} else {
				//下降，往左走
				--idx;
			}
		}

		return idx;
	}
};

//方法三：二分
//改进自法二，每次向一个方向走后，反方向的都可以忽略
class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		int n = nums.size();

		// 辅助函数，输入下标 i，返回一个二元组 (0/1, nums[i])
		// 方便处理 nums[-1] 以及 nums[n] 的边界情况
		auto get = [&](int i) -> pair<int, int> {
			if (i == -1 || i == n) {
				return { 0, 0 };
			}
			return { 1, nums[i] };
		};

		int left = 0, right = n - 1, ans = -1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (get(mid - 1) < get(mid) && get(mid) > get(mid + 1)) {
				ans = mid;
				break;
			}
			if (get(mid) < get(mid + 1)) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		return ans;
	}
};

//法四： 二分
//若上升右侧必有峰值
class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		int left = 0;
		int right = nums.size() - 1;
		while (left < right) {
			int mid = (right - left) / 2 + left;
			if (nums[mid] < nums[mid + 1]) {
				left = mid + 1;
			} else {
				right = mid;
			}
		}
		return right;
	}
};


