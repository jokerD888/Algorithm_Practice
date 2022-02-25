
//34. �����������в���Ԫ�صĵ�һ�������һ��λ��
//��һ:���α������ֱ�����ҿ�ʼ��Զ˱�����target
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

//������һ�α���
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


//��������������������ʹ�ö��ֲ���
class Solution {
public:
	int binarySearch(vector<int>& nums, int target, bool lower) {
		int left = 0, right = (int)nums.size() - 1;

		while (left <= right) {
			int mid = (right - left) / 2 + left;
			//��Ϊ�������жϵĴ��ڣ���lowerΪfalse,right�����ܻ��ܵ����һ������target��λ��
			//						��lowerΪtrue��right�����ܻ��ܵ���һ������target��λ�õ�ǰһλ
			//���ԣ�falseʱ,����right+1�����ص�һ������target��λ�ã�
			//		trueʱ������right+1���������һ������target�ĺ�һ��λ��
			if (nums[mid] > target || (lower && nums[mid] >= target)) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}		
		return right+1;
	}

	vector<int> searchRange(vector<int>& nums, int target) {
		//�ҳ���һ�����ڵ���target��λ��
		int leftIdx = binarySearch(nums, target, true);
		//�ҳ����һ������target��λ��
		int rightIdx = binarySearch(nums, target, false)-1;
		if (leftIdx <= rightIdx && rightIdx < nums.size() && nums[leftIdx] == target && nums[rightIdx] == target) {
			return vector<int>{leftIdx, rightIdx};
		}
		return vector<int>{-1, -1};
	}
};




//33. ������ת��������
//���ֲ���
//������һ��Ϊ��������һ����һ��������ģ���һ������������Ҳ���ǲ�������
//��ʱ���򲿷��ö��ַ����ҡ����򲿷���һ��Ϊ��������һ��һ��������һ���������򣬿������򡣾�����ѭ��.
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
			//target����ߵ�����������
			if (nums[0] <= nums[mid]) {
				//target����[left,mid-1]
				if (nums[0] <= target && target < nums[mid]) {
					right = mid - 1;
				} else {
					//target����[mid+1,right]
					left = mid + 1;
				}
			} else {	//target���ұߵ�����������
				//target����[mid+1��right]
				if (nums[mid] < target && target <= nums[n - 1]) {
					left = mid + 1;
				} else {
					//target����[left,mid-1]
					right = mid - 1;
				}
			}
		}
		return -1;
	}
};




//74. ������ά����
//��һ����������+���б���
//���α�����һ�У�ֱ���ҵ�һ������Ԫ�ش���target����ʱ��targetҪô���ڴ��е�ǰһ���У����ڵ�һ�к����һ�зֱ����⿼��
class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int row = matrix.size(), col = matrix[0].size();
		for (int i = 0; i < row; ++i) {
			if (matrix[i][0] < target) {
				continue;
			}
			//i>0 ����target�ڵ�һ�е����
			for (int j = 0; j < col && i>0; ++j) {
				if (matrix[i - 1][j] == target) {
					return true;
				}
			}
		}
		//����target�����һ�е����
		for (int j = 0; j < col; ++j) {
			if (matrix[row-1][j] == target) {
				return true;
			}
		}
		return false;
	}
};


//�����������ζ��ֲ��ң�������һ�еĲ��һ�Ϊ���ֲ���
class Solution {
public:
	bool searchMatrix(vector<vector<int>> matrix, int target) {
		//upper_bound���ص�������ָ�����Ԫ���������е���ȷ����λ��
		auto row = upper_bound(matrix.begin(), matrix.end(), target, [](const int b, const vector<int>& a) {
			return b < a[0];
			});
		//����λ����begin˵��target����С�Ļ�С������matrix�У�����false
		if (row == matrix.begin()) {
			return false;
		}
		//�ڲ���λ�õ�ǰһ��
		--row;
		//���ֲ��ң�����boolֵ
		return binary_search(row->begin(), row->end(), target);
	}
};
//ʱ��O��logM+logN=logMN) M��N��

//��������һ�ζ��ֲ���
//��������ÿһ��ƴ������һ�е�ĩβ�����õ�һ���������飬���ǿ����ڸ������϶����ҵ�Ŀ��Ԫ�ء�
//����ʵ��ʱ�����Զ�������������±꣬����ӳ�䵽ԭ������к����ϡ�
class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int m = matrix.size(), n = matrix[0].size();
		int low = 0, high = m * n - 1;
		while (low <= high) {
			int mid = (high - low) / 2 + low;
			//����Ϊ�ڶ�ά�����ӳ��
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
//ʱ��O��logMN) M��N��

