// 完美洗牌
// 下标循环修改。
// 但实际有些并不能。
// 所有有以下结论：当长度为3^k-1,时，每个循环下标的开始下标为（1,3,3^2,3^3,3^(k-1)
// 当长度不为这些的时候，可以找到最接近N的数，对部分数字利用三次反转进行交换。
class Solution {
public:
    // 根据i位置得出下一个跑到的位置
    int modifyIndex(int i, int len) {
        return (2 * i) % (len + 1);
        // 或
        //return i <= len / 2 ? 2 * i : 2 * (i - len / 2) - 1;
    }
    // 三次反转
    void rotate(vector<int>& arr, int l, int m, int r) {
        // 注意 C++ reverse是对[l，r)上左开右闭进行反转的
        reverse(arr.begin() + l, arr.begin() + m + 1);
        reverse(arr.begin() + m + 1, arr.begin() + r + 1);
        reverse(arr.begin() + l, arr.begin() + r + 1);
    }
    void cycles(vector<int>& arr, int start, int len, int k) {
        // 找到每一个出发位置trigger，一共k个
        // 每一个trigger都进行下标连续推
        // 出发位置是从1开始算的，而数组下标是从0开始算的。
        for (int i = 0, trigger = 1; i < k; ++i, trigger *= 3) {
            int pre = arr[trigger + start - 1];
            int cur = modifyIndex(trigger, len);
            while (cur != trigger) {    // 只要不回到环的起点，就传
                int tmp = arr[cur + start - 1];
                arr[cur + start - 1] = pre;
                pre = tmp;
                cur = modifyIndex(cur, len);
            }
            arr[cur + start - 1] = pre;
        }
    }

    void shuffle(vector<int>& arr, int l, int r) {
        while (r - l + 1 > 0) {     // 一块一块切，每一块长度满足3^k-1
            int len = r - l + 1;
            int base = 3;   // 3^k
            int k = 1;      // 次方
            // 计算小于等于len并且是离len最近的，满足3^k-1的数
            // 即找到最大的k，满足3^k<=len+1
            while (base <= (len + 1) / 3) {
                base *= 3;
                ++k;
            }
            int halt = base - 1 >> 1;       // 左边一半，右边一半
            int mid = l + r >> 1;
            // 反转部分
            rotate(arr, l + halt, mid, mid + halt);
            // 循环下标怼
            cycles(arr, l, base - 1, k);
            l += base - 1;  // 下下块
        }
    }
    void shuffle(vector<int>& arr) {
        shuffle(arr, 0, arr.size() - 1);
    }
};





// 324. 摆动排序 II



// 排序
// 一种简单的想法就是排序，排序后分半，记左半边（即小的那边）为a,记右半边（即大的那边）为b，如果数组长度为奇数，则将中间的元素分到前面
// 明显当原数组中重复元素大于一半，那么一定无法完成摆动排序
// 我们可以a[i] b[j] a[i+1] b[j+1]...这样排列。但这样有一个问题，对于数组[1,2,2,3]，按照这种做法求得的结果仍为[1,2,2，3]。
// 原因分析：出现上述情况其实是因为数组A和数组B出现了相同元素，我们用r来表示这一元素。而且我们可以很容易发现，
// 如果A和B都存在r，那么r定是A的最大值，B的最小值，这意味着r一定出现在A的尾部，B的头部。其实，如果这一数字的个数较少，不会出现这一现象，
// 只有当这一数字个数达到原数组元素总数的一半，才会在穿插后出现在相邻位置
// 要解决这一问题，我们需要使A的r和B的r在穿插后尽可能分开。一种可行的办法是将A和B反序
// 例如，对于数组[1,1,2,2,2,3]，分割为[1,1,2]和[2,2,3]，分别反序后得到[2, 1, 1]和[3, 2, 2]，此时2在A头部，B尾部，穿插后就不会发生相邻了。
// 实际操作是从两数组的后面先前进行排列

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int N = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> tmp(N);
        int idx = -1;
        int halt = (N + 1) >> 1;
        for (int i = halt - 1, j = N - 1; i >= 0 && j >= halt; --i, --j) {
            tmp[++idx] = nums[i];
            tmp[++idx] = nums[j];
        }
        if (N & 1)
            tmp[++idx] = nums[0];
        for (int i = 0; i < N; ++i)
            nums[i] = tmp[i];
    }
};


// 快排思想，三向切分
// 上法之所以是O(NlogN)是因为我们使用了快排，但实际上我们并不关心a和b内部是否有序
// 只需要满足A和B长度相同（或相差1），且A中的元素小于等于B中的元素，且r出现在A的头部和B的尾部即可。
// 我们可以使用快排思想，类似荷兰国旗问题，将相同的放在中间，左边的都小于中间的，右边的都大于中间的
// 这样时间即可优化至O(N)
class Solution {
public:
    pair<int, int> partition(vector<int>& arr, int l, int r, int pivot) {
        int less = l - 1, more = r + 1;
        int cur = l;
        while (cur < more) {
            if (arr[cur] < pivot)
                swap(arr[++less], arr[cur++]);
            else if (arr[cur] > pivot)      // 大的换过来不一定小于pivot，所以cur不++，还需要下次判断
                swap(arr[cur], arr[--more]);
            else
                ++cur;
        }
        return { less + 1,more - 1 };
    }
    void adjust(vector<int>& arr, int l, int r, int index) {
        int pivot = 0;
        while (l < r) {
            pivot = arr[l + rand() % (r - l + 1)];  // 使用随机数随机选一个位置作为坑点，RAND_MAX的范围32,767与最大长度相近可以随机
            auto range = partition(arr, l, r, pivot);
            int less = range.first, more = range.second;
            if (index >= less && index <= more)
                return;
            else if (index < less)
                r = less - 1;
            else
                l = more + 1;
        }
    }
    void wiggleSort(vector<int>& nums) {
        int N = nums.size();
        //adjust(nums, 0, N - 1, N / 2);
        // 或利用nth_element进行类似的操作，但无法保证中间元素相同的都连在一块
        nth_element(nums.begin(), nums.begin() + N / 2, nums.end());
        int mid = N / 2;
        int i = mid + 1, j = mid + 1;
        while (j < N) {
            if (nums[j] == nums[mid]) swap(nums[i++], nums[j]);
            ++j;
        }
        i = mid - 1, j = mid - 1;
        while (j >= 0) {
            if (nums[j] == nums[mid]) swap(nums[i--], nums[j]);
            --j;
        }

        vector<int> tmp(N);
        int idx = -1;
        int halt = (N + 1) >> 1;
        for (int i = halt - 1, j = N - 1; i >= 0 && j >= halt; --i, --j) {
            tmp[++idx] = nums[i];
            tmp[++idx] = nums[j];
        }
        if (N & 1)
            tmp[++idx] = nums[0];
        for (int i = 0; i < N; ++i)
            nums[i] = tmp[i];
    }

};


// 改快排+完美洗牌

// 进阶做法，时间复杂度O(N)，额外空间复杂度O(1)
class Solution {
public:
    // 荷兰国旗问题
    pair<int, int> partition(vector<int>& arr, int l, int r, int pivot) {
        int less = l - 1, more = r + 1;
        int cur = l;
        while (cur < more) {
            if (arr[cur] < pivot)
                swap(arr[++less], arr[cur++]);
            else if (arr[cur] > pivot)      // 大的换过来不一定小于pivot，所以cur不++，还需要下次判断
                swap(arr[cur], arr[--more]);
            else
                ++cur;
        }
        return { less + 1,more - 1 };
    }
    void adjust(vector<int>& arr, int l, int r, int index) {
        int pivot = 0;
        while (l < r) {
            pivot = arr[l + rand() % (r - l + 1)];  // 使用随机数随机选一个位置作为坑点，RAND_MAX的范围32,767与最大长度相近可以随机
            auto range = partition(arr, l, r, pivot);
            int less = range.first, more = range.second;
            if (index >= less && index <= more)
                return;
            else if (index < less)
                r = less - 1;
            else
                l = more + 1;
        }
    }
    // 根据i位置得出下一个跑到的位置
    int modifyIndex(int i, int len) {
        return (2 * i) % (len + 1);
        // 或
        //return i <= len / 2 ? 2 * i : 2 * (i - len / 2) - 1;
    }
    // 三次反转
    void rotate(vector<int>& arr, int l, int m, int r) {
        // 注意 C++ reverse是对[l，r)上左开右闭进行反转的
        reverse(arr.begin() + l, arr.begin() + m + 1);
        reverse(arr.begin() + m + 1, arr.begin() + r + 1);
        reverse(arr.begin() + l, arr.begin() + r + 1);
    }
    void cycles(vector<int>& arr, int start, int len, int k) {
        // 找到每一个出发位置trigger，一共k个
        // 每一个trigger都进行下标连续推
        // 出发位置是从1开始算的，而数组下标是从0开始算的。
        for (int i = 0, trigger = 1; i < k; ++i, trigger *= 3) {
            int pre = arr[trigger + start - 1];
            int cur = modifyIndex(trigger, len);
            while (cur != trigger) {    // 只要不回到环的起点，就传
                int tmp = arr[cur + start - 1];
                arr[cur + start - 1] = pre;
                pre = tmp;
                cur = modifyIndex(cur, len);
            }
            arr[cur + start - 1] = pre;
        }
    }

    void shuffle(vector<int>& arr, int l, int r) {
        while (r - l + 1 > 0) {     // 一块一块切，每一块长度满足3^k-1
            int len = r - l + 1;
            int base = 3;   // 3^k
            int k = 1;      // 次方
            // 计算小于等于len并且是离len最近的，满足3^k-1的数
            // 即找到最大的k，满足3^k<=len+1
            while (base <= (len + 1) / 3) {
                base *= 3;
                ++k;
            }
            int halt = base - 1 >> 1;       // 左边一半，右边一半
            int mid = l + r >> 1;
            // 反转部分
            rotate(arr, l + halt, mid, mid + halt);
            // 循环下标怼
            cycles(arr, l, base - 1, k);
            l += base - 1;  // 下下块
        }
    }
    void wiggleSort(vector<int>& nums) {
        srand(time(NULL));
        int N = nums.size();
        // 调整原数组，使得第N/2大的排在中间，左边都比它小，右边都比它大
        adjust(nums, 0, N - 1, N / 2);

        if (N & 1) {
            shuffle(nums, 1, N - 1);
        } else {
            shuffle(nums, 0, N - 1);
            reverse(nums.begin(), nums.end());
        }

    }
};


// 或 索引转化
// 通过 (2×n−2×i−1)mod(n∣1) 我们可以知道原i位置最终的位置
// 我们直接对摆动排序后的数组进行 partition 操作即可，我们按照 partition 后的数组顺序进行遍历，
//然后依次进行比较交换即可，这样就避免了再次将数组进行拷贝复制。
// 利用虚拟地址访问元素，在虚拟空间中对数组进行3 - way - partition或排序，使数组在虚拟空间中满足某一空间关系。
// 完成后，数组在真实空间中的空间结构就是我们最终需要的空间结构。

class Solution {
public:
    int partitionAroundPivot(int left, int right, int pivot, vector<int>& nums) {
        int pivotValue = nums[pivot];
        int newPivot = left;
        swap(nums[pivot], nums[right]);
        for (int i = left; i < right; ++i) {
            if (nums[i] > pivotValue) {
                swap(nums[i], nums[newPivot++]);
            }
        }
        swap(nums[right], nums[newPivot]);
        return newPivot;
    }

    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        default_random_engine gen((random_device())());
        while (left <= right) {
            uniform_int_distribution<int> dis(left, right);
            int pivot = dis(gen);
            int newPivot = partitionAroundPivot(left, right, pivot, nums);
            if (newPivot == k - 1) {
                return nums[newPivot];
            } else if (newPivot > k - 1) {
                right = newPivot - 1;
            } else {
                left = newPivot + 1;
            }
        }
        return nums[k - 1];
    }

    inline int transAddress(int i, int n) {
        return (2 * n - 2 * i - 1) % (n | 1);
    }

    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        int x = (n + 1) / 2;
        int mid = x - 1;
        int target = findKthLargest(nums, n - mid);
        for (int k = 0, i = 0, j = n - 1; k <= j; k++) {
            if (nums[transAddress(k, n)] > target) {        // 原k位置排完后的位置
                while (j > k && nums[transAddress(j, n)] > target) {    // 原j位置排完后的位置
                    j--;
                }
                swap(nums[transAddress(k, n)], nums[transAddress(j--, n)]);
            }
            if (nums[transAddress(k, n)] < target) {
                swap(nums[transAddress(k, n)], nums[transAddress(i++, n)]);
            }
        }
    }
};
