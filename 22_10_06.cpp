// 811. 子域名访问计数
class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> hs;
        for (auto& s : cpdomains) {
            int spacePos = s.find(' ');
            int num = stoi(s.substr(0, spacePos + 1));
            string ss = s.substr(spacePos+1);

            int pointPos = ss.find('.');
            while (pointPos!= ss.npos) {
                hs[ss] += num;
                ss = ss.substr(pointPos + 1);
                pointPos = ss.find('.');
            }
            hs[ss] += num;
        }

        vector<string> res;
        for (auto& [str, cnt] : hs) {
            res.push_back(to_string(cnt) + ' ' + str);
        }
        return res;
    }
};


// 150. 逆波兰表达式求值

class Solution {
public:
    typedef long long LL;
    LL cal(LL a, LL b, string opt) {
        LL res;
        if (opt == "+") {
            res = a + b;
        } else if (opt == "-") {
            res = a - b;
        } else if (opt == "*") {
            res = a * b;
        } else {
            res = a / b;
        }
        return res;
    }
    int evalRPN(vector<string>& tokens) {
        stack<LL> st;
        int N = tokens.size();
        for (int i = 0; i < N; ++i) {
            if (isdigit(tokens[i].back())) {
                st.push(stoi(tokens[i]));
            } else {
                LL a = st.top();
                st.pop();
                LL b = st.top();
                st.pop();
                st.push(cal(b, a, tokens[i]));
            }
        }
        return st.top();
    }
};