// 907. 子数组的最小值之和

// 单调栈
// 我们枚举每个位置i作为最小值，且找到以该位置为最小值的区间数目
// 要找到所有的区间数目，不妨找以i结尾且i是最小值的子序列数目left,再找以i开头且i是最小值的子序列的数目right，
// left*right即为以i位置作为最小值的子序列数目，为防止重复计算，left子序列包含大于等于，而right子序列仅包含大于
// 这个过程可以用单调栈来解决
// 使用单调递增栈来找到左边比它小的，离他最近的位置，右边找离他近的，小于等于他的
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int N = arr.size();
        vector<int> left(N);
        vector<int> right(N);
        stack<int> st;
        for (int i = 0; i < N; ++i) {       // 找左边的
            while (st.size() && arr[st.top()] >= arr[i]) {   // 栈顶元素大于当前元素，弹出
                st.pop();
            }
            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        while (st.size()) st.pop();
        for (int i = N - 1; i >= 0; --i) {       // 找右边的
            while (st.size() && arr[st.top()] > arr[i]) {  // 栈顶元素大于等于当前元素
                st.pop();
            }
            right[i] = st.empty() ? N : st.top();
            st.push(i);
        }
        int res = 0;
        const int mod = 1e9 + 7;
        for (int i = 0; i < N; ++i) {

            int l = i - left[i];
            int r = right[i] - i;
            res += (1ll * arr[i] * l * r) % mod;
            res %= mod;
        }
        return res;
    }
};


// dp + 单调栈
// 设dp[i] 是以i结尾的子序列的最小值的和
// 那么返回累加dp[i] （i的取值[0,N)） 即可
// 明显的dp[0]=arr[0],
// 对于普遍的位置i，我们可以分为两部分
//  1）以arr[i]最为最小值的子序列  2)不以arr[i]作为最小值的子序列
//  情况1： dp[i]=arr[i]*(i+1)
//  情况2： 我们找到其左边比它小的离它最近的位置j，dp[i]=dp[j]+arr[i]*(i-j)
//          情况2之所以这么做，是因为可以根据j位置分为包含j位置的子序列和不包含j位置的子序列
//          所有包含包含j位置的子序列和和，恰好是do[j] ,不包含j位置的子序列，则是arr[i]*(i-j)
// 所以我们同样利用单调栈来找出其左边比它小的离它最近的
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int N = arr.size();
        int res = 0;
        const int mod = 1e9 + 7;
        vector<int> dp(N);
        stack<int> st;
        for (int i = 0; i < N; ++i) {  // 找左边比它小的
            while (st.size() && arr[i] < arr[st.top()]) {
                st.pop();
            }
            dp[i] = st.empty() ? arr[i] * (i + 1) : arr[i] * (i - st.top()) + dp[st.top()];
            st.push(i);
            res = (res + dp[i]) % mod;
        }
        return res;
    }
};
