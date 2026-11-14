#include <vector>
#include <stack>

class Solution {
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        int n = temperatures.size();
        std::vector<int> interval(n, 0);
        std::stack<int> st;

        for (int i = 0; i < n; i++)
        {
            while (!st.empty() && temperatures[i] > temperatures[st.top()])
            {
                int preIdx = st.top();
                interval[preIdx] = i - preIdx;
                st.pop();
            }
            st.push(i);
        }
        return interval;
    }
};