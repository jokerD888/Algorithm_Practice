// 1237. 找出给定方程的正整数解

// 题意难懂，总之就是给你一个类customfunction，调用其f（x,y)函数，找出所有的x和y使得f=z

// 枚举
// O（N*N)
class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        vector<vector<int>> res;
        for (int x = 1; x <= 1000; ++x)
            for (int y = 1; y <= 1000; ++y)
                if (customfunction.f(x, y) == z)
                    res.push_back({ x,y });
        return res;
    }
};

// 进一步，利用函数单调递增的特性，使用二分
// O（N*logN)
class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        vector<vector<int>> res;
        for (int x = 1; x <= 1000; ++x) {
            int l = 1,r=1001;
            while (l<r) {
                int mid = l + r >> 1;
                if (customfunction.f(x, mid) < z)
                    l = mid + 1;
                else
                    r = mid;
            }
            if (customfunction.f(x, l) == z)
                res.push_back({ x, l});
        }
        return res;
    }
};

//双指针，上面的二分中我们只利用了y的单调性，x同时也具有单调性，所有可以使用双指针
// O(N)
// 左右指针，
class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        vector<vector<int>> res;
        for (int x = 1, y = 1000; x <= 1000 && y > 0; ++x) {
            while (y > 0 && customfunction.f(x, y) > z) --y;
            if (y >= 1 && customfunction.f(x, y) == z) res.push_back({ x,y });
        }
        return res;
    }
};



// 1797. 设计一个验证系统

// 哈希表直接搞
class AuthenticationManager {
private:
    int timeToLive;
    unordered_map<string, int> mp;
public:
    AuthenticationManager(int timeToLive) {
        this->timeToLive = timeToLive;
    }

    void generate(string tokenId, int currentTime) {
        mp[tokenId] = currentTime + timeToLive;
    }

    void renew(string tokenId, int currentTime) {
        if (mp.count(tokenId) && mp[tokenId] > currentTime) {
            mp[tokenId] = currentTime + timeToLive;
        }
    }

    int countUnexpiredTokens(int currentTime) {
        int res = 0;
        for (auto& [_, time] : mp) {
            if (time > currentTime) {
                res++;
            }
        }
        return res;
    }
};


//哈希表+双向链表 
// 用一个双向链表保存验证码和过期时间的顺序。
// 链表的节点保存验证码和过期时间信息，并且在一条链表上，节点保存的过期时间是递增的。
// 额外用一个哈希表 map 来保存验证码 - 节点对，提供根据验证码来快速访问节点的方法。
// generate 时，新建节点，将节点插入链表末尾，并插入 map。
// renew 时，如果验证码存在并且未过期，根据 map 访问到节点，更新过期时间，并将节点从原来位置移动到链表末尾。
// 调用 countUnexpiredTokens 时，从链表头部开始，删除过期的节点，并从 map 删除。
// 最后 map 的长度就是未过期的验证码的数量。
struct Node {
public:
    int expire;
    string key;
    Node* prev;
    Node* next;

    Node(int expire_) : expire(expire_), prev(nullptr), next(nullptr) {}
    Node(int expire_, string key_) : expire(expire_), key(key_), prev(nullptr), next(nullptr) {}
    Node(int expire_, string key_, Node* prev_, Node* next_) : expire(expire_), key(key_), prev(prev_), next(next_) {}
};

class AuthenticationManager {
private:
    int timeToLive;
    Node* head;
    Node* tail;
    unordered_map<string, Node*> mp;
public:
    AuthenticationManager(int timeToLive) {
        this->timeToLive = timeToLive;
        this->head = new Node(-1);
        this->tail = new Node(-1);
        this->head->next = this->tail;
        this->tail->prev = this->head;
    }

    void generate(string tokenId, int currentTime) {
        Node* node = new Node(currentTime + timeToLive, tokenId);
        mp[tokenId] = node;
        Node* last = tail->prev;
        last->next = node;
        node->prev = last;
        tail->prev = node;
        node->next = tail;
    }

    void renew(string tokenId, int currentTime) {
        if (mp.count(tokenId) && mp[tokenId]->expire > currentTime) {
            Node* node = mp[tokenId];
            Node* prev = node->prev;
            Node* next = node->next;
            prev->next = next;
            next->prev = prev;
            node->expire = currentTime + timeToLive;
            Node* last = tail->prev;
            last->next = node;
            node->prev = last;
            tail->prev = node;
            node->next = tail;
        }
    }

    int countUnexpiredTokens(int currentTime) {
        while (head->next->expire > 0 && head->next->expire <= currentTime) {
            Node* node = head->next;
            mp.erase(node->key);
            head->next = node->next;
            node->next->prev = head;
            delete node;
        }
        return mp.size();
    }
};
