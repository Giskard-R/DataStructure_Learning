#include <vector>
#include <algorithm>

#if 0 //暴力解法
class Solution
{
public:
	int maxSubArray(std::vector<int>& nums)
	{
		int n = nums.size();
		int cur_max = nums[0];
		for (int i = 0; i < n; i++)
		{
			int sum = 0;
			for (int j = i; j < n; j++)
			{
				sum += nums[j];
				cur_max = std::max(cur_max, sum);
			}
		}
		return cur_max;
	}
};
#else //Kadane算法
class Solution
{
public:
	int maxSubArray(std::vector<int>& nums)
	{
		int n = nums.size();
		int curMax = nums[0];
		int gloMax = nums[0];
		for (int i = 1; i < n; i++)
		{
			//如果往事已成负担, 那你需要扔掉过去重新开始
			curMax = std::max(nums[i], curMax + nums[i]);
			gloMax = std::max(gloMax, curMax);
		}
		return gloMax;
	}
};

#endif

