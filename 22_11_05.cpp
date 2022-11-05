// 剑指 Offer 20. 表示数值的字符串

// 对所给数值进行三种类型的判断
// 注意细节较多
class Solution {
public:
    bool isfloat(string s) {
        if (s.size() < 2) return false;
        int index = 0;
        if (s[0] == '+' || s[0] == '-')
            ++index;
        int len = s.size();
        if (s[index] == '.') {
            int i;
            for (i = index + 1; i < len; ++i) {
                if (!isdigit(s[i]))
                    return false;
            }
            if (i == index + 1) return false;       // '.'后没有数字
        } else {
            while (index < len && isdigit(s[index]) && s[index] != '.')
                ++index;
            if (index >= len || s[index] != '.')
                return false;
            for (int i = index + 1; i < len; ++i) {
                if (!isdigit(s[i]))
                    return false;
            }
        }

        return true;
    }
    bool isinteger(string s) {
        if (s.empty()) return false;

        int len = s.size();
        int index = 0;
        if (s[0] == '+' || s[0] == '-')
            ++index;
        int i;
        for (i = index; i < len; ++i) {
            if (!isdigit(s[i]))
                return false;
        }
        return index != i;
    }
    bool isnum(string s) {
        int l = 0, r = 0;
        int len = s.size();
        // 跳过前面的空格
        while (l < len && s[l] == ' ')
            ++l;
        r = l;
        // 找到e的位置或空格的位置
        while (r < len && s[r] != 'e' && s[r] != 'E' && s[r] != ' ')
            ++r;
        // 截取空格之后到e或空格之间的字符串
        string substr = s.substr(l, r - l);
        // 如果中间的字符串既不是整数也不是小数，false

        if (!isinteger(substr) && !isfloat(substr))
            return false;


        // 后面即没有e,空格数也为0
        if (r >= len) return true;
        if (s[r] == ' ') {
            // 没有e,后面全是空格了
            for (int i = r; i < len; ++i) {
                if (s[i] != ' ')
                    return false;
            }

        } else {
            // 有e
            // 找到后面的整数
            l = r + 1;
            while (r < len && s[r] != ' ')
                ++r;
            if (l >= r || !isinteger(s.substr(l, r - l)))
                return false;

            for (int i = r; i < len; ++i) {
                if (s[i] != ' ')
                    return false;
            }
        }

        return true;
    }

    bool isNumber(string s) {
        return isnum(s) || isfloat(s) || isinteger(s);
    }
};



// 不妨先去掉首位的空格，简化代码
class Solution {
public:
    bool isfloat(string s) {
        if (s.size() < 2) return false;
        int len = s.size();
        int index = 0;
        if (s[0] == '+' || s[0] == '-')
            ++index;
        if (s[index] == '.') {
            int i;
            for (i = index + 1; i < len; ++i) {
                if (!isdigit(s[i]))
                    return false;
            }
            if (i == index + 1) return false;       // '.'后没有数字
        } else {
            // 找点
            while (index < len && isdigit(s[index]) && s[index] != '.')
                ++index;
            if (index >= len || s[index] != '.')
                return false;
            for (int i = index + 1; i < len; ++i) {
                if (!isdigit(s[i]))
                    return false;
            }
        }

        return true;
    }
    bool isinteger(string s) {
        if (s.empty()) return false;

        int len = s.size();
        int index = 0;
        if (s[0] == '+' || s[0] == '-')
            ++index;
        int i;
        for (i = index; i < len; ++i) {
            if (!isdigit(s[i]))
                return false;
        }
        return index != i;
    }
    bool isnum(string s) {
        int l = 0, r = 0;
        int len = s.size();
        // 找到e的位置
        while (r < len && s[r] != 'e' && s[r] != 'E')
            ++r;
        // 截取e之前的字符串
        string substr = s.substr(l, r - l);
        // 如果中间的字符串既不是整数也不是小数，false
        if (!isinteger(substr) && !isfloat(substr))
            return false;

        // 有e
        if (r < len) {
            if (!isinteger(s.substr(r + 1, len - r - l)))
                return false;
        }
        return true;
    }

    bool isNumber(string s) {
        // 去掉前后空格
        int i = 0, j = s.size() - 1;
        while (i < j && s[i] == ' ')
            ++i;
        while (i < j && s[j] == ' ')
            --j;
        s = s.substr(i, j - i + 1);
        return isnum(s) || isfloat(s) || isinteger(s);
    }
};


// 利用点，数字，正负号，大小e之间的互斥关系可以写得简洁一些
class Solution {
public:
    bool isNumber(string s) {
        if (s.size() == 0) return false;

        //跳过首尾空格
        int left = 0, right = s.length() - 1;
        while (left <= right && s[left] == ' ') {
            left++;
        }
        if (left > right) return false;
        while (left < right && s[right] == ' ') {
            right--;
        }

        bool isNum = false;
        bool isDot = false;
        bool isEe = false;
        bool isSign = false;

        for (int i = left; i <= right; i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                isNum = true;
            }
            // 一个'.'；e/E后面跟一个整数（不能有'.'）
            else if (s[i] == '.' && !isDot && !isEe) {
                isDot = true;
            }
            // 一个'E'或'e'；前面需要出现过数字
            else if ((s[i] == 'E' || s[i] == 'e') && isNum && !isEe) {
                isEe = true;
                //// 避免e结尾的情况 e后面得跟一个整数
                isNum = false;
            }
            // '+''-'只能出现在开头或者'E'或'e'的后一位
            else if ((s[i] == '+' || s[i] == '-') && (i == left || s[i - 1] == 'E' || s[i - 1] == 'e')) {
                isSign = true;
            } else {
                return false;
            }
        }
        // 必须以数字结尾
        return isNum;
    }
};



// 确定有限状态自动机

// 怎么挖掘出所有可能的状态呢 ? 一个常用的技巧是，用「当前处理到字符串的哪个部分」当作状态的表述。
//根据这一技巧，不难挖掘出所有状态 :
//1.起始的空格2.符号位3.整数部分
//   4.左侧有整数的小数点
//  5.左侧无整数的小数点（根据前面的第二条额外规则，需要对左侧有无整数的两种小数点做区分)
//  6.小数部分7.字符e
//  8.指数部分的符号位9.指数部分的整数部分10.未尾的空格


class Solution {
public:
    enum State {
        STATE_INITIAL,      // 初始状态
        STATE_INT_SIGN,     // 符号位
        STATE_INTEGER,      // 整数
        STATE_POINT,        // 小数点有整数
        STATE_POINT_WITHOUT_INT,    // 小数点左边没有整数
        STATE_FRACTION,         // 小数部分
        STATE_EXP,              // 指数e
        STATE_EXP_SIGN,         // 指数符号
        STATE_EXP_NUMBER,       // 指数数字
        STATE_END           // 结束
    };

    enum CharType {
        CHAR_NUMBER,        // 数字
        CHAR_EXP,           // 指数
        CHAR_POINT,         // 小数点
        CHAR_SIGN,          // 符号
        CHAR_SPACE,         // 空格
        CHAR_ILLEGAL        // 非法
    };

    CharType toCharType(char ch) {
        if (ch >= '0' && ch <= '9') {
            return CHAR_NUMBER;
        } else if (ch == 'e' || ch == 'E') {
            return CHAR_EXP;
        } else if (ch == '.') {
            return CHAR_POINT;
        } else if (ch == '+' || ch == '-') {
            return CHAR_SIGN;
        } else if (ch == ' ') {
            return CHAR_SPACE;
        } else {
            return CHAR_ILLEGAL;
        }
    }

    bool isNumber(string s) {
        unordered_map<State, unordered_map<CharType, State>> transfer{
            {
                STATE_INITIAL, {
                    {CHAR_SPACE, STATE_INITIAL},
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_POINT, STATE_POINT_WITHOUT_INT},
                    {CHAR_SIGN, STATE_INT_SIGN}
                }
            }, {
                STATE_INT_SIGN, {
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_POINT, STATE_POINT_WITHOUT_INT}
                }
            }, {
                STATE_INTEGER, {
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_POINT, STATE_POINT},
                    {CHAR_SPACE, STATE_END}
                }
            }, {
                STATE_POINT, {
                    {CHAR_NUMBER, STATE_FRACTION},
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_SPACE, STATE_END}
                }
            }, {
                STATE_POINT_WITHOUT_INT, {
                    {CHAR_NUMBER, STATE_FRACTION}
                }
            }, {
                STATE_FRACTION,
                {
                    {CHAR_NUMBER, STATE_FRACTION},
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_SPACE, STATE_END}
                }
            }, {
                STATE_EXP,
                {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                    {CHAR_SIGN, STATE_EXP_SIGN}
                }
            }, {
                STATE_EXP_SIGN, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER}
                }
            }, {
                STATE_EXP_NUMBER, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                    {CHAR_SPACE, STATE_END}
                }
            }, {
                STATE_END, {
                    {CHAR_SPACE, STATE_END}
                }
            }
        };

        int len = s.length();
        State st = STATE_INITIAL;

        for (int i = 0; i < len; i++) {
            CharType typ = toCharType(s[i]);
            if (transfer[st].find(typ) == transfer[st].end()) {
                return false;
            } else {
                st = transfer[st][typ];
            }
        }
        return st == STATE_INTEGER || st == STATE_POINT || st == STATE_FRACTION || st == STATE_EXP_NUMBER || st == STATE_END;
    }
};
