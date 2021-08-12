//双指针

#include<iostream>
using namespace std;
#include<vector>
//283. 移动零

//额外开辟一个数组
class Solution 
{
public:
    void moveZeroes(vector<int>& nums) 
    {
        vector<int> v(nums.size());
        int i = 0;
        for (auto e : nums)
        {
            if (e != 0)
            {
                v[i] = e;
                ++i;
            }
        }
        nums = v;
    }
};


//不利用额外数组
//利用一个位置指针pos来标记0的位置，若当前下标和pos不同，则交换元素
class Solution 
{
public:
    void moveZeroes(vector<int>& nums) 
    {
        int n = nums.size();
        int pos = 0;
        for (int i = 0; i < n; i++)
        {   
            if (nums[pos] != 0)
            {
                pos++;
            }
            else if ( i != pos && nums[i]!=0  )
            {
                int tmp = nums[pos];
                nums[pos] = nums[i];
                nums[i] = tmp;
                pos++;
                while (nums[pos] != 0)
                {
                    pos++;
                }
            }
        }
    }
};


//利用两个指针，left记录0的下标，right记录非0下标,
class Solution 
{
public:
    void moveZeroes(vector<int>& nums) 
    {
        int n = nums.size();
        int left = 0, right = 0;
        while (right < n)
        {
            if (left != right)
            {
                swap(nums[left], nums[right]);
            }

            if (nums[left] != 0)//找到0的位置，找到后，若交换则次位置又变为非0,开始往后找0
                left++;
            right++;
        }
    }
};

//管解
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size(), left = 0, right = 0;
        while (right < n) {
            if (nums[right]) {
                swap(nums[left], nums[right]);
                left++;
            }
            right++;
        }
    }
};

//网友，强啊，哈哈
//先覆盖后改0
class Solution {
    public void moveZeroes(int[] nums) 
    {
        int index = 0;
        for (int num : nums) 
        {
            if (num != 0) {
                nums[index++] = num;
            }
        }
        for (int i = index; i < nums.length; i++) 
        {
            nums[i] = 0;
        }
    }
}



//167. 两数之和 II - 输入有序数组

//先找第二个加数的边界，缩小查找范围。再两个for嵌套，即可解决，但效率不高，为此方法，利用有序这个条件，使用二分查找

class Solution 
{
public:
    vector<int> twoSum(vector<int>& numbers, int target) 
    {
        int n = numbers.size();
        vector<int> v;
        int max = 0;
        for (int i = 0; i < n; i++)//找第二个加数的边界
        {
            if (numbers[i] > target- numbers[0])//  a+b=c  -->  b=c-a
            {
                max = i;
                break;
            }
        }
        if (max == 0)//所有数都比target小
            max = n-1;
        for (int i = 0; i < max; i++)//因一定有两数相加等于targrt，找到一组返回即可
        {
            int dv = target - numbers[i];
            /*for (int j = i + 1; j < max; j++)
            {
                if (dv == numbers[j])
                {
                    v.push_back(i+1);
                    v.push_back(j+1);
                    return v;
                }
            }*/
            //提高效率，使用二分查找
            int left = i + 1, right = max;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                if (dv == numbers[mid])
                {
                    return { i + 1,mid + 1 };
                }
                else if (numbers[mid] > dv )
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }

            }
        }
        //return v;
        return { -1,-1 };
    }
};


//双指针法,分别指向头和尾，向中间遍历，所两数和大于target，和得小点，--high;若和小于target，和得大点， ++low;
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) 
    {
        int low = 0, high = numbers.size() - 1;
        while (low < high) 
        {
            int sum = numbers[low] + numbers[high];
            if (sum == target) 
            {
                return { low + 1, high + 1 };
            }
            else if (sum < target) 
            {
                ++low;
            }
            else 
            {
                --high;
            }
        }
        return { -1, -1 };
    }
};
