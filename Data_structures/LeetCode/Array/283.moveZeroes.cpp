#include <vector>
#include <algorithm>

class Solution
{
public:
	void moveZeroes(std::vector<int>& nums)
	{
		int n = nums.size();
		int slow = 0;
		for (int fast = 0; fast < n; fast++)
		{
			if (nums[fast] != 0)
			{
				std::swap(nums[slow++], nums[fast]);
			}
		}
	}
};