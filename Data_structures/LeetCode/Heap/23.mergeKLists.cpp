#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

class Solution
{
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
	{
		ListNode head;
		ListNode* cur = &head;
		while (l1 && l2)
		{
			if (l1->val <= l2->val)
			{
				cur->next = l1;
				l1 = l1->next;
			}
			else
			{
				cur->next = l2;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		cur->next = l1 ? l1 : l2;
		return head.next;
	}

	ListNode* merge(std::vector<ListNode*>& lists, int left, int right)
	{
		if (left > right)
			return nullptr;
		if (left == right)
			return lists[left];
		int mid = left + (right - left) / 2;
		ListNode* l1 = merge(lists, left, mid);
		ListNode* l2 = merge(lists, mid + 1, right);
		return mergeTwoLists(l1, l2);
	}

	ListNode* mergeKLists(std::vector<ListNode*>& lists)
	{
		return merge(lists, 0, lists.size() - 1);
	}
};