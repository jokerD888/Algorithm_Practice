//451. �����ַ�����Ƶ������
//����һ����ϣ���¼���ִ���������vector�����ִ�������
class Solution {
public:
    string frequencySort(string s) {
        map<char, int> m;
        for (auto c : s) {
            ++m[c];
        }
        vector<pair<char, int>> ans;
        for (auto kv : m) {
            ans.emplace_back(kv);
        }
        sort(ans.begin(), ans.end(), [](const pair<char, int>& a, const pair<char, int>& b) {return a.second > b.second; });
        string ret;
        for (auto kv : ans) {
            ret.append(kv.second, kv.first);
        }
        return ret;
    }
};

//��������Ͱ����
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mp;
        int maxFreq = 0;
        int length = s.size();
        for (auto& ch : s) {
            maxFreq = max(maxFreq, ++mp[ch]);
        }
        vector<string> buckets(maxFreq + 1);
        for (auto& [ch, num] : mp) {
            buckets[num].push_back(ch);
        }
        string ret;
        for (int i = maxFreq; i > 0; i--) {
            string& bucket = buckets[i];
            for (auto& ch : bucket) {
                for (int k = 0; k < i; k++) {
                    ret.push_back(ch);
                }
            }
        }
        return ret;
    }
};


//���������ȶ���
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> m;
        for (char i : s)
        {
            m[i]++;
        }
        priority_queue<pair<int, char>, vector<pair<int, char>>, less<pair<int, char>>> pq;
        for (auto i : m)
        {
            pq.emplace(i.second, i.first);
        }
        string res;
        for (auto j : m)
        {
            res.append(pq.top().first, pq.top().second);
            pq.pop();
        }
        return res;
    }
};


//973. ��ӽ�ԭ��� K ����
//��һ���Զ����������ȡǰK����
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        sort(points.begin(), points.end(), [](const vector<int>& x, const vector<int>& y)
            {return x[0] * x[0] + x[1] * x[1] < y[0] * y[0] + y[1] * y[1]; });
        return { points.begin(),points.begin() + k };
    }
};


//��������
//���������ʵʱά��k����С�ľ���ƽ��
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        //key Ϊ����   valueΪ ��Ӧ����points�е��±�
        priority_queue<pair<int, int>> q;
        for (int i = 0; i < k; ++i) {
            q.emplace(points[i][0] * points[i][0] + points[i][1] * points[i][1], i);
        }
        int n = points.size();
        for (int i = k; i < n; ++i) {
            int dist = points[i][0] * points[i][0] + points[i][1] * points[i][1];
            if (dist < q.top().first) {
                q.pop();
                q.emplace(dist, i);
            }
        }
        vector<vector<int>> ans;
        while (!q.empty()) {
            ans.push_back(points[q.top().second]);
            q.pop();
        }
        return ans;
    }
};



//������������ѡ�񣨿��������˼�룩
class Solution {
private:
    mt19937 gen{ random_device{}() };

public:
    void random_select(vector<vector<int>>& points, int left, int right, int k) {
        int pivot_id = uniform_int_distribution<int>{ left, right }(gen);
        int pivot = points[pivot_id][0] * points[pivot_id][0] + points[pivot_id][1] * points[pivot_id][1];
        swap(points[right], points[pivot_id]);
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            int dist = points[j][0] * points[j][0] + points[j][1] * points[j][1];
            if (dist <= pivot) {
                ++i;
                swap(points[i], points[j]);
            }
        }
        ++i;
        swap(points[i], points[right]);
        // [left, i-1] ��С�ڵ��� pivot, [i+1, right] ������ pivot
        if (k < i - left + 1) {
            random_select(points, left, i - 1, k);
        }         else if (k > i - left + 1) {
            random_select(points, i + 1, right, k - (i - left + 1));
        }
    }

    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int n = points.size();
        random_select(points, 0, n - 1, k);
        return { points.begin(), points.begin() + k };
    }
};

//��ֱ�ӵ���C++ api
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        nth_element(points.begin(), points.begin() + k - 1, points.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[0] * u[0] + u[1] * u[1] < v[0] * v[0] + v[1] * v[1];
            });
        return { points.begin(), points.begin() + k };
    }
};

