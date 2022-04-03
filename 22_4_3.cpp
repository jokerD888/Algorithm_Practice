//17. 电话号码的字母组合
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

//31. 下一个排列

//法一：调用API
class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		next_permutation(nums.begin(), nums.end());
	}
};

// 法二：两边扫描
//1.我们需要将一个左边的「较小数」与一个右边的「较大数」交换，以能够让当前排列变大，从而得到下一个排列。
//2.同时我们要让这个「较小数」尽量靠右，而「较大数」尽可能小。当交换完成后，
//「较大数」右边的数需要按照升序重新排列。这样可以在保证新排列大于原来排列的情况下，使变大的幅度尽可能小。

// 先从后往前寻找第一个非降序（从左往右的顺序）的数字，记为较小值i，再从后往前找第一个大于较小值的数组，即为较大值j
// 在寻找较大值的过程中，较大值的范围一定再[i+1,n]上，且因此部分为降序，遇到的第一个大于i的数字即为较大值
class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int i = nums.size() - 2;
		// 较小数
		while (i >= 0 && nums[i] >= nums[i + 1]) {
			i--;
		}
		// i<0的话，说明一整个数组都是降序,即当前数组已经是最大的排序了,随后直接逆序即可
		if (i >= 0) {
			int j = nums.size() - 1;
			//较大数
			while (j >= 0 && nums[i] >= nums[j]) {
				j--;
			}
			swap(nums[i], nums[j]);
		}
		reverse(nums.begin() + i + 1, nums.end());
	}
};

