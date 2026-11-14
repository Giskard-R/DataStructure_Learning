#include <string>
#include <unordered_map>
class Solution {
public:
    bool isAnagram(std::string s, std::string t) {
        if (s.size() != t.size())
            return false;
        std::unordered_map<char, int> mp;
        for (const auto& ch : s)
            mp[ch]++;
        for (const auto& ch : t)
            mp[ch]--;
        for (const auto& e : mp)
            if (e.second)
                return false;
        return true;
    }
};