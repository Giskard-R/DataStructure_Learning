struct ListNode
{
	int val;
	ListNode* next;

	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

#if 0 //µü´ú
class Solution
{
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
	{
		ListNode* dummy = new ListNode(0);
		ListNode* cur = dummy;

		while (list1 && list2)
		{
			if (list1->val <= list2->val)
			{
				cur->next = list1;
			}
			else
			{
				cur->next = list2;
			}
			cur = cur->next;
		}

		if (!list1)
		{
			cur->next = list1;
		}
		else
		{
			cur->next = list2;
		}
		ListNode* head = dummy->next;
		delete dummy;
		return head;
	}
};
#else //µİ¹é
class Solution
{
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
	{
		if (!list1)
			return list2;
		if (!list2)
			return list1;
		if (list1->val <= list2->val)
		{
			list1->next = mergeTwoLists(list1->next, list2);
			return list1;
		}
		else
		{
			list2->next = mergeTwoLists(list2->next, list1);
			return list2;
		}
	}
};

#endif