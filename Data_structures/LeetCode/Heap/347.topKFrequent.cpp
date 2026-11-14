#include <vector>
#include <unordered_map>
#include <queue>

class Solution
{
public:
	std::vector<int> topKFrequent(std::vector<int>& nums, int k)
	{
		using Pair = std::pair<int, int>;

		std::unordered_map<int, int> freq;
		std::priority_queue <Pair,std::vector<Pair> ,std::greater<Pair>> q;
		std::vector<int> res;

		for (const int& e : nums)
		{
			freq[e]++;
		}
		for (const auto& v : freq)
		{
			q.push({ v.second,v.first });
			if (q.size() > k)
				q.pop();
		}
		while (!q.empty())
		{
			res.emplace_back(q.top().second);
			q.pop();
		}
		return res;
	}
};