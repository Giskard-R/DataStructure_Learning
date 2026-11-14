#include <vector>
#include <climits>

class Solution
{
public:
	int minSubArrayLen(int target, std::vector<int>& nums)
	{
		int n = nums.size();
		int left = 0;
		int sum = 0;
		int minLen = INT_MAX;
		for (int right = 0; right < n; right++)
		{
			sum += nums[right];
			while (sum >= target)
			{
				int curLen = right - left + 1;
				minLen = std::min(minLen, curLen);
				sum -= nums[left];
				left++;
			}
		}
		return minLen == INT_MAX ? 0 : minLen;
	}
};