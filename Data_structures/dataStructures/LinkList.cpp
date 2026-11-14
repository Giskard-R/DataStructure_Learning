#if 0 // 单链表 裸指针实现

#include <iostream>

class LinkList
{
private:
	struct LNode
	{
		int data;
		LNode* next;
	};

	LNode* head;

public:
	LinkList()
		:head(new LNode)
	{
		std::cout << "List is created!\n";

		head->next = nullptr;
	}

	~LinkList()
	{
		while (head != nullptr)
		{
			LNode* q = head;
			head = head->next;
			delete q;
		}

		std::cout << "List is destroyed!\n";
	}

	// 在第i个位置插入元素e，i从1开始
	bool InsertList(int i, int e)
	{
		if (i < 1)
			return false;

		LNode* p = head;

		for (int j = 0; j < i - 1; j++)
		{
			if (p == nullptr)
				return false;

			p = p->next;
		}

		LNode* newNode = new LNode;
		newNode->data = e;
		newNode->next = p->next;
		p->next = newNode;
		return true;
	}

	// 删除第i个结点，e接收被删除的值
	bool DeleteList(int i, int& e)
	{
		if (i < 1)
			return false;

		LNode* p = head;

		// p移动到被删结点的前驱
		for (int j = 0; j < i - 1; j++)
		{
			if (p->next == nullptr)
				return false;

			p = p->next;
		}

		LNode* del = p->next;

		if (del == nullptr)
			return false;

		e = del->data;
		p->next = del->next;
		delete del;
	}

	// 按位查找，获取第i个元素
	bool GetElemList(int i, int& e)
	{
		if (i < 1)
			return false;

		LNode* p = head->next;
		int j = 0;

		while (p != nullptr && j < i - 1)
		{
			p = p->next;
			j++;
		}

		if (p == nullptr)
			return false;

		e = p->data;
		return true;
	}

	// 按值查找：查找元素e，返回位序，找不到返回0
	int LocateElemList(int e)
	{
		LNode* p = head->next;
		int pos = 1;

		while (p != nullptr)
		{
			if (p->data == e)
				return pos;
			p = p->next;
			pos++;
		}

		return 0;
	}

	// 清空链表：删除所有数据结点，保留哑结点（头结点）
	void ClearList()
	{
		LNode* p = head->next;

		while (p != nullptr)
		{
			LNode* q = p;
			p = p->next;
			delete q;
		}
		head->next = nullptr;
	}

	void PrintList()
	{
		LNode* p = head->next;

		while (p != nullptr)
		{
			std::cout << p->data << " ";
			p = p->next;
		}
		std::cout << '\n';
	}

};

int main()
{
	LinkList L;
	L.InsertList(1, 10);
	L.InsertList(2, 20);
	L.InsertList(3, 30);
	std::cout << "插入后链表：";
	L.PrintList();

	int e;
	L.DeleteList(2, e);
	std::cout << "被删除元素：" << e << "\n";
	std::cout << "删除后链表：";
	L.PrintList();

	L.GetElemList(2, e);
	std::cout << "第2个元素：" << e << "\n";

	int pos = L.LocateElemList(30);
	if (pos != 0)
		std::cout << "元素30的位序：" << pos << "\n";
	else
		std::cout << "未找到该元素\n";

	L.ClearList();
	std::cout << "清空链表后：";
	L.PrintList();

	// 清空后仍然可以继续插入
	L.InsertList(1, 99);
	std::cout << "清空后插入99：";
	L.PrintList();

	return 0;
}

#elif 0 //shared_ptr实现单链表

#include <iostream>
#include <memory>

class LinkList
{
private:
	struct LNode
	{
		int data;
		std::shared_ptr<LNode> next;

		LNode(int val) :data(val), next(nullptr) {}
	};

	std::shared_ptr<LNode> head;

public:
	LinkList() { head = std::make_shared<LNode>(0); }

	bool IsEmpty() const
	{
		return head->next == nullptr;
	}

	int Length() const
	{
		int cnt = 0;
		auto cur = head->next;

		while (cur != nullptr)
		{
			cnt++;
			cur = cur->next;
		}
		return cnt;
	}

	void InsertTail(int val)
	{
		auto cur = head;

		while (cur->next != nullptr)
		{
			cur = cur->next;
		}

		cur->next = std::make_shared<LNode>(val);
	}

	bool InsertList(int pos, int val)
	{
		if (pos < 0)
			return false;

		auto cur = head;

		for (int i = 0; i < pos; i++)
		{
			if (cur->next == nullptr)
				return false;
			cur = cur->next;
		}

		auto newNode = std::make_shared<LNode>(val);
		newNode->next = cur->next;
		cur->next = newNode;
		return true;
	}

	bool DeleteList(int pos, int& val)
	{
		if (pos < 0)
			return false;

		auto cur = head;

		for (int i = 0; i < pos; i++)
		{
			if (cur->next == nullptr)
				return false;
			cur = cur->next;
		}

		auto del = cur->next;

		if (del == nullptr)
			return false;

		val = del->data;
		cur->next = del->next;
		return true;
	}

	bool GetElem(int pos, int& val) const
	{
		if (pos < 0)
			return false;

		auto cur = head->next;

		for (int i = 0; i < pos; i++)
		{
			if (cur == nullptr)
				return false;
			cur = cur->next;
		}

		if (cur == nullptr)
			return false;

		val = cur->data;
		return true;
	}

	int LocateElem(int val) const
	{
		int idx = 0;
		auto cur = head->next;

		while (cur != nullptr)
		{
			if (cur->data == val)
				return idx;

			cur = cur->next;
			idx++;
		}

		return -1;
	}

	void ClearList()
	{
		head->next = nullptr;
	}

	void PrintList() const
	{
		auto cur = head->next;
		while (cur != nullptr)
		{
			std::cout << cur->data << " ";
			cur = cur->next;
		}
		std::cout << '\n';
	}
};

int main()
{
	LinkList L;
	L.InsertTail(10);
	L.InsertTail(20);
	L.InsertTail(30);
	L.InsertTail(40);
	L.InsertTail(50);
	L.PrintList();

	L.InsertList(1, 15);
	L.PrintList();

	int delVal;
	L.DeleteList(2, delVal);
	std::cout << "删除的值：" << delVal << "\n";
	L.PrintList();

	// 测试GetElem
	int getVal;
	if (L.GetElem(1, getVal))
	{
		std::cout << "下标1元素：" << getVal << "\n";
	}

	// 测试LocateElem
	int pos = L.LocateElem(30);
	std::cout << "元素30的下标：" << pos << "\n";

	// 测试ClearList
	L.ClearList();
	std::cout << "清空后链表是否为空：" << (L.IsEmpty() ? "是" : "否") << "\n";

	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

#elif 0 //裸指针实现循环链表 

//-----------------------------------------------------------------------------------------------------------------------------------------


#include <iostream>

class CirLinkList
{
private:
	struct LNode
	{
		int data;
		LNode* next;
	};

	LNode* head;

public:
	CirLinkList()
	{
		head = new LNode;
		head->next = head;
	}

	~CirLinkList()
	{
		ClearList();
		delete head;
	}

	bool IsEmpty()
	{
		return head->next == head;
	}

	int Length() const
	{
		int cnt = 0;
		LNode* p = head;

		while (p->next != head)
		{
			cnt++;
			p = p->next;
		}

		return cnt;
	}

	bool InsertList(int i, int e)
	{
		if (i < 1)
			return false;

		LNode* p = head;
		int j = 0;

		while (j < i - 1 && p->next != head)
		{
			p = p->next;
			j++;
		}

		if (j < i - 1)
			return false;

		LNode* newNode = new LNode;
		newNode->data = e;
		newNode->next = p->next;
		p->next = newNode;
		return true;
	}

	bool DeleteList(int i, int& e)
	{
		if (i < 1 || IsEmpty())
			return false;

		LNode* p = head;
		int j = 0;

		while (j < i - 1 && p->next != head)
		{
			p = p->next;
			j++;
		}

		if (j < i - 1 || p->next == head)
			return false;

		LNode* del = p->next;
		e = del->data;
		p->next = del->next;
		delete del;
		return true;
	}

	bool GetElemList(int i, int& e)
	{
		if (i < 1 || IsEmpty())
			return false;

		LNode* p = head->next;
		int j = 0;

		while (j < i - 1 && p != head)
		{
			p = p->next;
			j++;
		}

		if (p == head)
			return false;

		e = p->data;
		return true;
	}

	int LocateElemList(int e)
	{
		if (IsEmpty())
			return 0;

		LNode* p = head->next;
		int pos = 1;

		while (p != head)
		{
			if (p->data == e)
				return pos;

			p = p->next;
			pos++;
		}

		return 0;
	}

	void ClearList()
	{
		LNode* p = head->next;

		while (p != head)
		{
			LNode* q = p;
			p = p->next;
			delete q;
		}

		head->next = head;
	}

	void PrintList()
	{
		if (IsEmpty())
			std::cout << "Linklist is empty.\n";

		LNode* p = head->next;

		while (p != head)
		{
			std::cout << p->data << " ";
			p = p->next;
		}

		std::cout << '\n';
	}
};


int main()
{
	CirLinkList L;
	L.InsertList(1, 10);
	L.InsertList(2, 20);
	L.InsertList(3, 30);
	std::cout << "插入后链表：";
	L.PrintList();

	int e;
	L.DeleteList(2, e);
	std::cout << "被删除元素：" << e << "\n";
	std::cout << "删除后链表：";
	L.PrintList();

	L.GetElemList(2, e);
	std::cout << "第2个元素：" << e << "\n";

	int pos = L.LocateElemList(30);
	if (pos != 0)
		std::cout << "元素30的位序：" << pos << "\n";
	else
		std::cout << "未找到\n";

	L.ClearList();
	std::cout << "清空链表后：";
	L.PrintList();
	L.InsertList(1, 99);
	std::cout << "清空后插入99：";
	L.PrintList();
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

#elif 0 // 裸指针实现双向链表

//-----------------------------------------------------------------------------------------------------------------------------------------


#include <iostream>

class DLinkList
{
private:
	struct LNode
	{
		int data;
		LNode* prior;
		LNode* next;
	};

	LNode* head;

public:
	DLinkList()
	{
		head = new LNode;
		head->prior = nullptr;
		head->next = nullptr;
		std::cout << "Double List created.\n";
	}

	~DLinkList()
	{
		ClearList();
		delete head;
		std::cout << "Double List destroyed.\n";
	}

	bool IsEmpty()
	{
		return head->next == nullptr;
	}

	int Length() const
	{
		int cnt = 0;
		LNode* p = head->next;

		while (p != nullptr)
		{
			p = p->next;
			cnt++;
		}

		return cnt;
	}

	bool InsertList(int i, int e)
	{
		if (i < 1)
			return false;

		LNode* p = head;
		int j = 0;

		while (j < i - 1 && p->next != nullptr)
		{
			p = p->next;
			j++;
		}

		if (j < i - 1)
			return false;

		LNode* newNode = new LNode;
		newNode->data = e;
		newNode->next = p->next;

		if (p->next != nullptr)
			p->next->prior = newNode;

		newNode->prior = p;
		p->next = newNode;
		return true;
	}

	bool DeleteList(int i, int& e)
	{
		if (i < 1 || IsEmpty())
			return false;

		LNode* p = head;
		int j = 0;

		while (j < i - 1 && p->next != nullptr)
		{
			p = p->next;
			j++;
		}

		if (j < i - 1 || p->next == nullptr)
			return false;

		LNode* del = p->next;
		e = del->data;
		p->next = del->next;

		if (del->next != nullptr)
			del->next->prior = p;

		delete del;
		return true;
	}

	bool GetElemList(int i, int& e)
	{
		if (i < 1 || IsEmpty())
			return false;

		LNode* p = head->next;
		int j = 0;

		while (p != nullptr && j < i - 1)
		{
			p = p->next;
			j++;
		}

		if (p == nullptr)
			return false;

		e = p->data;
		return true;
	}

	int LocateElemList(int e)
	{
		if (IsEmpty())
			return 0;

		LNode* p = head->next;
		int pos = 1;

		while (p != nullptr)
		{
			if (p->data == e)
				return pos;
			p = p->next;
			pos++;
		}

		return 0;
	}

	bool FrontInsert(int e)
	{
		LNode* newNode = new LNode;
		newNode->data = e;
		newNode->next = head->next;
		newNode->prior = head;
		head->next = newNode;

		if (head->next != nullptr)
			head->next->prior = newNode;

		return true;
	}

	bool TailInsert(int e)
	{
		LNode* p = head;

		while (p->next != nullptr)
			p = p->next;

		LNode* newNode = new LNode;
		newNode->data = e;
		newNode->next = nullptr;
		newNode->prior = p;
		p->next = newNode;
		return true;
	}

	void ClearList()
	{
		LNode* p = head->next;

		while (p != nullptr)
		{
			LNode* q = p;
			p = p->next;
			delete q;
		}

		head->next = nullptr;
	}

	void PrintList()
	{
		if (IsEmpty())
			std::cout << "List is empty.\n";

		LNode* p = head->next;

		while (p != nullptr)
		{
			std::cout << p->data << " ";
			p = p->next;
		}
		std::cout << '\n';
	}
};

int main()
{
	DLinkList list;
	list.FrontInsert(10);
	list.FrontInsert(20);
	list.TailInsert(30);
	std::cout << "链表：";
	list.PrintList(); // 输出 20 10 30

	int e;
	list.DeleteList(2, e);
	std::cout << "删除元素：" << e << "\n";
	std::cout << "链表：";
	list.PrintList();

	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

#elif 0 // <list>实现双向链表, <list>里的链表默认为双向循环链表

//-----------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <list>

class DoubleList
{
private:
	std::list<int> data;

public:
	bool IsEmpty() const
	{
		return data.empty();
	}

	void InsertFront(int val)
	{
		data.push_front(val);
	}

	void InsertTail(int val)
	{
		data.push_back(val);
	}

	bool DeleteVal(int val)
	{
		if (IsEmpty())
			return false;

		data.remove(val);
		return true;
	}

	void ClearList()
	{
		data.clear();
	}

	void Print() const
	{
		for (auto& v : data)
			std::cout << v << " ";

		std::cout << "\n";
	}

	bool GetElem(int pos, int& e) const
	{
		if (IsEmpty() || pos < 1)
			return false;

		auto it = data.begin();

		for (int i = 0; i < pos - 1; i++)
		{
			it++;

			if (it == data.end())
				return false;
		}

		e = *it;
		return true;
	}

	int LocateElem(int val) const
	{
		int idx = 1;
		auto it = data.begin();

		while (it != data.end())
		{
			if (*it == val)
				return idx;

			it++;
			idx++;
		}

		return 0;
	}

	bool InsertList(int pos, int val)
	{
		if (pos < 1)
			return false;

		auto it = data.begin();

		for (int i = 0; i < pos - 1; i++)
		{
			if (it == data.end())
				return false;

			it++;
		}

		data.insert(it, val);
		return true;
	}

	bool DeleteList(int pos, int& e)
	{
		if (IsEmpty() || pos < 1)
			return false;

		auto it = data.begin();

		for (int i = 0; i < pos - 1; i++)
		{
			it++;

			if (it == data.end())
				return false;
		}

		e = *it;
		data.erase(it);
		return true;
	}

	int ListLength() const
	{
		return static_cast<int> (data.size());
	}
};

int main()
{
	DoubleList dl;
	dl.InsertTail(10);
	dl.InsertTail(20);
	dl.InsertTail(30);
	std::cout << "初始链表：";
	dl.Print();
	std::cout << "链表长度：" << dl.ListLength() << "\n";

	// 按位插入，在第2位插入15
	dl.InsertList(2, 15);
	std::cout << "第2位插入15：";
	dl.Print();
	std::cout << "链表长度：" << dl.ListLength() << "\n";

	// 按位删除，删除第3个元素
	int delVal;
	dl.DeleteList(3, delVal);
	std::cout << "删除第3个元素，值为：" << delVal << "\n";
	std::cout << "删除后链表：";
	dl.Print();
	std::cout << "链表长度：" << dl.ListLength() << "\n";

	// 按位查找
	int res;
	if (dl.GetElem(2, res))
	{
		std::cout << "第2个元素：" << res << "\n";
	}

	// 按值查找
	int pos = dl.LocateElem(30);
	if (pos != 0)
		std::cout << "值30的位置：" << pos << "\n";
	else
		std::cout << "未找到\n";

	dl.ClearList();
	std::cout << "清空后，是否为空：" << (dl.IsEmpty() ? "是" : "否") << "\n";
	std::cout << "清空后链表长度：" << dl.ListLength() << "\n";
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

#elif 0 //裸指针实现双向循环链表

//-----------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>

class DoubleCirList
{
private:
	struct DNode
	{
		int data;
		DNode* prev;
		DNode* next;

		//形参初始化为0
		DNode(int val = 0) :data(val), prev(nullptr), next(nullptr) {}
	};

	DNode* head;

public:

	DoubleCirList()
	{
		head = new DNode();
		head->next = head;
		head->prev = head;
	}

	~DoubleCirList()
	{
		ClearList();
		delete head;
	}

	void ClearList()
	{
		DNode* p = head->next;

		while (p != head)
		{
			DNode* q = p;
			p = p->next;
			delete q;
		}

		head->next = head;
		head->prev = head;
	}

	bool IsEmpty() const
	{
		return head->next == head;
	}

	int ListLength() const
	{
		int len = 0;
		DNode* p = head->next;

		while (p != head)
		{
			p = p->next;
			len++;
		}

		return len;
	}

	void InsertFront(int val)
	{
		DNode* newNode = new DNode(val);
		newNode->next = head->next;
		newNode->prev = head;
		head->next->prev = newNode;
		head->next = newNode;
	}

	void InsertTail(int val)
	{
		DNode* newNode = new DNode(val);
		newNode->next = head;
		newNode->prev = head->prev;
		head->prev->next = newNode;
		head->prev = newNode;
	}

	bool InsertList(int pos, int val)
	{
		if (pos < 1)
			return false;

		DNode* p = head;
		int i = 0;

		while (p->next != head && i < pos - 1)
		{
			p = p->next;
			i++;
		}

		if (i != pos - 1)
			return false;

		DNode* newNode = new DNode(val);
		newNode->next = p->next;
		newNode->prev = p;
		p->next->prev = newNode;
		p->next = newNode;
		return true;
	}

	bool GetElem(int pos, int& e) const
	{
		if (IsEmpty() || pos < 1)
			return false;

		DNode* p = head->next;
		int i = 0;

		while (p != head && i < pos - 1)
		{
			p = p->next;
			i++;
		}

		if (p == head)
			return false;

		e = p->data;
		return true;
	}

	int LocateElem(int val) const
	{
		DNode* p = head->next;
		int idx = 1;

		while (p != head)
		{
			if (p->data == val)
				return idx;

			p = p->next;
			idx++;
		}

		return 0;
	}

	bool DeleteList(int pos, int& e)
	{
		if (IsEmpty() || pos < 1)
			return false;

		DNode* p = head->next;
		int i = 0;

		while (p != head && i < pos - 1)
		{
			p = p->next;
			i++;
		}

		if (p == head)
			return false;

		e = p->data;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		return true;
	}

	bool DeleteVal(int val)
	{
		DNode* p = head->next;

		while (p != head)
		{
			if (p->data == val)
			{
				p->next->prev = p->prev;
				p->prev->next = p->next;
				delete p;
				return true;
			}

			p = p->next;
		}

		return false;
	}

	void Print() const
	{
		DNode* p = head->next;

		while (p != head)
		{
			std::cout << p->data << " ";
			p = p->next;
		}

		std::cout << '\n';
	}

	// 有序合并：La,Lb递增，生成递增Lc，不去重
	static void MergeList_duplicate(const DoubleCirList& La, const DoubleCirList& Lb, DoubleCirList& Lc)
	{
		Lc.ClearList();
		int i = 1;
		int j = 1;
		int va;
		int vb;
		bool ha = La.GetElem(i, va);
		bool hb = Lb.GetElem(j, vb);

		while (ha && hb)
		{
			if (va <= vb)
			{
				Lc.InsertTail(va);
				i++;
				ha = La.GetElem(i, va);
			}
			else
			{
				Lc.InsertTail(vb);
				j++;
				hb = Lb.GetElem(j, vb);
			}
		}

		while (ha)
		{
			Lc.InsertTail(va);
			i++;
			ha = La.GetElem(i, va);
		}

		while (hb)
		{
			Lc.InsertTail(vb);
			j++;
			hb = Lb.GetElem(j, vb);
		}
	}

	static void MergeList_deduplicate(const DoubleCirList& La, const DoubleCirList& Lb, DoubleCirList& Lc)
	{
		Lc.ClearList();
		int i = 1;
		int j = 1;
		int va;
		int vb;
		bool ha = La.GetElem(i,va);
		bool hb = Lb.GetElem(j,vb);

		while (ha && hb)
		{
			if (va < vb)
			{
				Lc.InsertTail(va);
				i++;
				ha = La.GetElem(i, va);
			}
			else if (va > vb)
			{
				Lc.InsertTail(vb);
				j++;
				hb = Lb.GetElem(j, vb);
			}
			else
			{
				Lc.InsertTail(va);
				i++;
				j++;
				ha = La.GetElem(i, va);
				hb = Lb.GetElem(j, vb);
			}
		}

		while (ha)
		{
			Lc.InsertTail(va);
			i++;
			ha = La.GetElem(i, va);
		}

		while (hb)
		{
			Lc.InsertTail(vb);
			j++;
			hb = Lb.GetElem(j, vb);
		}
	}

	static void MergeAppend(const DoubleCirList& La, const DoubleCirList& Lb, DoubleCirList& Lc)
	{
		Lc.ClearList();
		int val;

		for (int i = 1; i <= La.ListLength(); i++)
		{
			La.GetElem(i, val);
			Lc.InsertTail(val);
		}

		for (int i = 1; i <= Lb.ListLength(); i++)
		{
			Lb.GetElem(i, val);
			Lc.InsertTail(val);
		}
	}
};

int main()
{
	DoubleCirList dcl;
	dcl.InsertTail(10);
	dcl.InsertTail(20);
	dcl.InsertTail(30);
	std::cout << "初始链表：";
	dcl.Print();
	std::cout << "长度：" << dcl.ListLength() << "\n";

	dcl.InsertList(2, 15);
	std::cout << "第2位插入15：";
	dcl.Print();

	int delVal;
	dcl.DeleteList(3, delVal);
	std::cout << "删除第3个元素，值=" << delVal << "\n";
	std::cout << "删除后：";
	dcl.Print();

	int e;
	if (dcl.GetElem(2, e))
		std::cout << "第2个元素：" << e << "\n";

	int pos = dcl.LocateElem(30);
	if (pos != 0)
		std::cout << "30位于第" << pos << "位\n";

	dcl.ClearList();
	std::cout << "清空后是否为空：" << (dcl.IsEmpty() ? "是" : "否") << "\n";

	DoubleCirList La, Lb, Lc;
	La.InsertTail(1);
	La.InsertTail(3);
	La.InsertTail(5);
	La.InsertTail(7);
	Lb.InsertTail(2);
	Lb.InsertTail(3);
	Lb.InsertTail(6);
	Lb.InsertTail(8);

	std::cout << "La: ";
	La.Print();
	std::cout << "Lb: ";
	Lb.Print();

	DoubleCirList::MergeList_duplicate(La, Lb, Lc);
	std::cout << "合并后Lc（有序不去重）：";
	Lc.Print();

	std::cout << std::endl;

	std::cout << "La: ";
	La.Print();
	std::cout << "Lb: ";
	Lb.Print();

	DoubleCirList::MergeList_deduplicate(La, Lb, Lc);
	std::cout << "合并后Lc（有序去重）：";
	Lc.Print();

	std::cout << std::endl;

	std::cout << "La: ";
	La.Print();
	std::cout << "Lb: ";
	Lb.Print();

	DoubleCirList::MergeAppend(La, Lb, Lc);
	std::cout << "合并后Lc：";
	Lc.Print();

	std::cin.get();
	return 0;
}

#endif