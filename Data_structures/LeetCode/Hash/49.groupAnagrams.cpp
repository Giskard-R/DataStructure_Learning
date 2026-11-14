#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> mp;
        for (const auto& s : strs)
        {
            auto key = s;
            std::sort(key.begin(), key.end());
            mp[key].emplace_back(s);
        }
        std::vector<std::vector<std::string>> res;
        for (auto& e : mp)
        {
            res.emplace_back(e.second);
        }
        return res;
    }
};