#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        std::stack<int> st;
        int maxArea = 0;
        heights.push_back(0);

        for (int i = 0; i < heights.size(); i++)
        {
            while (!st.empty() && heights[i] < heights[st.top()])
            {
                int curIdx = st.top();
                int height = heights[curIdx];
                st.pop();
                int left = st.empty() ? -1 : st.top();
                int width = i - left - 1;
                maxArea = std::max(maxArea, width * height);
            }
            st.push(i);
        }
        return maxArea;
    }
};