//���ֲ����㷨��ϰ


#include<iostream>
using namespace std;
#include<vector>

//704. ���ֲ���
//����һ�� n ��Ԫ������ģ������������� nums ��һ��Ŀ��ֵ target  ��
//дһ���������� nums �е� target�����Ŀ��ֵ���ڷ����±꣬���򷵻� - 1��

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



//278. ��һ������İ汾


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
//�������һ�������ֲ��԰���������n�ﵽ��10^9���𣬽ӽ���int�����ֵ�����ǵ�ĳ��left+rightʱ���������int�Ķ��С�����������
//����뵽����unsigned,���Ž���int mid = left + (right - left) / 2;���ɱ����˼���ʱ�����

//�˾��Ҹ�
//�ٷ���,�����Ķ��ֲ��ҵ�while����ʱleft<=right,�ڴ������޸�Ϊleft<right����Ϊ�����ã�����˴ˡ��ָ���⣬һ������true,��һ������false
//��ȻҪһֱѭ�������ֱ��ʣ��һ��Ԫ�أ���ÿ��ѭ����ֻ������һ���жϽӿ�
class Solution {
public:
    int firstBadVersion(int n) 
    {
        int left = 1, right = n;
        while (left < right) // ����Ĵ󻷾�����һ���д���汾
        { // ѭ��ֱ���������Ҷ˵���ͬ
            int mid = left + (right - left) / 2; // ��ֹ����ʱ���
            if (isBadVersion(mid)) 
            {
                right = mid; // �������� [left, mid] ��//����midû�м�һ
            }
            else 
            {
                left = mid + 1; // �������� [mid+1, right] ��
            }
        }
        // ��ʱ�� left == right��������Ϊһ���㣬��Ϊ��
        return left;
    }
};


//
//35. ��������λ��

class Solution
{
public:
    int searchInsert(vector<int>& nums, int target) 
    {
        int left = 0,right = nums.size() - 1;

        while (left < right)//ʹ���������ֻʣ��һ��Ԫ�أ����ڴ�֮ǰ���ҵ��˾ͷ�����������
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            else if (target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
        if (target <= nums[left])//ʣ�����һ��������������ҵ��ˣ�����targetС�����Ԫ�أ���ֻҪ�������ԭ����������
            return left;
        else
            return left + 1;//target�������Ԫ�أ����뵽���漴��
    }
};

//�����ڴ˽ⷨ���Ƶ���
//������Ϊ��Ϊ���Ž�
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


//�ٽ⣨�˷��ϲ�����⣬�˾���ʤ��
//������һ������ans����¼������ұ߽硱,��target < nums[mid]������߽绹����С���޸ģ������target = nums[mid]��˵�����ұ߽硱�ҵ��ˣ�
// ���ҵ�֮���ѭ���С��߽硱�����ᱻ�޸��ˣ���󷵻ص�ans��target������
//�����Ҳ�����������target���Ԫ�أ����left>right����ѭ��,��ʱans��ֵ��ΪҪ�����λ�ã�
//�����һ��ѭ��ֻʣ��һ��Ԫ��ʱ������ʱright = mid - 1;������ left = mid + 1;ans��ֵ��������Ҫ�����λ��
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
