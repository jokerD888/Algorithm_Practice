//  399. 除法求值

// 并查集
class Solution {
public:

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int N = equations.size();
        UnionFind uf(2 * N);
        // 预处理，将变量的值与id进行映射，使得并查集的底层使用数组实现，便于编码
        unordered_map<string, int> hashMap(2 * N);
        int id = 0;
        for (int i = 0; i < N; ++i) {
            string var2 = equations[i][1];
            string var1 = equations[i][0];

            if (!hashMap.count(var1)) {
                hashMap[var1] = ++id;
            }
            if (!hashMap.count(var2)) {
                hashMap[var2] = ++id;
            }

            uf.unionSet(hashMap[var1], hashMap[var2], values[i]);
        }

        // 做查询
        int M = queries.size();
        vector<double> res(M);
        for (int i = 0; i < M; ++i) {
            string var1 = queries[i][0];
            string var2 = queries[i][1];

            int id1 = hashMap[var1];
            int id2 = hashMap[var2];

            if (!id1 || !id2) {
                res[i] = -1.0;
            } else {
                res[i] = uf.isConnected(id1, id2);
            }
        }
        return res;
    }

    class UnionFind {
    public:
        UnionFind(int n) {
            ++n;
            fa.resize(n);
            for (int i = 0; i < n; ++i) fa[i] = i;
            w.resize(n, 1.0);
        }
        void unionSet(int x, int y, double val) {
            int rx = find(x), ry = find(y);
            if (rx == ry) return;

            fa[rx] = fa[ry];    // y做x的父
            w[rx] = w[y] * val / w[x];  // 更新权值
        }
        int find(int x) {       //  查找的同时做路径压缩
            if (x != fa[x]) {
                int origin = fa[x]; // 原来的父
                fa[x] = find(fa[x]);    // 路径压缩
                w[x] *= w[origin];      // 更新权值
            }

            return fa[x];
        }
        double isConnected(int x, int y) {
            int rx = find(x);
            int ry = find(y);
            if (rx == ry) {
                return w[x] / w[y];
            } else {
                return -1.0;
            }
        }
    private:
        vector<int> fa;
        vector<double> w;
    };
};



// bfs，构图，对于任意一个查询，可以从起点出发，通过bfs的方法，不断更新起点与当前点之间的路径长度，直至搜随到中点为止
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int nvars = 0;
        unordered_map<string, int> variables;

        int n = equations.size();
        for (int i = 0; i < n; i++) {
            if (variables.find(equations[i][0]) == variables.end()) {
                variables[equations[i][0]] = nvars++;
            }
            if (variables.find(equations[i][1]) == variables.end()) {
                variables[equations[i][1]] = nvars++;
            }
        }

        // 对于每个点，存储其直接连接到的所有点及对应的权值
        vector<vector<pair<int, double>>> edges(nvars);
        for (int i = 0; i < n; i++) {
            int va = variables[equations[i][0]], vb = variables[equations[i][1]];
            edges[va].push_back(make_pair(vb, values[i]));
            edges[vb].push_back(make_pair(va, 1.0 / values[i]));
        }

        vector<double> ret;
        for (const auto& q : queries) {
            double result = -1.0;
            if (variables.find(q[0]) != variables.end() && variables.find(q[1]) != variables.end()) {
                int ia = variables[q[0]], ib = variables[q[1]];
                if (ia == ib) {
                    result = 1.0;
                } else {
                    queue<int> points;
                    points.push(ia);
                    vector<double> ratios(nvars, -1.0);
                    ratios[ia] = 1.0;

                    while (!points.empty() && ratios[ib] < 0) {
                        int x = points.front();
                        points.pop();

                        for (const auto [y, val] : edges[x]) {
                            if (ratios[y] < 0) {
                                ratios[y] = ratios[x] * val;
                                points.push(y);
                            }
                        }
                    }
                    result = ratios[ib];
                }
            }
            ret.push_back(result);
        }
        return ret;
    }
};




// Floyd 算法

// 预先使用Floyd算法，先计算出任意两个点之间的距离
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int id = 0;
        unordered_map<string, int> variables;

        int N = equations.size();
        for (int i = 0; i < N; i++) {
            if (!variables.count(equations[i][0])) {
                variables[equations[i][0]] = id++;
            }
            if (!variables.count(equations[i][1])) {
                variables[equations[i][1]] = id++;
            }
        }
        vector<vector<double>> graph(id, vector<double>(id, -1.0));
        for (int i = 0; i < N; i++) {
            int va = variables[equations[i][0]], vb = variables[equations[i][1]];
            graph[va][vb] = values[i];
            graph[vb][va] = 1.0 / values[i];
        }

        for (int k = 0; k < id; k++) {
            for (int i = 0; i < id; i++) {
                for (int j = 0; j < id; j++) {
                    if (graph[i][k] > 0 && graph[k][j] > 0) {
                        graph[i][j] = graph[i][k] * graph[k][j];
                    }
                }
            }
        }

        vector<double> ret;
        for (const auto& q : queries) {
            double result = -1.0;
            if (variables.count(q[0]) && variables.count(q[1])) {
                int ia = variables[q[0]], ib = variables[q[1]];
                if (graph[ia][ib] > 0) {
                    result = graph[ia][ib];
                }
            }
            ret.push_back(result);
        }
        return ret;
    }
};




// 406. 根据身高重建队列

// 按照身高从小到大排，需求从大到小排
// 从前往后遍历，根据需求i，找到第i个空位放入
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[0] < v[0] || (u[0] == v[0] && u[1] > v[1]);
            });
        int n = people.size();
        vector<vector<int>> ans(n);
        for (const vector<int>& person : people) {
            int spaces = person[1] + 1;
            for (int i = 0; i < n; ++i) {
                if (ans[i].empty()) {
                    --spaces;
                    if (!spaces) {
                        ans[i] = person;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};


// 对数组进行排序，从身高从大到小排，需求从小到大排
// 按照这个规则进行排序后，依次从前往后遍历，根据需求i插入i位置
// 这样处理后，插入位置之后不受影响，保持原有规则
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[0] > v[0] || (u[0] == v[0] && u[1] < v[1]);
            });
        vector<vector<int>> ans;
        for (const vector<int>& person : people) {
            ans.insert(ans.begin() + person[1], person);
        }
        return ans;
    }
};

// 以上两种做法的时间瓶颈主要在插入上，可以自定义有序表，实现O(logN)插入
// 以上两法是O(N^2),此法做到O(NlogN)
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int N = people.size();
        vector<Unit> units(N);
        for (int i = 0; i < N; ++i) {
            units[i] = { people[i][0],people[i][1] };
        }

        sort(units.begin(), units.end(), [](const Unit& a, const Unit& b) {
            return a.h == b.h ? a.k<b.k : a.h>b.h;
            });
        SBTree tree;
        for (int i = 0; i < N; ++i) {
            tree.insert(units[i].k, i);
        }

        vector<int> allIndexes = tree.allIndexes();
        vector<vector<int>> ans(N);
        int index = 0;
        for (int i : allIndexes) {
            ans[index++] = { units[i].h,units[i].k };
        }

        return ans;
    }
    class Unit {
    public:
        int h, k;
        Unit(int h_, int k_) :h(h_), k(k_) {}
        Unit(){}
    };
    class SBTNode {
    public:
        int val;
        SBTNode* left, * right;
        int size;
        SBTNode(int arrIndex):left(nullptr),right(nullptr) {
            val = arrIndex;
            size = 1;
        }
    };
    class SBTree {
    public:
        SBTNode* root;
        SBTree() :root(nullptr) {}
        SBTNode* RightRotate(SBTNode* cur) {
            // 右旋
            SBTNode* leftNode = cur->left;
            cur->left = leftNode->right;
            leftNode->right = cur;
            // 节点数量调整,cur 和 leftNode 的结构发生了变化，进行调整
            leftNode->size = cur->size;		// leftNode作为新头，节点数量直接为原头的节点数量
            // cur节点数=左数节点数+右树节点数 + 1
            cur->size = (cur->left ? cur->left->size : 0) + (cur->right ? cur->right->size : 0) + 1;
            return leftNode;
        }
        SBTNode* LeftRotate(SBTNode* cur) {
            // 处理类似上述右旋
            SBTNode* rightNode = cur->right;
            cur->right = rightNode->left;
            rightNode->left = cur;
            rightNode->size = cur->size;
            cur->size = (cur->left ? cur->left->size : 0) + (cur->right ? cur->right->size : 0) + 1;
            return rightNode;
        }
        SBTNode* Maintain(SBTNode* cur) {
            if (!cur)
                return nullptr;
            int LSize = cur->left ? cur->left->size : 0;
            int LLSize = cur->left && cur->left->left ? cur->left->left->size : 0;
            int LRSize = cur->left && cur->left->right ? cur->left->right->size : 0;
            int RSize = cur->right ? cur->right->size : 0;
            int RRSize = cur->right && cur->right->right ? cur->right->right->size : 0;
            int RLSize = cur->right && cur->right->left ? cur->right->left->size : 0;
            if (LLSize > RSize) {	// LL型违规，左左侄的节点数大于右叔
                cur = RightRotate(cur);	// 右旋
                cur->right = Maintain(cur->right);	// 右旋完后，新树cur的右孩子结构发生了改变，调整
                cur = Maintain(cur);	// cur本身是新根，结构也发生了改变，调整
            } else if (LRSize > RSize) {
                // LR型违规，左右侄的节点数大于右叔，若LL和LR同时出现，LL以先判断，走到这里就不会出现这种情况了
                cur->left = LeftRotate(cur->left);
                cur = RightRotate(cur);
                // 三个节点结构均发生改变，调整
                cur->left = Maintain(cur->left);
                cur->right = Maintain(cur->right);
                cur = Maintain(cur);
            } else if (RRSize > LSize) {	// RR型
                cur = LeftRotate(cur);
                cur->left = Maintain(cur->left);
                cur = Maintain(cur);
            } else if (RLSize > LSize) {		// RL型
                cur->right = RightRotate(cur->right);
                cur = LeftRotate(cur);
                cur->left = Maintain(cur->left);
                cur->right = Maintain(cur->right);
                cur = Maintain(cur);
            }
            return cur;
        }
        SBTNode* insert(SBTNode* root, int index, SBTNode* cur) {
            if (!root) return cur;
            ++root->size;
            int leftAndHeadSize = (root->left ? root->left->size : 0) + 1;
            if (index < leftAndHeadSize) {
                root->left = insert(root->left, index, cur);
            } else {
                root->right = insert(root->right, index - leftAndHeadSize, cur);
            }
            root = Maintain(root);
            return root;
        }
        SBTNode* get(SBTNode* root, int index) {
            int leftSize = root->left ? root->left->size : 0;
            if (index < leftSize) {
                return get(root->left, index);
            } else if (index == leftSize) {
                return root;
            } else {
                return get(root->right, index - leftSize - 1);
            }
        }
        void process(SBTNode* head, vector<int>& indexes) {
            if (!head) {
                return;
            }
            process(head->left, indexes);
            indexes.push_back(head->val);
            process(head->right, indexes);
        }
        void insert(int index, int value) {
            SBTNode* cur = new SBTNode(value);
            if (!root) {
                root = cur;
            } else {
                if (index <= root->size) {
                    root = insert(root, index, cur);
                }
            }
        }
        int get(int index) {
            SBTNode* ans = get(root, index);
            return ans->val;
        }
        vector<int> allIndexes() {
            vector<int> indexes;
            process(root, indexes);
            return indexes;
        }

    };

};
