//890. 查找和替换模式

// 双映射
class Solution {
public:
	bool match(string& word, string& pattern) {
		unordered_map<char, char> mp;
		for (int i = 0; i < word.size(); ++i) {
			char x = word[i], y = pattern[i];
			if (!mp.count(x))	
				mp[x] = y;
			else if (mp[x] != y)
				return false;
		}
		return true;
	}
	vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
		vector<string> res;
		for (auto& word : words) {
			if (match(word, pattern) && match(pattern, word))
				res.push_back(word);
		}
		return res;

	}
};
// 或
class Solution {
public:
	vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
		vector<string> ans;
		for (auto&& w : words) {
			// trs是映射关系，trs[i]使用低7位作为i的映射值，高1位作为i是否被映射
			char trs[128]{};
			bool flag = true;
			for (int i = 0, n = w.size(); i < n; ++i) {
				if (trs[w[i]] & 127) {		// 如果 w[i] 有映射了
					if ((trs[w[i]] & 127) != pattern[i]) {	// 映射的不是pattern[i],break;
						flag = false;
						break;
					}
				} else {		// w[i] 无映射
					if (trs[pattern[i]] & 128) {	// 但pattern[i] 有被映射，break;
						flag = false;
						break;
					}
					// pattern [i] 没过映射过
					trs[pattern[i]] |= 128;			// pattern 被映射了
					trs[w[i]] |= pattern[i];		// w[i] 映射为 pattern[i]
				}
			}
			if (flag) ans.emplace_back(move(w));
		}
		return ans;
	}
};
// 或
class Solution {
public:
	vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
		vector<string> res;
		bool flag = true;
		for (auto& word : words) {
			flag = true;
			for (int i = 0; i < word.size(); i++) {	
				// 对于i位置的字符进行检查，利用s.find判断word[i]和patten[i]在word和在patten中首次出现的位置是否相同，只要有一定不同就说明不匹配
				// 因为只要不匹配其首次出现的次数一定不相同，可以用反推法证明
				if (word.find(word[i]) != pattern.find(pattern[i])) {
					flag = false;
					break;
				}
			}
			if (flag) res.push_back(word);
		}
		return res;
	}
};