#include <vector>
#include <cstdlib>

class Solution
{
public:
	int partition(std::vector<int>& nums, int left, int right)
	{
		int ranIdx = left + std::rand() % (right - left + 1);
		std::swap(nums[left], nums[ranIdx]);
		int pivot = nums[left];
		while (left < right)
		{
			while (left < right && nums[right] >= pivot)
				right--;
			nums[left] = nums[right];

			while (left < right && nums[left] <= pivot)
				left++;
			nums[right] = nums[left];
		}
		nums[left] = pivot;
		return left;
	}

	int quickSelect(std::vector<int>& nums, int l, int r, int targetPos)
	{
		int pos = partition(nums, l, r);

		if (pos == targetPos)
			return nums[pos];
		else if (pos < targetPos)
			return quickSelect(nums, pos + 1, r, targetPos);
		else
			return quickSelect(nums, l, pos - 1, targetPos);
	}

	int findKthLargest(std::vector<int>& nums, int k)
	{
		int n = nums.size();
		int targetPos = n - k;
		return quickSelect(nums, 0, n - 1, targetPos);
	}
};