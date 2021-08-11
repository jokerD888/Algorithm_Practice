
//˫ָ��
#include<iostream>
using namespace std;
#include<vector>
#include <numeric>
#include<algorithm>
#include<cmath>
//977. ���������ƽ��
//
//
////��ͨ�ⷨ����
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
////����sort��������ֱ������
////ʱ�临�Ӷȣ�O(nlogn)
////�ռ临�Ӷȣ�O(logn)�����˴洢�𰸵��������⣬������ҪO(logn) ��ջ�ռ��������
//
//
////˫ָ��
////������ԭ��������������������࿴���Ⱑ�Լ�����ˣ�����ÿ����ƽ���������ԭ���������������Ϊ�˽���
////�������ǵõ��������Ѿ�����������飬��˾Ϳ���ʹ�ù鲢�ķ������������ˡ�
////����أ�ʹ������ָ��ֱ�ָ��λ�� neg �� neg + 1��
////ÿ�αȽ�����ָ���Ӧ������ѡ���С���Ǹ�����𰸲��ƶ�ָ�롣��ĳһָ�������߽�ʱ������һָ�뻹δ�������������η���𰸡�
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
//            if (i < 0) //ȫ��������ʱj=0,ֱ�Ӵ�ͷ��β������ƽ�������
//            {
//                ans.push_back(nums[j] * nums[j]);
//                ++j;
//            }
//            else if (j == n) //ȫ����,��ʱi=n-1,��β��ͷ������ƽ�������
//            {
//                ans.push_back(nums[i] * nums[i]);
//                --i;
//            }
//            else if (nums[i] * nums[i] < nums[j] * nums[j]) //��ʱ���ݲ��ָ�������һ����������iΪ��������ָ�룬jΪ��������ָ�룬
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
//        for (int i = 0, j = n - 1, pos = n - 1; i <= j;)//i,jͷβָ�룬ѭ��ֱ����������������������β�Ϳ�ʼ��ͷ�����Ԫ��
//        {                                               //��Ϊƽ�����Ԫ�����ݣ����и���������£�ͷ��β���м���С��
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
////189. ��ת����//
//
////������ת��
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
//        //�����ÿ⺯��
//        reverse(nums.begin(), nums.end() - k );
//        reverse(nums.end() - k, nums.end());
//        reverse(nums.begin(), nums.end());
//
//    }
//};
//
////ʹ�ö��������
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
//        nums.assign(newArr.begin(), newArr.end());//����������
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
        //count����������Ϊ�� 0 ��ʼ���ϱ��������ջص���� 0�������������aȦ��a��Ϊ��������ÿȦ�ĳ���Ϊn
        //,��������У�ÿһ���ĳ���Ϊk,���߹���b��Ԫ�أ������ߵ��ܲ���Ϊbk��Ҳ����aȦ�ĳ��ȣ���a*n=b*k��
        //�� a*n һ��Ϊ n,k �Ĺ�����������Ϊ�����ڵ�һ�λص����ʱ�ͽ��������aҪ��С����a*n����n,k����С������lcm(n,k) ��
        // ��� b ��Ϊlcm(n,k)/k����˵��������ٴλص����Ĺ����л���ʵ�lcm(n,k)/k ��Ԫ�ء�
        //Ϊ�˷��ʵ����е�Ԫ�أ�������Ҫ���б����Ĵ���Ϊ��n/lcm(n,k)/k  -��  n*k/lcm(n,k)  ���ٽ�����Լ������С�������Ĺ�ϵ
        //��Ҫ�����Ĵ���Ϊn��k�����Լ��
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



