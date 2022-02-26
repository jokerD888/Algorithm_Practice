//153. Ѱ����ת���������е���Сֵ
//����
class Solution {
public:
	int findMin(vector<int>& nums) {
		int low = 0;
		int high = nums.size() - 1;
		while (low < high) {
			int pivot = low + (high - low) / 2;
			if (nums[pivot] < nums[high]) {
				//��С��������
				//pivot��������С��
				high = pivot;
			} else {
				//��С�����Ұ��
				low = pivot + 1;
			}
		}
		return nums[low];
	}
};


//162. Ѱ�ҷ�ֵ
//��һ:Ѱ�����ֵ
//���ֵһ���Ƿ�ֵ
class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		return max_element(nums.begin(), nums.end()) - nums.begin();
	}
};


//���������µ���
//������Ǵ�һ��λ�ÿ�ʼ�����ϵ���ߴ��ߣ���ô����һ�����Ե���һ����ֵλ�á�
class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		int n = nums.size();
		int idx = rand() % n;

		// ���������������±� i������һ����Ԫ�� (0/1, nums[i])
		// ���㴦�� nums[-1] �Լ� nums[n] �ı߽����
		auto get = [&](int i) -> pair<int, int> {
			if (i == -1 || i == n) {
				//��firstΪ0����ʾ���߸���������
				return { 0, 0 };
			}
			return { 1, nums[i] };
		};
		// nums[idx-1]<nums[idx]<nums[idx+1]�������Ļ�
		while (!(get(idx - 1) < get(idx) && get(idx) > get(idx + 1))) {
			if (get(idx) < get(idx + 1)) {
				//������������
				++idx;
			} else {
				//�½���������
				--idx;
			}
		}

		return idx;
	}
};

//������������
//�Ľ��Է�����ÿ����һ�������ߺ󣬷�����Ķ����Ժ���
class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		int n = nums.size();

		// ���������������±� i������һ����Ԫ�� (0/1, nums[i])
		// ���㴦�� nums[-1] �Լ� nums[n] �ı߽����
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

//���ģ� ����
//�������Ҳ���з�ֵ
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


