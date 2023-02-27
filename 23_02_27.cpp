//4. 寻找两个正序数组的中位数
// 二分
// 思路：要找到第k小的元素，那么就取pivot1=nums1[k/2-1]和pivot=nums[k/2-1]进行比较
// num1 中小于等于pivot1的元素有 num1[0...k/2-2] 共k/2-1个，nums同理也有k/2-1个
// 取pivot=min(pivot1,pivot2) 两个数组中都小于pivoit的元素共计不超过k/2-1 + k/2-1 <= k-2个
// 这样pivot 本身最大也只能是k-1小的元素
// 如果pivot= pivot1,那么num1[0...k/2-1]都不可能是第k小的元素，把这些元素全部“删除”，剩下的作为新的num1数组，再修改对应的k值，nums2同理
// 总之：通过有序的条件，不断枚举两个数组中k/2-1的位置，一次去掉一批前面不可能的数。
// 时间O(log(m+n) ,初始k=(m+n)/2,之后每一轮循环可以将查找范围去除一半
class Solution {
public:
    int getKthElement(const vector<int>& num1, const vector<int>& num2,int k) {
        int n = num1.size();
        int m = num2.size();

        int index1 = 0, index2 = 0;
        while (true) {
            // 边界
            if (index1 == n) {
                return num2[index2 + k - 1];
            }
            if (index2 == m) {
                return num1[index1 + k - 1];
            }
            if (k == 1) {
                return min(num1[index1], num2[index2]);
            }

            // 一般情况
            int new_index1 = min(index1 + k / 2 - 1, n - 1);
            int new_index2 = min(index2 + k / 2 - 1, m - 1);
            int pivot1 = num1[new_index1];
            int pivot2 = num2[new_index2];

            if (pivot1 <= pivot2) {
                k -= new_index1 - index1 + 1;
                index1 = new_index1 + 1;
            } else {
                k -= new_index2 - index2 + 1;
                index2 = new_index2 + 1;
            }

        }
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int total_size = nums1.size() + nums2.size();
        if (total_size & 1) {
            return getKthElement(nums1, nums2, (total_size + 1) / 2);
        } else {
            return (getKthElement(nums1, nums2, total_size / 2) + getKthElement(nums1, nums2, total_size / 2 + 1)) / 2.0;
        }
    }
};


// 划分数组
// 分割数组，即假设中位数的分割线，在nums1中是i，在nums2中是j,那么就有，nums1[i-1]<=nums[j] && nums2[j-1]<=nums1[i]
// 利用这个关系式子进行分割线的二分，实际上我们只需要二分分割线i,j可以由i+j=(n+m+1)/2求出nums2的分割线
// 时间O（log(min(n,m)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size())
            nums1.swap(nums2);

        int n = nums1.size();
        int m = nums2.size();

        // 分割线左边的所有元素需要满足的个数
        int total_left = (n + m ) / 2;

        // 在nums1的区间[0,n]里查找恰当的分割线
        // 使得 nums1[i-1]<=nums[j] && nums2[j-1]<=nums1[i]
        int l = 0, r = n;
        // 寻找分割线，直到l==r,就可以在num1中直到一条分割线i，随后可利用分割线i+j=(n+m+1)/2求出nums2的分割线
        while (l < r) {
            int i = (l +r+1) / 2;       // 对i进行二分
            int j = total_left - i;

            if (nums1[i - 1] > nums2[j]) {  // nums1分割线左边的>nums2分割线右边的，说明nums1指针应该右移
                r = i - 1;
            } else {
                l = i;
            }

        }
        // 此时l就是分割线i
        int i = l;
        int j = total_left - i;
        // 边界处理
        int num1_lfet_max = i == 0 ? INT_MIN : nums1[i - 1];
        int num1_right_min = i == n ? INT_MAX : nums1[i];
        int num2_left_max = j == 0 ? INT_MIN : nums2[j - 1];
        int num2_right_min = j == m ? INT_MAX : nums2[j];

        // 注意total_left = (n + m + 1) / 2; 多加了1，应对奇数
        if ((n + m) & 1) {  // 奇，中位数在分割线的左边
            return min(num1_right_min, num2_right_min);
        } else {    // 偶，两个中位数在分割线的两侧，左侧找大，右侧找小
            return (max(num1_lfet_max, num2_left_max) + min(num1_right_min, num2_right_min)) / 2.0;
        }

    }
};