//˫ָ��

#include<iostream>
using namespace std;
#include<vector>
//283. �ƶ���

//���⿪��һ������
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


//�����ö�������
//����һ��λ��ָ��pos�����0��λ�ã�����ǰ�±��pos��ͬ���򽻻�Ԫ��
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


//��������ָ�룬left��¼0���±꣬right��¼��0�±�,
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

            if (nums[left] != 0)//�ҵ�0��λ�ã��ҵ������������λ���ֱ�Ϊ��0,��ʼ������0
                left++;
            right++;
        }
    }
};

//�ܽ�
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

//���ѣ�ǿ��������
//�ȸ��Ǻ��0
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



//167. ����֮�� II - ������������

//���ҵڶ��������ı߽磬��С���ҷ�Χ��������forǶ�ף����ɽ������Ч�ʲ��ߣ�Ϊ�˷����������������������ʹ�ö��ֲ���

class Solution 
{
public:
    vector<int> twoSum(vector<int>& numbers, int target) 
    {
        int n = numbers.size();
        vector<int> v;
        int max = 0;
        for (int i = 0; i < n; i++)//�ҵڶ��������ı߽�
        {
            if (numbers[i] > target- numbers[0])//  a+b=c  -->  b=c-a
            {
                max = i;
                break;
            }
        }
        if (max == 0)//����������targetС
            max = n-1;
        for (int i = 0; i < max; i++)//��һ����������ӵ���targrt���ҵ�һ�鷵�ؼ���
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
            //���Ч�ʣ�ʹ�ö��ֲ���
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


//˫ָ�뷨,�ֱ�ָ��ͷ��β�����м�������������ʹ���target���͵�С�㣬--high;����С��target���͵ô�㣬 ++low;
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
