struct ListNode
{
	int val;
	ListNode* next;

	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
	ListNode* detectCycle(ListNode* head) {
		ListNode* slow = head;
		ListNode* fast = head;

		while (fast && fast->next)
		{
			fast = fast->next->next;
			slow = slow->next;
			if (fast==slow)
			{
				fast = head;
				while (fast != slow)
				{
					fast = fast->next;
					slow = slow->next;
				}
				return slow;
			}
		}
		return nullptr;
	}
};