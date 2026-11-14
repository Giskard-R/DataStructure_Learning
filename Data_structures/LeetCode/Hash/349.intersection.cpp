#include <vector>
#include <unordered_set>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_set<int> ls(nums1.begin(), nums1.end());
        std::vector<int> res;
        for (const int& e : nums2)
        {
            if (ls.count(e))
            {
                res.emplace_back(e);
                ls.erase(e);
            }
        }
        return res;
    }
};