//17. �绰�������ĸ���
class Solution {
public:

	void DFS(map<char, string>& m, string& digits, int index, string& path, vector<string>& ans) {
		if (index == digits.size()) {
			ans.push_back(path);
			return;
		}
		string s = m[digits[index]];
		for (auto i : s) {
			path += i;
			DFS(m, digits, index + 1, path, ans);
			path.pop_back();
		}
	}
	vector<string> letterCombinations(string digits) {
		if (digits.empty()) {
			return {};
		}
		vector<string> ans;
		map<char, string> m{ {'2',"abc"},{'3',"def"},{'4',"ghi"},{'5',"jkl"},{'6',"mno"},{'7',"pqrs"},{'8',"tuv"},{'9',"wxyz"} };
		string s;
		DFS(m, digits, 0, s, ans);
		return ans;
	}
};

//31. ��һ������

//��һ������API
class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		next_permutation(nums.begin(), nums.end());
	}
};

// ����������ɨ��
//1.������Ҫ��һ����ߵġ���С������һ���ұߵġ��ϴ��������������ܹ��õ�ǰ���б�󣬴Ӷ��õ���һ�����С�
//2.ͬʱ����Ҫ���������С�����������ң������ϴ�����������С����������ɺ�
//���ϴ������ұߵ�����Ҫ���������������С����������ڱ�֤�����д���ԭ�����е�����£�ʹ���ķ��Ⱦ�����С��

// �ȴӺ���ǰѰ�ҵ�һ���ǽ��򣨴������ҵ�˳�򣩵����֣���Ϊ��Сֵi���ٴӺ���ǰ�ҵ�һ�����ڽ�Сֵ�����飬��Ϊ�ϴ�ֵj
// ��Ѱ�ҽϴ�ֵ�Ĺ����У��ϴ�ֵ�ķ�Χһ����[i+1,n]�ϣ�����˲���Ϊ���������ĵ�һ������i�����ּ�Ϊ�ϴ�ֵ
class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int i = nums.size() - 2;
		// ��С��
		while (i >= 0 && nums[i] >= nums[i + 1]) {
			i--;
		}
		// i<0�Ļ���˵��һ�������鶼�ǽ���,����ǰ�����Ѿ�������������,���ֱ�����򼴿�
		if (i >= 0) {
			int j = nums.size() - 1;
			//�ϴ���
			while (j >= 0 && nums[i] >= nums[j]) {
				j--;
			}
			swap(nums[i], nums[j]);
		}
		reverse(nums.begin() + i + 1, nums.end());
	}
};

