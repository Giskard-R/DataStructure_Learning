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
	ListNode* removeElements(ListNode* head, int val) {
		ListNode* dummy = new ListNode(0, head);
		ListNode* cur;
		cur = dummy;
		while (cur->next)
		{
			if (cur->next->val == val)
			{
				ListNode* del;
				del = cur->next;
				cur->next = cur->next->next;
				delete del;
			}
			else
				cur = cur->next;
		}
		ListNode* ans = dummy->next;
		delete dummy;
		return ans;
	}
};