//934. 最短的桥-----------------------------------------------------
 //法一：先DFS找出两座岛，后从一座岛出发，BFS一旦遇到另一座岛，根据此时的BFS层数即可得出答案

class Solution {
public:
	int n, m;
	int shortestBridge(vector<vector<int>>& grid) {
		n = grid.size(), m = grid[0].size();
		auto colors = getComponents(grid);

		queue<int> qu;
		unordered_set<int> target;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (colors[i][j] == 1)
					qu.push(i * m + j);
				else if (colors[i][j] == 2)
					target.insert(i * m + j);
			}
		}

		//bfs
		int ans = 0;
		while (!qu.empty()) {
			int cnt = qu.size();
			++ans;
			while (cnt--) {
				auto node = qu.front();
				qu.pop();
				int x = node / m, y = node % m;
				for (int i = 0; i < 4; ++i) {
					int new_r = x + dire[i], new_c = y + dire[i + 1];
					if (!isVaild(new_r, new_c)) continue;
					if (colors[new_r][new_c] != 1) {
						if (target.find(new_r * m + new_c) != target.end())	//放在即将去队列时判断可比出对时判断少遍历一层
							return ans - 1;
						qu.push(new_r * m + new_c);
						colors[new_r][new_c] = 1;
					}
				}
			}
		}
		return -1;
	}

	int dire[5] = { -1,0,1,0,-1 };
	bool isVaild(int r, int c) {
		if (r < 0 || r == n || c < 0 || c == m)
			return false;
		return true;
	}
	vector<vector<int>> getComponents(vector<vector<int>>& grid) {
		vector<vector<int>> colors(n, vector<int>(m, 0));
		int t = 0;	//第几个岛

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (colors[i][j] == 0 && grid[i][j] == 1) {
					//dfs
					stack<int> st;
					st.push(i * m + j);//二维下标化为一维
					colors[i][j] = ++t;

					//下面的dfs就会把当前找到的岛跑完
					while (!st.empty()) {
						int node = st.top();
						st.pop();
						int x = node / m, y = node % m;
						for (int i = 0; i < 4; ++i) {
							int new_r = x + dire[i], new_c = y + dire[i + 1];
							if (!isVaild(new_r, new_c)) continue;	//如果下标不合法，continue
							if (grid[new_r][new_c] == 1 && colors[new_r][new_c] == 0) {
								colors[new_r][new_c] = t;	//记录当前块属于第几个岛的同时，也起到了标记，避免重复范围的作用
								st.push(new_r * m + new_c);
							}
						}
					}
				}
			}
		}
		return colors;
	}
};

//法二：dfs寻找第一个岛屿，并把此岛的1全部赋值为2，并获取岛外围"一圈"的海面 
//	   再从第一个岛外围的"海面”开始bfs寻找第二个岛屿，并把过程中经过的0赋值为2
// 法二除了使用queue和系统栈再无其他额外空间，且比法一少最开始的一大层BFS，时间也优于法一
class Solution {
private:
	vector<int> direction{ -1,0,1,0,-1 };

private:
	void dfs(vector<vector<int>>& grid, queue<pair<int, int>>& que, int row, int col) {
		int m = grid.size();
		int n = grid[0].size();

		if (row < 0 || row >= m || col < 0 || col >= n || grid[row][col] == 2) {
			return;
		}
		if (grid[row][col] == 0) {  // 岛外围"一圈"的海面
			que.push({ row,col });
			grid[row][col] = 2;	//最外层的海面置为2,防止首次BFS中重复入队最外层的海面
			return;
		}

		// 标记搜过
		grid[row][col] = 2;

		// 上下左右
		dfs(grid, que, row + 1, col);
		dfs(grid, que, row - 1, col);
		dfs(grid, que, row, col - 1);
		dfs(grid, que, row, col + 1);
	}
public:
	int shortestBridge(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();

		// dfs寻找第一个岛屿，并把1全部赋值为2，并获取 岛外围"一圈"的海面 
		queue<pair<int, int>> que;
		bool flag = false;
		for (int i = 0; i < m; ++i) {
			if (flag) break;
			for (int j = 0; j < n; ++j) {
				if (grid[i][j] == 1) {
					dfs(grid, que, i, j);
					flag = true;
					break;
				}
			}
		}

		// bfs寻找第二个岛屿，并把过程中经过的0赋值为2
		int level = 0;
		while (!que.empty()) {
			++level;                 // 第i圈 (第i层)
			int size = que.size();

			while (size--) {
				int row = que.front().first;
				int col = que.front().second;
				que.pop();
				// 下右上左
				for (int i = 0; i < 4; ++i) {
					int r = row + direction[i];
					int c = col + direction[i + 1];
					if (r >= 0 && r < m && c >= 0 && c < n) {
						if (grid[r][c] == 2) {	//走过，continue
							continue;
						}
						if (grid[r][c] == 1) {	//遇见另一个岛
							return level;
						}
						if (grid[r][c] == 0) {	
							que.push({ r,c });
							//此处应该在入队的时候标记走过，不该在出队的时候才标记，否则效率相差可能较大，因为可能会有同一块被反复入队
							grid[r][c] = 2;  
						}
					}
				}
			}
		}

		return 0;
	}
};



int main()
{
	Solution s;
	///vector<vector<int>> arr{ {0,1,0} ,{0,0,0}, {0, 0, 1} };
	vector<vector<int>> arr{ {1,1,1,1,1} ,{1,0,0,0,1} ,{1,0,0,0,1} ,{0,0,1,0,0} };
	//vector<vector<int>> arr{ {1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1 } };
	cout << s.shortestBridge(arr);
	return 0;
}