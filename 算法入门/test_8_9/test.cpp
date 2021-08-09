//二分查找算法练习


#include<iostream>
using namespace std;
#include<vector>

//704. 二分查找
//给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，
//写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 - 1。

class Solution 
{
public:
    int search(vector<int>& nums, int target) 
    {
        int left = 0;
        int right = nums.size()-1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (target == nums[mid])
                return mid;
            else if (target < nums[mid])
                right = mid - 1;
            else if (target > nums[mid])
                left = mid + 1;
        }
        return -1;
    }
};



//278. 第一个错误的版本


class Solution
{
public:
    int firstBadVersion(int n) 
    {
        if (isBadVersion(1))
            return 1;
        int left = 1;
        int right = n;
        while (left <= right)
        {
            int mid = left + ( right -left ) / 2;
            if (!isBadVersion(mid) && isBadVersion(mid+1))
                return mid+1; 
            else if (!isBadVersion(mid))
                left = mid + 1;
            else 
                right = mid - 1;
            
        }
        return -1;
    }
};
//卡到最后一步，发现测试案例给出的n达到了10^9级别，接近了int的最大值，于是当某次left+right时结果大于了int的额定大小，导致了溢出
//最次想到了用unsigned,最优解是int mid = left + (right - left) / 2;即可避免了计算时的溢出

//此局我负
//官方解,往常的二分查找的while条件时left<=right,在此巧妙修改为left<right即可为题所用，解决了此“分割”类题，一部分是true,另一部分是false
//虽然要一直循环到最后直达剩下一个元素，但每次循环都只调用了一次判断接口
class Solution {
public:
    int firstBadVersion(int n) 
    {
        int left = 1, right = n;
        while (left < right) // 此题的大环境下是一定有错误版本
        { // 循环直至区间左右端点相同
            int mid = left + (right - left) / 2; // 防止计算时溢出
            if (isBadVersion(mid)) 
            {
                right = mid; // 答案在区间 [left, mid] 中//这里mid没有减一
            }
            else 
            {
                left = mid + 1; // 答案在区间 [mid+1, right] 中
            }
        }
        // 此时有 left == right，区间缩为一个点，即为答案
        return left;
    }
};


//
//35. 搜索插入位置

class Solution
{
public:
    int searchInsert(vector<int>& nums, int target) 
    {
        int left = 0,right = nums.size() - 1;

        while (left < right)//使得区间最后只剩下一个元素，若在此之前，找到了就返回索引即可
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            else if (target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
        if (target <= nums[left])//剩的最后一个，结果无论是找到了，还是target小于这个元素，都只要返回这个原素索引即可
            return left;
        else
            return left + 1;//target大于这个元素，插入到后面即可
    }
};

//网上于此解法类似的有
//个人认为此为最优解
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) 
    {
        int low = 0;
        int high = nums.size() - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (nums[mid] == target)         
                return mid;
            else if (nums[mid] < target)
                low = mid + 1;
            else 
                high = mid - 1;
        }
        return low;
    }
}

class Solution
{
public:
    int searchInsert(vector<int>& nums, int target)
    {
        int left = 0,right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (nums[mid] >= target)
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left;
    }
};


//官解（此法较不易理解，此局我胜）
//设置了一个变量ans，记录这个“右边界”,若target < nums[mid]，这个边界还会缩小被修改，当这个target = nums[mid]，说明“右边界”找到了，
// 在找到之后的循环中“边界”都不会被修改了，最后返回的ans即target的索引
//若是找不到，不存在target这个元素，最后left>right跳出循环,此时ans的值即为要插入的位置，
//当最后一次循环只剩下一个元素时，无论时right = mid - 1;，还是 left = mid + 1;ans的值都是他们要插入的位置
var searchInsert = function(nums, target) 
{
    const n = nums.length;
    let left = 0, right = n - 1, ans = n;
    while (left <= right)
    {
        let mid = ((right - left) >> 1) + left;
        if (target <= nums[mid]) 
        {
            ans = mid;
            right = mid - 1;
        }
        else 
        {
            left = mid + 1;
        }
    }
    return ans;
};
