#include <vector>
#include <unordered_set>

class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        std::unordered_set<int> ls;
        int maxLen = 0;
        for (const auto& e : nums)
        {
            ls.insert(e);
        }
        for (const int& v : ls)
        {
            if (!ls.count(v - 1))
            {
                int cur = v;
                int curLen = 1;
                while (ls.count(cur+1))
                {
                    cur++;
                    curLen++;
                }
                if (curLen > maxLen)
                {
                    maxLen = curLen;
                }
            }
        }
        return maxLen;
    }
};