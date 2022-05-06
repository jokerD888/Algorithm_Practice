#include <iostream>
using namespace std;
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>
//992. K 个不同整数的子数组-----------------------------------------------------------------------------
class Solution {
public:
	int subarraysWithKDistinct(vector<int>& nums, int k) {
		int n = nums.size();
		vector<int> num1(n + 1), num2(n + 1);	//数字范围在长度范围内，可用数字替代哈希表
		int tot1 = 0, tot2 = 0;
		int left1 = 0, left2 = 0, right = 0;
		int ret = 0;
		while (right < n) {
			if (!num1[nums[right]]) {	//新数字
				tot1++;
			}
			num1[nums[right]]++;		//出现新数+1
			if (!num2[nums[right]]) {	//新数字
				tot2++;
			}
			num2[nums[right]]++;		//出现次数+1
			while (tot1 > k) {			//tot1>k，需要左缩
				num1[nums[left1]]--;	//出现次数-1
				if (!num1[nums[left1]]) {	//只出现一次，tot--
					tot1--;
				}
				left1++;		//left1左缩
			}
			//num2与上同理
			while (tot2 > k - 1) {
				num2[nums[left2]]--;
				if (!num2[nums[left2]]) {
					tot2--;
				}
				left2++;
			}
			ret += left2 - left1;
			right++;
		}
		return ret;
	}
};


//207. 课程表---------------------------------------------------------

// 法一（bfs)：利用拓扑排序，利用hash_map记录每个节点的入度，先找出入度为0的那一批节点，随后遍历此点指向的终点，将终点入度--
//--后，若是入度为0后也加入queue中，其中可能有无任何关联的课程，利用hash_set检查有关联的课程数目，即可得出无关联的课程数。
class Solution {
public:
	bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
		if (prerequisites.size() == 0)
			return true;
		unordered_map<int, int> node_map;	//记录节点入度
		unordered_map<int, vector<int>> nexts;	//记录以key为起点的终点集
		unordered_set<int> diff;	
		for (auto nums : prerequisites) {
			node_map[nums[0]]++;
			node_map[nums[1]];
			nexts[nums[1]].push_back(nums[0]);
			diff.insert(nums[0]);
			diff.insert(nums[1]);
		}
		queue<int> zero_queue;
		for (auto kv : node_map) {	//入队入度为0节点
			if (kv.second == 0) {
				zero_queue.push(kv.first);
			}
		}
		int cnt = numCourses-diff.size();	//以无关联的课程数为起点
		while (!zero_queue.empty()) {
			int cur = zero_queue.front();
			zero_queue.pop();
			++cnt;
			auto arr = nexts[cur];
			for (auto next : arr) {
				--node_map[next];	//消除节点cur带来的入度影响
				if (node_map[next] == 0) {	//新的入度为0的节点
					zero_queue.push(next);
				}
			}
		}
		return cnt == numCourses;	
	}
};
//或
class Solution {
private:
	vector<vector<int>> edges;	//数据范围不大，用以映射
	vector<int> indeg;	//indeg表i节点的入度

public:
	bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
		edges.resize(numCourses);
		indeg.resize(numCourses);
		for (const auto& info : prerequisites) {
			edges[info[1]].push_back(info[0]);
			++indeg[info[0]];
		}

		queue<int> q;
		for (int i = 0; i < numCourses; ++i) {
			if (indeg[i] == 0) {
				q.push(i);
			}
		}

		int visited = 0;
		while (!q.empty()) {
			++visited;
			int u = q.front();
			q.pop();
			for (int v : edges[u]) {
				--indeg[v];
				if (indeg[v] == 0) {
					q.push(v);
				}
			}
		}

		return visited == numCourses;
	}
};



//法二：dfs
class Solution {
private:
	vector<vector<int>> edges;
	vector<int> visited;
	bool valid = true;

public:
	void dfs(int u) {
		// vis[i]==1是i节点正在搜索
		visited[u] = 1;	
		for (int v : edges[u]) {
			if (visited[v] == 0) {
				dfs(v);
				if (!valid) {
					return;
				}
			} else if (visited[v] == 1) {	//有环
				valid = false;
				return;
			}
		}
		//vis[i] == 2是以搜索完
		visited[u] = 2;
	}

	bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
		edges.resize(numCourses);
		visited.resize(numCourses);
		for (const auto& info : prerequisites) {
			edges[info[1]].push_back(info[0]);
		}
		for (int i = 0; i < numCourses && valid; ++i) {
			if (!visited[i]) {
				dfs(i);
			}
		}
		return valid;
	}
};
