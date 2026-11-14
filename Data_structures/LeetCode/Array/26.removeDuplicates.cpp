#include <vector>

class Solution
{
public:
	int removeDuplicates(std::vector<int>& nums)
	{
		if (nums.empty())
			return 0;
		int slow = 0;
		for (int fast = 1; fast < nums.size(); fast++)
		{
			if (nums[slow] != nums[fast])
			{
				nums[++slow] = nums[fast];
			}
		}
		return slow + 1;
	}
};