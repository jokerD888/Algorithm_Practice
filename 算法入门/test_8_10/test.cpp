
//双指针
#include<iostream>
using namespace std;
#include<vector>
#include <numeric>
#include<algorithm>
#include<cmath>
//977. 有序数组的平方
//
//
////普通解法。。
//class Solution 
//{
//public:
//
//    vector<int> sortedSquares(vector<int>& nums)
//    {
//        for (int i = 0; i < nums.size(); i++)
//        {
//            nums[i] *= nums[i];
//        }
//        sort(nums.begin(), nums.end());
//    }
//};
////借助sort函数进行直接排序
////时间复杂度：O(nlogn)
////空间复杂度：O(logn)。除了存储答案的数组以外，我们需要O(logn) 的栈空间进行排序。
//
//
////双指针
////忽略了原数据是有序的条件。（多看题意啊自己）因此，若将每个数平方后，数组的原负数部分由升序变为了降序
////由于我们得到了两个已经有序的子数组，因此就可以使用归并的方法进行排序了。
////具体地，使用两个指针分别指向位置 neg 和 neg + 1，
////每次比较两个指针对应的数，选择较小的那个放入答案并移动指针。当某一指针移至边界时，将另一指针还未遍历到的数依次放入答案。
//
//class Solution 
//{
//public:
//    vector<int> sortedSquares(vector<int>& nums) 
//    {
//        int n = nums.size();
//        int negative = -1;
//        for (int i = 0; i < n; ++i) 
//        {
//            if (nums[i] < 0) 
//            {
//                negative = i;
//            }
//            else 
//            {
//                break;
//            }
//        }
//
//        vector<int> ans;
//        int i = negative, j = negative + 1;
//        while (i >= 0 || j < n) 
//        {
//            if (i < 0) //全正数，此时j=0,直接从头到尾的数据平方后插入
//            {
//                ans.push_back(nums[j] * nums[j]);
//                ++j;
//            }
//            else if (j == n) //全负数,此时i=n-1,从尾到头的数据平方后插入
//            {
//                ans.push_back(nums[i] * nums[i]);
//                --i;
//            }
//            else if (nums[i] * nums[i] < nums[j] * nums[j]) //此时数据部分负数，另一部分正数，i为负数部分指针，j为正数部分指针，
//            {
//                ans.push_back(nums[i] * nums[i]);
//                --i;
//            }
//            else 
//            {
//                ans.push_back(nums[j] * nums[j]);
//                ++j;
//            }
//        }
//
//        return ans;
//    }
//};
//
//
//
//class Solution
//{
//public:
//    vector<int> sortedSquares(vector<int>& nums) 
//    {
//        int n = nums.size();
//        vector<int> ans(n);
//        for (int i = 0, j = n - 1, pos = n - 1; i <= j;)//i,j头尾指针，循环直到两者相遇，从新容器的尾巴开始往头方向放元素
//        {                                               //因为平方后的元素数据，在有负数的情况下，头大尾大，中间最小，
//            if (nums[i] * nums[i] > nums[j] * nums[j]) 
//            {
//                ans[pos] = nums[i] * nums[i];
//                ++i;
//            }
//            else 
//            {
//                ans[pos] = nums[j] * nums[j];
//                --j;
//            }
//            --pos;
//        }
//        return ans;
//    }
//};
//
//
////189. 旋转数组//
//
////三步反转法
//class Solution 
//{
//public:
//    void Reverse(vector<int>& v, int left, int right)
//    {
//        while (left < right)
//        {
//            int tmp = v[left];
//            v[left] = v[right];
//            v[right] = tmp;
//            left++;
//            right--;
//        }
//    }
//    void rotate(vector<int>& nums, int k) 
//    {
//        int n = nums.size();
//        k = k % n;
//       /* Reverse(nums, 0, n-k - 1);
//        Reverse(nums, n-k, n-1);
//        Reverse(nums, 0, n - 1);*/
//        //或利用库函数
//        reverse(nums.begin(), nums.end() - k );
//        reverse(nums.end() - k, nums.end());
//        reverse(nums.begin(), nums.end());
//
//    }
//};
//
////使用额外的数组
//class Solution 
//{
//public:
//    void rotate(vector<int>& nums, int k) 
//    {
//        int n = nums.size();
//        vector<int> newArr(n);
//        for (int i = 0; i < n; ++i) 
//        {
//            newArr[(i + k) % n] = nums[i];
//        }
//        nums.assign(newArr.begin(), newArr.end());//拷贝回自身
//    }
//};

//                                                 
class Solution 
{                                    
public:
    int gcd(int a,int b)
    {
        int k = a < b ? a : b;
        for (int i = k; i > 0; i--)
        {
            if (a % i == 0 && b % i == 0)
                return i;
        }
    }
    void rotate(vector<int>& nums, int k) 
    {
        int n = nums.size();
        k = k % n;
        int count = gcd(n,k);
        //count的由来：因为从 0 开始不断遍历，最终回到起点 0，这个过程走了a圈（a正为整数），每圈的长度为n
        //,这个过程中，每一步的长度为k,共走过了b个元素，所以走的总步长为bk，也即这a圈的长度，即a*n=b*k。
        //即 a*n 一定为 n,k 的公倍数。又因为我们在第一次回到起点时就结束，因此a要最小，故a*n就是n,k的最小公倍数lcm(n,k) ，
        // 因此 b 就为lcm(n,k)/k，这说明从起点再次回到起点的过程中会访问到lcm(n,k)/k 个元素。
        //为了访问到所有的元素，我们需要进行遍历的次数为，n/lcm(n,k)/k  -》  n*k/lcm(n,k)  ，再结合最大公约数和最小公倍数的关系
        //需要遍历的次数为n和k的最大公约数
        for (int start = 0; start < count; ++start) 
        {
            int current = start;
            int prev = nums[start];
            do 
            {
                int next = (current + k) % n;
                swap(nums[next], prev);
                current = next;
            } while (start != current);
        }
    }
};
int main(void)
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    Solution s;
    s.rotate(v, 3);
}



