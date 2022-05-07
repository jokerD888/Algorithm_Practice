#include <iostream>
using namespace std;
#include <vector>
#include <queue>
//IndexTree(树状数组）--------------------------------------------------------------------------------
class IndexTree {
private:
	vector<int> tree;
	int N;
public:
	// 0位置弃而不用
	IndexTree(int size) :N(size) {
		tree.resize(N + 1);
	}

	// 1~index累加和多少
	int sum(int index) {
		int ret = 0;
		while (index > 0) {
			ret += tree[index];
			index -= index & -index;
		}
		return ret;
	}

	void add(int index, int d) {
		while (index <= N) {
			tree[index] += d;
			index += index & -index;
		}
	}
};
// 对数器
class Right {
private:
	vector<int> nums;
	int N;
public:
	Right(int size) :N(size) {
		nums.resize(N + 1);
	}
	int sum(int index) {
		int ret = 0;
		for (int i = 1; i <= index; ++i) {
			ret += nums[i];
		}
		return ret;
	}
	void add(int index, int d) {
		nums[index] += d;
	}
};

void TestIndexTree() {
	srand(time(NULL));
	int N = 100;
	int V = 100;
	int testTime = 2000000;
	IndexTree tree(N);
	Right test(N);
	cout << "test begin" << endl;
	for (int i = 0; i < testTime; i++) {
		int index = (int)(rand() % N) + 1;
		if (rand() % 2 < 1) {
			int add = (int)(rand() * V);
			tree.add(index, add);
			test.add(index, add);
		} else {
			if (tree.sum(index) != test.sum(index)) {
				cout << "Oops!" << endl;;
			}
		}
	}
	cout << "test finish" << endl;
}


//IndexTree2D(树状数组二维）--------------------------------------------------------------------------------
class IndexTree2D {
private:
	vector<vector<int>> tree;
	vector<vector<int>> nums;
	int N;
	int M;

public:

	IndexTree2D(vector<vector<int>>& matrix) {
		if (matrix.size() == 0 || matrix[0].size() == 0)
			return;
		N = matrix.size();
		M = matrix[0].size();
		tree.resize(N + 1, vector<int>(N + 1));
		nums.resize(N + 1, vector<int>(N + 1));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				update(i, j, matrix[i][j]);
			}
		}
	}
	//从左上角[1,1]到[row,col]右下角矩阵的和
	int sum(int row, int col) {
		int sum = 0;
		for (int i = row + 1; i > 0; i -= i & (-i)) {
			for (int j = col + 1; j > 0; j -= j & (-j)) {
				sum += tree[i][j];
			}
		}
		return sum;
	}
	void update(int row, int col, int val) {
		if (N == 0 || M == 0) {
			return;
		}
		int add = val - nums[row][col];
		nums[row][col] = val;
		for (int i = row + 1; i <= N; i += i & (-i)) {
			for (int j = col + 1; j <= M; j += j & (-j)) {
				tree[i][j] += add;
			}
		}
	}
	int sumRegion(int row1, int col1, int row2, int col2) {
		if (N == 0 || M == 0) {
			return 0;
		}
		return sum(row2, col2) + sum(row1 - 1, col1 - 1) - sum(row1 - 1, col2) - sum(row2, col1 - 1);
	}
};



//AC自动机--------------------------------------------------------------------------------------
class Node {
public:
	// 如果一个node，end为空，不是结尾
	// 如果end不为空，表示这个点是某个字符串的结尾，end的值就是这个字符串
	string end;
	bool endUse;
	Node* fail;
	vector<Node*> nexts;

	Node() :endUse(false), fail(nullptr)
	{
		nexts.resize(26);
	}
};
class ACAutomation {
private:
	Node* root;
public:
	ACAutomation() :root(new Node()) {}

	//建前缀树，有多少个敏感词就调用多少次。
	void insert(const string& s) {
		Node* cur = root;
		int index = 0;
		for (int i = 0; i < s.size(); ++i) {
			index = s[i] - 'a';
			if (!cur->nexts[index]) {
				cur->nexts[index] = new Node();
			}
			cur = cur->nexts[index];
		}
		cur->end = s;
	}
	//前缀数建立好后，调用build建立fail指针的指向
	//bfs一层一层建立，特别的root指向nullptr，根下的第一层都指向root,其他的节点，判断其父节点的fail是为空，
	// 不为空的话，判断其下是否有相同的路（i)存在，若存在，建立指向，否则，cfail=cfail->fail
	void build() {
		queue<Node*> qu;
		qu.push(root);
		Node* cur = nullptr;
		Node* cfail = nullptr;
		while (!qu.empty()) {
			//某个父亲
			cur = qu.front();
			qu.pop();
			for (int i = 0; i < 26; ++i) {	//查看所有路
				// cur为父亲， i为儿子，接下来必须把i号儿子的fail指针设置好
				if (cur->nexts[i]) {	//如果有i号儿子的话
					cur->nexts[i]->fail = root;	//先设为空，不行的话后续再改过来
					cfail = cur->fail;
					while (cfail) {
						if (cfail->nexts[i]) {
							cur->nexts[i]->fail = cfail->nexts[i];
							break;
						}
						cfail = cfail->fail;
					}
					qu.push(cur->nexts[i]);
				}
			}

		}
	}
	//对str查找有那些敏感词出现
	//每次来到一个cur节点，如果当前字符在这条路上没配出来，就随着fail方向走向下条路径，
	//若现在来到的路径是可以匹配的，就不断cfail往上转，若stirng不为空，存入答案数组
	vector<string> containWords(string str) {
		Node* cur = root;
		Node* follow = nullptr;
		int index = 0;
		vector<string> ans;
		for (int i = 0; i < str.size(); i++) {
			index = str[i] - 'a'; // 路
			// 如果当前字符在这条路上没配出来，就随着fail方向走向下条路径
			while (!cur->nexts[index] && cur != root) {
				cur = cur->fail;
			}
			// 1) 现在来到的路径，是可以继续匹配的
			// 2) 现在来到的节点，就是前缀树的根节点
			cur = cur->nexts[index]  ? cur->nexts[index] : root;
			follow = cur;
			while (follow != root) {
				if (follow->endUse) {
					break;
				}
				// 不同的需求，在这一段之间修改
				if (!follow->end.empty()) {
					ans.push_back(follow->end);
					follow->endUse = true;
				}
				// 不同的需求，在这一段之间修改
				follow = follow->fail;
			}
		}
		return ans;
	}
	
};

void testAC() {
	ACAutomation ac;
	ac.insert("dhe");
	ac.insert("he");
	ac.insert("abcdzheks");
	// 设置fail指针
	ac.build();

	auto contains = ac.containWords("abcdhekskdjfafhasldkflskdjhwqaeruv");
	for (string word : contains) {
		cout << word << endl;
	}
}


int main() {
	TestIndexTree();
	testAC();

	return 0;
}