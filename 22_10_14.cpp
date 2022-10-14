//  218. 天际线问题


// 优先队列
// 可以发现，关键点的坐标都是建筑的左右边界，对于每个边界点，天际线的高度即为所有落在该点的建筑的最高值
// 所以暴力的，我们可以枚举建筑的每一个边缘作为关键点的横坐标，过程中，我们O(N)检查每个建筑是否包含该横坐标，找到最大高度
//      对于O(N)的查找最大高度的过程，可以用优先队列来优化，优化为O(logN)，因为buildings是按左边缘非递减排序的，所以我们将所有左边缘小于等于当前坐标的入堆
// 若答案数组为空 或 将要加入答案的坐标不等于数组尾的坐标 ，则将当前坐标以及高度加入答案数组
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {

        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) -> bool { return a.second < b.second; };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> que(cmp);

        vector<int> boundaries;
        for (auto& building : buildings) {
            boundaries.emplace_back(building[0]);       // 找出每个边界点
            boundaries.emplace_back(building[1]);
        }
        sort(boundaries.begin(), boundaries.end());     // 对所有边界点排序

        vector<vector<int>> ret;
        int n = buildings.size(), idx = 0;
        for (auto& boundary : boundaries) {
            // 因为buildings是按左边缘非递减排序的，所以我们将所有左边缘小于等于当前坐标的入堆
            while (idx < n && buildings[idx][0] <= boundary) {
                que.emplace(buildings[idx][1], buildings[idx][2]);  // 将右边界和高度入堆
                idx++;
            }
            // 剔除无效的，即右边界小于等于当前坐标的，等于不能漏，因为有边界对之后的高度没有贡献
            while (!que.empty() && que.top().first <= boundary) {
                que.pop();
            }

            int maxn = que.empty() ? 0 : que.top().second;
            if (ret.size() == 0 || maxn != ret.back()[1]) { // 注意高度相同的合并
                ret.push_back({ boundary, maxn });
            }
        }
        return ret;
    }
};



// 或

// 有序表
// 同样的，我们把左右端点分开看作一个点，按坐标进行排序，我们用高度的正负来标记是左边缘还是右边缘
// 我们用一个有序表来记录每个高度出现的个数，从左往右遍历，遇到高度为正的，将该该高度次数++，否则--，若减到0，则从有序表剔除
class Solution {
public:
    typedef pair<int, int> PII;
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int N = buildings.size();
        vector<PII> nodes(N * 2);
        for (int i = 0; i < N; ++i) {
            nodes[i * 2] = make_pair(buildings[i][0], buildings[i][2]);         // 将左边缘的高度标记为正
            nodes[i * 2 + 1] = make_pair(buildings[i][1], -buildings[i][2]);    // 将右边缘的高度标记为负
        }
        sort(nodes.begin(), nodes.end());
        map<int, int> height_times, X_height;   // height_times 描述高度出现的次数

        N = 2 * N;
        for (int i = 0; i < N; ++i) {
            int x = nodes[i].first, h = nodes[i].second;
            if (h >= 0) {      // 左边缘
                ++height_times[h];
            } else {                // 右边缘,记得对哈希表操作时取负数
                if (height_times[-h] == 1)   // 只要左边缘和右边缘不是同一个坐标，那么对右边缘的高度进行查询的时候一定存在
                    height_times.erase(-h);
                else
                    --height_times[-h];
            }
            if (height_times.empty())
                X_height[x] = 0;
            else
                X_height[x] = height_times.rbegin()->first;
        }
        vector<vector<int>> res;
        for (auto p : X_height) {
            int x = p.first;
            int h = p.second;
            if (res.empty() || res.back()[1] != h) {  //  注意高度相同的合并
                res.push_back({ x,h });
            }
        }
        return res;
    }
};
// 优化
// 上面之所以用有序表记录各位置的高度，是因为排序规则所限制
// 默认的pair<int,int> 排序是，按第一关键字小的排，若相等，按第二关键字按小排
// 这就导致，若有一个建筑右边缘和另一个建筑的左边缘相同，则左边缘的排在后面，若直接在循环内结算比较麻烦或者说无法结算
// 我们自定义排序，第一个关键字相同时，按第二关键字大的排，这样即可在循环内结算
class Solution {
public:
    typedef pair<int, int> PII;
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int N = buildings.size();
        vector<PII> nodes(N * 2);
        for (int i = 0; i < N; ++i) {
            nodes[i * 2] = make_pair(buildings[i][0], buildings[i][2]);         // 将左边缘的高度标记为正
            nodes[i * 2 + 1] = make_pair(buildings[i][1], -buildings[i][2]);    // 将右边缘的高度标记为负
        }
        sort(nodes.begin(), nodes.end(), [](const PII& a, const PII& b) {return a.first != b.first ? a.first<b.first : a.second>b.second; });
        map<int, int> height_times, X_height;   // height_times 描述高度出现的次数

        vector<vector<int>> res;
        N = 2 * N;
        for (int i = 0; i < N; ++i) {
            int x = nodes[i].first, h = nodes[i].second;
            if (h>=0) {      // 左边缘
                ++height_times[h];
            } else {                // 右边缘,记得对哈希表操作时取负数
                if (height_times[-h] == 1)   // 只要左边缘和右边缘不是同一个坐标，那么对右边缘的高度进行查询的时候一定存在
                    height_times.erase(-h);
                else
                    --height_times[-h];
            }
            h = height_times.empty() ? 0 : height_times.rbegin()->first;
            if (res.empty() || res.back()[1] != h)      // 注意高度相同的合并
                res.push_back({ x,h });
        }
        return res;
    }
};

