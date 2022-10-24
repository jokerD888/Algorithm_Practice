// 380. O(1) 时间插入、删除和获取随机元素

// 数组+哈希表
// 利用哈希表可以做到O(1)时间做到插入和删除，但无法根据下标定位到确定的元素，故无法在O(1）时间内随机等概率返回一个数
// 我们加入vector变长数组，利用哈希表映射每个元素对应的下标，可以实现O(1)的插入，对于删除的话
// 我们利用哈希表找到要删除的元素的下标，将该位置和最后一个数交换，即可O(1)时间删除数组中的元素

class RandomizedSet {
public:
    RandomizedSet() {
        srand((unsigned)time(NULL));
    }

    bool insert(int val) {
        if (indices.count(val)) {
            return false;
        }
        int index = nums.size();
        nums.emplace_back(val);
        indices[val] = index;
        return true;
    }

    bool remove(int val) {
        if (!indices.count(val)) {
            return false;
        }
        int index = indices[val];
        int last = nums.back();
        nums[index] = last;
        indices[last] = index;
        nums.pop_back();
        indices.erase(val);
        return true;
    }

    int getRandom() {
        int randomIndex = rand() % nums.size();
        return nums[randomIndex];
    }
private:
    vector<int> nums;
    unordered_map<int, int> indices;
};



// 384. 打乱数组

// random_shuffle库函数
class Solution {
public:
    vector<int> tmp, arr;
    Solution(vector<int>& nums) {
        srand(time(NULL));
        arr = tmp = nums;
    }

    vector<int> reset() {
        return arr;
    }

    vector<int> shuffle() {
        random_shuffle(tmp.begin(), tmp.end());
        return tmp;
    }
};


// Fisher-Yates 洗牌算法
// 我们可以在移除waiting的第k个元素时，将第k个元素与数组的最后1个元素交换，然后移除交换后数组的最后1个元素，
// 这样我们只需要O(1)的时间复杂度即可完成移除第k个元素的操作。此时，被移除的交换后数组的最后1个元素即为我们根据随机下标获取的元素。
// 在此基础上，我们也可以不移除最后1个元素，而直接将其作为乱序后的结果，
// 并更新待乱序数组的长度从而实现数组的原地乱序。因为我们不再需要从数组中移除元素，
// 所以也可以将第k个元素与第1个元素交换。

class Solution {
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
        this->original = nums;
    }

    vector<int> reset() {
        return original;
    }

    vector<int> shuffle() {
        for (int i = 0; i < nums.size(); ++i) {
            int j = i + rand() % (nums.size() - i);
            swap(nums[i], nums[j]);
        }
        return nums;
    }
private:
    vector<int> nums;
    vector<int> original;
};



