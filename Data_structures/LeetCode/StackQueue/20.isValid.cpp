#include <string>
#include <stack>

class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> st;
        for (char c : s)
        {
            //读取左括号并入栈
            if (c == '(' || c == '[' || c == '{')
                st.push(c);
            else //读取右括号
            {
                if (st.empty()) //栈空: 没有左括号
                    return false;

                // 有左括号, 取栈顶括号与当前右括号作判断
                char topCh = st.top();
                st.pop();

                //括号不匹配
                if (topCh != '(' && c == ')' ||
                    topCh != '[' && c == ']' ||
                    topCh != '{' && c == '}')
                    return false;
            }
        }
        // 判断栈内是否还有括号, 有括号返回false, 无括号返回true
        return st.empty();
    }
};