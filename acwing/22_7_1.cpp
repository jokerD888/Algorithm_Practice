// 102. 最佳牛围栏
// 二分+前缀和+双指针
// 思路，二分答案，牛的平均身高一定在[0,2000]之内，我们二分，若确实有某个长度的区间使得平均值大于mid，那么自然可以舍去[l,mid]
// 对于所二分的mid,就是我们假定的平均身高avg, 先在原数组每个数减去avg,再求前缀和，这样在减去avg后[j-F,j]这个区间若和大于0,说明实际答案大于等于假定的avg
// 我们使用双指针i,j  j是我们连续区间的右边界，i是最小的左边界即i=j-m,而1~i就是以j为右边界所有可能长度的左边界，
// 求的是区间和大于等于0，即sum[j]-sum[j-F]>=0,等同于sum[j]>=sum[j-F],即我们只要在[1,i]中的最小值使得sum[j]>=minv即可
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000 + 10;
int cows[N];
double sum[N];
int n, m;

bool check(double avg) {
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + cows[i] - avg;

	double minv = 0;	// sum[0]=0
	for (int i = 0, j = m; j <= n; ++j, ++i) {
		minv = min(minv, sum[i]);
		if (sum[j] >= minv) return true;
	}
	return false;
}

int main()
{

	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> cows[i];
	double l = 0, r = 2000;
	while (r - l > 1e-5) {
		double mid = (l + r) / 2;	// 实数不能用>>1
		if (check(mid)) l = mid;	 // 因为实数的稠密性，二分边界就不像整数+1，-1了
		else r = mid;
	}
	printf("%d\n", int(r * 1000));	// 因为答案是向下取整，所以选r
	return 0;
}	



// 113. 特殊排序
// 二分插入排序
// 使用插入排序，但对于要插入的位置使用二分查找，compare调用次数O(NlogN)<10000
// 查找大于等于要插入元素的位置i，然后将i及其往后的移1位插入，代码中先插入到最后，然后往前交换位置
class Solution {
public:
	vector<int> specialSort(int N) {
		vector<int> res;
		res.push_back(1);
		for (int i = 2; i <= N; i++) {
			int l = 0, r = res.size() - 1;
			while (l <= r) {
				int mid = l + r >> 1;
				if (compare(i, res[mid]))r = mid - 1;
				else l = mid + 1;
			}
			res.push_back(i);
			for (int j = res.size() - 2; j >= l; j--)   swap(res[j], res[j + 1]);
		}
		return res;
	}
};

// 或使用库函数stable_sort 基于归并排序，比较O(NlogN)
// 归并排序共递归logN层，每层需要比较O(N)次，故也符号题目要求
class Solution {
public:
	vector<int> specialSort(int N) {
		vector<int>v;
		for (int i = 1; i <= N; ++i)v.push_back(i);
		stable_sort(v.begin(), v.end(), compare);
		return v;
	}
};