
// 75. 颜色分类

// 荷兰国旗问题
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        // zero_edge表示0区域的边界，即前zero_edge都是0
        int left = 0, right = n, zero_edge = 0;
        while (left < right) {
            if (nums[left] == 2) {
                swap(nums[left], nums[--right]);
            } else if (nums[left] == 0) {
                swap(nums[left++], nums[zero_edge++]);
            } else {
                ++left;
            }
        }
    }
};

// 215. 数组中的第K个最大元素
// 快排思想
class Solution {
public:
    int partition(vector<int>& nums, int left, int right, int k) {
        int pivot = nums[left + rand() % (right - left)];
        int l = left, r = right, mid = left;

        // 荷兰国旗问题
        while (l < r) {
            if (nums[l] < pivot)
                swap(nums[l], nums[--r]);
            else if (nums[l] > pivot)
                swap(nums[l++], nums[mid++]);
            else
                ++l;
        }
        // 此时[left,mid) < pivot   mid=pivot [mid,right)>=pivot
        // 左闭右开
        if (mid == k) return nums[mid];
        if (mid > k) return partition(nums, left, mid, k);
        return partition(nums, mid + 1, right, k);

    }
    int findKthLargest(vector<int>& nums, int k) {
        srand(time(0));
        return partition(nums, 0, nums.size(), k - 1);      // k-1 ，从0开始
    }
};
// 或类似的，不使用荷兰国旗方法，使用换坑法
class Solution {
public:
    int partition(vector<int>& nums, int left, int right, int k) {
        int pos = left + rand() % (right - left);
        swap(nums[right - 1], nums[pos]);
        int pivot = nums[right - 1];

        int mid = left;
        for (int i = left; i < right - 1; ++i)
            if (nums[i] > pivot)
                swap(nums[mid++], nums[i]);
        swap(nums[mid], nums[right - 1]);

        // 此时[left,mid) < pivot   mid=pivot [mid,right)>=pivot
        // 左闭右开
        if (mid == k) return nums[mid];
        if (mid > k) return partition(nums, left, mid, k);
        return partition(nums, mid + 1, right, k);

    }
    int findKthLargest(vector<int>& nums, int k) {
        srand(time(0));
        return partition(nums, 0, nums.size(), k - 1);      // k-1 ，从0开始
    }
};

//  大根堆
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> heap;   // 大根堆
        k = nums.size() - k + 1;
        for (auto i : nums) {
            if (heap.size() < k) heap.push(i);
            else {
                if (i < heap.top()) {
                    heap.pop();
                    heap.push(i);
                }
            }
        }
        return heap.top();
    }
};
