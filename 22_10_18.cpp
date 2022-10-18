// 315. 计算右侧小于当前元素的个数

// 归并排序
// 实际上就是求每个位置上逆序对的个数
class Solution {
public:
    // index 记录每个数字对应的原数组中的下标
    vector<int> index,temp,tempIndex,res;

    void Merge(vector<int>& a, int l, int mid, int r) {
        int i = l, j = mid + 1, p = l;
        while (i <= mid && j <= r)
        {
            if (a[i] <= a[j])
            {
                temp[p] = a[i];     
                tempIndex[p] = index[i];    // 修改下标，tmp[p]中元素的下标在原始数字中为index[i]
                res[index[i]] += (j - mid - 1); // a[i]<=a[j]那么，逆序对的个数就为j前面的哪些数
                ++i;               
                ++p;
            } else
            {
                temp[p] = a[j];
                tempIndex[p] = index[j];
                ++j;
                ++p;
            }
        }
        // 完成剩余的
        while (i <= mid)
        {
            temp[p] = a[i];
            tempIndex[p] = index[i];
            res[index[i]] += (j - mid - 1);
            ++i;
            ++p;
        }

        while (j <= r)
        {
            temp[p] = a[j];
            tempIndex[p] = index[j];
            ++j;
            ++p;
        }
        // 从临时数组放回原数组
        for (int k = l; k <= r; ++k)
        {
            index[k] = tempIndex[k];
            a[k] = temp[k];
        }
    }
    void MergeSort(vector<int>& a, int l, int r) {
        if (l >= r) return;

        int mid = (l + r) >> 1;
        MergeSort(a, l, mid);
        MergeSort(a, mid + 1, r);
        Merge(a, l, mid, r);
    }
    vector<int> countSmaller(vector<int>& nums) {
        int N = nums.size();
        index.resize(N);
        tempIndex.resize(N);
        temp.resize(N);
        res.resize(N);

        for (int i = 0; i < N; ++i) index[i] = i;
        MergeSort(nums, 0, N - 1);
        return res;
    }
};



// 离散化+树状数组
// 离散化：这里我们将原数组去重后排序，原数组每个数映射到去重排序后这个数对应位置的下标，
// 我们称这个下标为这个对应数字的 id。已知数字获取 id 可以在去重排序后的数组里面做二分查找，
// 已知 id 获取数字可以直接把 id 作为下标访问去重排序数组的对应位置
// 记value序列为v，我们可以看出它第i―1位的前缀和表示「有多少个数比i小」。
// 那么我们可以从后往前遍历序列u，记当前遍历到的元素为ai，我们把ai对应的桶的值自增1，记ai=p，
// 把v序列p-1位置的前缀和加入到答案中算贡献。为什么这么做是对的呢，因为我们在循环的过程中，我们把原序列分成了两部分，
// 后半部部分已经遍历过(已入桶)，前半部分是待遍历的(未入桶)，那么我们求到的p-1位置的前缀和就是「已入桶」的元素中比p小的元素的个数总和。
// 这种动态维护前缀和的问题我们可以用「树状数组」来解决。


class Solution {
public:
    vector<int> a, c;
    inline int lowbit(int x) {
        return x & (-x);
    }
    void update(int p) {
        while (p < c.size()) {
            c[p] += 1;
            p += lowbit(p);
        }
    }
    int query(int p) {
        int res = 0;
        while (p) {
            res += c[p];
            p -= lowbit(p);
        }
        return res;
    }
    inline int getId(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
    vector<int> countSmaller(vector<int>& nums) {
        int N = nums.size();
        vector<int> res(N);
        // 离散化
        a.assign(nums.begin(), nums.end());
        sort(a.begin(), a.end());   
        a.erase(unique(a.begin(), a.end()), a.end());       // 去重

        c.resize(nums.size());
        for (int i = N - 1; i >= 0; --i) {
            int id = getId(nums[i]);
            res[i] = query(id - 1);
            update(id);
        }
        return res;
    }
};

