//208. 实现 Trie (前缀树)--------------------------------------------------------
class Trie {
public:
	class Node {
	public:
		bool endUse;
		vector<Node*> nexts;
		Node() :endUse(false), nexts(26) {}
	};
	Node* root;

	Trie() :root(new Node) {}

	void insert(string word) {
		Node* cur = root;
		int index = 0;
		for (int i = 0; i < word.size(); ++i) {
			index = word[i] - 'a';
			if (!cur->nexts[index]) {
				cur->nexts[index] = new Node();
			}
			cur = cur->nexts[index];
		}
		cur->endUse = true;
	}

	bool search(string word) {
		Node* cur = root;
		int index = 0;
		for (int i = 0; i < word.size(); ++i) {
			index = word[i] - 'a';
			if (!cur->nexts[index])
				return false;
			else
				cur = cur->nexts[index];
		}
		return cur->endUse == true;
	}

	bool startsWith(string prefix) {
		Node* cur = root;
		int index = 0;
		for (int i = 0; i < prefix.size(); ++i) {
			index = prefix[i] - 'a';
			if (!cur->nexts[index])
				return false;
			else
				cur = cur->nexts[index];
		}
		return true;
	}
};

// 或
class Trie {
private:
	vector<Trie*> children;
	bool isEnd;

	Trie* searchPrefix(string prefix) {
		Trie* node = this;
		for (char ch : prefix) {
			ch -= 'a';
			if (node->children[ch] == nullptr) {
				return nullptr;
			}
			node = node->children[ch];
		}
		return node;
	}

public:
	Trie() : children(26), isEnd(false) {}

	void insert(string word) {
		Trie* node = this;
		for (char ch : word) {
			ch -= 'a';
			if (node->children[ch] == nullptr) {
				node->children[ch] = new Trie();
			}
			node = node->children[ch];
		}
		node->isEnd = true;
	}

	bool search(string word) {
		Trie* node = this->searchPrefix(word);
		return node != nullptr && node->isEnd;
	}

	bool startsWith(string prefix) {
		return this->searchPrefix(prefix) != nullptr;
	}
};

//221. 最大正方形----------------------------------------------------------------
//法一：暴力===================================================
// 枚举左上角


class Solution {
public:
	int check(vector<vector<char>>& matrix, int x, int y) {
		int maxLen = min(matrix.size() - x, matrix[0].size() - y);
		for (int k = maxLen; k >= 1; --k) {
			bool vaild = true;
			for (int i = x; i < x + k; ++i) {
				for (int j = y; j < y + k; ++j) {
					if (matrix[i][j] == '0') {
						vaild = false;
						break;
					}
				}
				if (!vaild) break;
			}
			if (vaild)
				return k;
		}
		return 1;

	}
	int maximalSquare(vector<vector<char>>& matrix) {
		int n = matrix.size(), m = matrix[0].size();
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (matrix[i][j] == '1') {
					ans = max(check(matrix, i, j),ans);
				}
			}
		}
		return ans * ans;

	}
};
//或
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int n = matrix.size(), m = matrix[0].size();
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (matrix[i][j] == '1') {
					int min_len = min(n - i, m - j);
					for (int k = min_len; k >= 1; --k) {
						bool vaild = true;
						for (int x = i; x < i + k; ++x) {
							for (int y = j; y < j + k; ++y) {
								if (matrix[x][y] == '0') {
									vaild = false;
									break;
								}
							}
							if(!vaild)break;
						}
						if (vaild)
							ans = max(ans, k);
					}
				}
			}
		}
		return ans * ans;

	}
};

//法二:dp
class Solution {
public:
	vector<int> dp;
	//dp的下标index为二维数组的一维形式，dp的含义，dp[i]表示以(i/m,i%m)为右下角的最大正方形边长
	int check(vector<vector<char>>& matrix, int r, int c,int len) {
		//检查位于（r，c）点向上和向左的方向是不是都全是1
		for (int i = 1; i <=len; ++i) {
			if (matrix[r-i][c] == '0' || matrix[r][c-i] == '0')
				return i-1;
		}

		return len;
	}
	int maximalSquare(vector<vector<char>>& matrix) {
		int n = matrix.size(), m = matrix[0].size();
		dp.resize(n * m,0);
		int ans = 0;

		//初始化dp数组第一行第一列
		for (int i = 0; i < n; ++i) {
			if (matrix[i][0] == '1') {
				dp[i * m] = 1;
				ans = 1;
			}
		}
		for (int i = 0; i < m; ++i) {
			if (matrix[0][i] == '1') {
				dp[i] = 1;
				ans = 1;
			}
		}
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < m; ++j) {
				if (matrix[i][j] == '1') {
					int max_vaild_len = check(matrix, i, j, dp[(i - 1) * m + j - 1]);
					dp[i * m + j] = max_vaild_len + 1;
					ans = max(ans, dp[i * m + j]);
				}
			}
		}
		return ans * ans;

	}
};
//最优解法的dp
//上法的运行时间主要浪费在对（x,y)的上方和左方一定长度上是否为全一的判断
//没有合理利用（x-1,y)和（x,y-1)的dp信息，根据这两个位置的dp信息，就可以替代上述的操作
//因为此法中dp的含义还和上面的相同，dp[i][j]代表以（i，j)作为右下角的正方形的最大边长
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		if (matrix.size() == 0 || matrix[0].size() == 0) {
			return 0;
		}
		int maxSide = 0;
		int rows = matrix.size(), columns = matrix[0].size();
		vector<vector<int>> dp(rows, vector<int>(columns));
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (matrix[i][j] == '1') {
					if (i == 0 || j == 0) {		//对第一行或第一列的特判
						dp[i][j] = 1;
					} else {
						dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
					}
					maxSide = max(maxSide, dp[i][j]);
				}
			}
		}
		int maxSquare = maxSide * maxSide;
		return maxSquare;
	}
};


int main()
{
	Trie t;
	t.insert("apple");
	cout << t.search("apple") << endl;
	cout << t.search("app") << endl;
	t.startsWith("app");
	return 0;
}