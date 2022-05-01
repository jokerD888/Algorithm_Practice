//121. 买卖股票的最佳时机---------------------------------------------------
//法一：枚举，枚举每个买入的时间点，后遍历其后的所有元素，找出最适合的卖出点
// 超时
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int ans = 0;
		for (int i = 0; i < prices.size(); ++i) {
			int index = i;
			for (int j = i + 1; j < prices.size(); ++j) {
				if (prices[j] > prices[i] && prices[j] > prices[index])
					index = j;
			}
			ans = max(ans, prices[index] - prices[i]);
		}
		return ans;
	}
};
// 法二：一遍遍历，依次记录历史最低点，依次更新最大收益
// 当来到prices[i]时prices[0...i-1]中的最小值即为当前历史最低点，假设历史最低点买入，当前卖出是否能更新最大收益
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int minprice = INT_MAX, maxprofit = 0;
		for (int price : prices) {
			maxprofit = max(maxprofit, price - minprice);
			minprice = min(price, minprice);
		}
		return maxprofit;
	}
};

//128. 最长连续序列------------------------------------------------------

// 利用unordered_set去重且具有O（1)时间的查找
class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_set<int> num_set;

		for (const int& num : nums) {
			num_set.insert(num);
		}

		int longestStreak = 0;

		for (const int& num : num_set) {
			// 如果nun前有连续的num-1，那么以num开始的连续字串就不必再算
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


//139. 单词拆分-----------------------------------------------------
//法一：利用unordered_set实现快速字符串查找，但无法通过有重复单词组成的多个不同字符串如"aaaa","aaa"
// 部分无法通过
class Solution {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> word_set(wordDict.begin(), wordDict.end());

		int len = s.size();
		int last = 0;
		for (int i = 0; i < len; ++i) {
			if (word_set.find(s.substr(last, i - last + 1)) == word_set.end()) {
				continue;
			} else {
				last = i + 1;
			}
		}
		if (last == len)
			return true;
		else
			return false;
	}
};

//法二：dp

class Solution {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> wordDictSet(wordDict.begin(), wordDict.end());
		//dp[i] 表示字符串s前i个字符组成的字符串s[0..i−1] 是否能被空格拆分成若干个字典中出现的单词

		vector<bool> dp(s.size() + 1);
		dp[0] = true;
		for (int i = 1; i <= s.size(); ++i) {
			// 以j为分割点，将s[0..i]分割为s[0...j-1]和s[j...i]若两个字符串都可被字典中的word组成，那么这个整体就可以被组成
			for (int j = 0; j < i; ++j) {
				if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()) {
					dp[i] = true;
					break;
				}
			}
		}

		return dp[s.size()];
	}
};
// dp+剪枝
class Solution {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> wordDictSet(wordDict.begin(), wordDict.end());
		//dp[i] 表示字符串s前i个字符组成的字符串s[0..i−1] 是否能被空格拆分成若干个字典中出现的单词
		int max_len = 0;
		for (auto& word : wordDict) {
			max_len = max(max_len, (int)word.size());
		}

		vector<bool> dp(s.size() + 1);
		dp[0] = true;
		for (int i = 1; i <= s.size(); ++i) {
			// 以j为分割点，将s[0..i]分割为s[0...j-1]和s[j...i]若两个字符串都可被字典中的word组成，那么这个整体就可以被组成
			// 逆序枚举+剪枝
			for (int j = i - 1; j >= 0; --j) {
				// 如果j到i的距离已超过最大单词的长度，break
				if (i - j > max_len) {
					break;
				}
				if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()) {
					dp[i] = true;
					break;
				}
			}
		}

		return dp[s.size()];
	}
};
