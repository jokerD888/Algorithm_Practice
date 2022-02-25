
//34. 在排序数组中查找元素的第一个和最后一个位置
//法一:两次遍历，分别从左，右开始向对端遍历找target
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		if (nums.size() < 1) {
			return { -1,-1 };
		}
		int begin = 0, end = nums.size() - 1;
		while (begin < nums.size() && nums[begin++] != target) {}
		while (end >= 0 && nums[end--] != target) {}
		if (nums[begin-1]==target)
			return { begin - 1,end + 1 };
		else
			return { -1,-1 };

	}
};

//法二：一次遍历
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int begin = 0, end = nums.size() - 1,cur=0;
		while (begin <= end) {
			if (nums[begin] != target || nums[end] != target) {
				if (nums[begin] != target) {
					++begin;
				}
				if (nums[end] != target) {
					--end;
				}
			} else {
				break;
			}
			
		}
		if (begin > end) {
			return { -1,-1 }; 
		} else {
			return { begin, end };
		}
	}
};


//法三：利用数组已排序，使用二分查找
class Solution {
public:
	int binarySearch(vector<int>& nums, int target, bool lower) {
		int left = 0, right = (int)nums.size() - 1;

		while (left <= right) {
			int mid = (right - left) / 2 + left;
			//因为这里先判断的大于，若lower为false,right最终总会跑到最后一个等于target的位置
			//						若lower为true，right最终总会跑到第一个等于target的位置的前一位
			//所以，false时,返回right+1代表返回第一个等于target的位置，
			//		true时，返回right+1代表返回最后一个等于target的后一个位置
			if (nums[mid] > target || (lower && nums[mid] >= target)) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}		
		return right+1;
	}

	vector<int> searchRange(vector<int>& nums, int target) {
		//找出第一个大于等于target的位置
		int leftIdx = binarySearch(nums, target, true);
		//找出最后一个大于target的位置
		int rightIdx = binarySearch(nums, target, false)-1;
		if (leftIdx <= rightIdx && rightIdx < nums.size() && nums[leftIdx] == target && nums[rightIdx] == target) {
			return vector<int>{leftIdx, rightIdx};
		}
		return vector<int>{-1, -1};
	}
};




//33. 搜索旋转排序数组
//二分查找
//将数组一分为二，其中一定有一个是有序的，另一个可能是有序，也能是部分有序。
//此时有序部分用二分法查找。无序部分再一分为二，其中一个一定有序，另一个可能有序，可能无序。就这样循环.
class Solution {
public:
	int search(vector<int>& nums, int target) {
		int n = (int)nums.size();
		if (!n) {
			return -1;
		}
		if (n == 1) {
			return nums[0] == target ? 0 : -1;
		}
		int left = 0, right = n - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (nums[mid] == target) return mid;
			//target在左边的有序数组中
			if (nums[0] <= nums[mid]) {
				//target处于[left,mid-1]
				if (nums[0] <= target && target < nums[mid]) {
					right = mid - 1;
				} else {
					//target处于[mid+1,right]
					left = mid + 1;
				}
			} else {	//target在右边的有序数组中
				//target处于[mid+1，right]
				if (nums[mid] < target && target <= nums[n - 1]) {
					left = mid + 1;
				} else {
					//target处于[left,mid-1]
					right = mid - 1;
				}
			}
		}
		return -1;
	}
};




//74. 搜索二维矩阵
//法一：遍历首列+按行遍历
//依次遍历第一列，直到找到一个首行元素大于target，此时的target要么就在此行的前一行中，对于第一行和最后一行分别特殊考虑
class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int row = matrix.size(), col = matrix[0].size();
		for (int i = 0; i < row; ++i) {
			if (matrix[i][0] < target) {
				continue;
			}
			//i>0 考虑target在第一行的情况
			for (int j = 0; j < col && i>0; ++j) {
				if (matrix[i - 1][j] == target) {
					return true;
				}
			}
		}
		//考虑target在最后一行的情况
		for (int j = 0; j < col; ++j) {
			if (matrix[row-1][j] == target) {
				return true;
			}
		}
		return false;
	}
};


//方法二：两次二分查找，将方法一中的查找换为二分查找
class Solution {
public:
	bool searchMatrix(vector<vector<int>> matrix, int target) {
		//upper_bound返回迭代器，指向给定元素在序列中的正确插入位置
		auto row = upper_bound(matrix.begin(), matrix.end(), target, [](const int b, const vector<int>& a) {
			return b < a[0];
			});
		//插入位置在begin说明target比最小的还小，不在matrix中，返回false
		if (row == matrix.begin()) {
			return false;
		}
		//在插入位置的前一行
		--row;
		//二分查找，返回bool值
		return binary_search(row->begin(), row->end(), target);
	}
};
//时间O（logM+logN=logMN) M行N列

//方法三：一次二分查找
//若将矩阵每一行拼接在上一行的末尾，则会得到一个升序数组，我们可以在该数组上二分找到目标元素。
//代码实现时，可以二分升序数组的下标，将其映射到原矩阵的行和列上。
class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int m = matrix.size(), n = matrix[0].size();
		int low = 0, high = m * n - 1;
		while (low <= high) {
			int mid = (high - low) / 2 + low;
			//处理为在二维数组的映射
			int x = matrix[mid / n][mid % n];
			if (x < target) {
				low = mid + 1;
			} else if (x > target) {
				high = mid - 1;
			} else {
				return true;
			}
		}
		return false;
	}
};
//时间O（logMN) M行N列

