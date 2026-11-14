#if 0 // <array> µœ÷À≥–Ú’ª

#include <iostream>
#include <array>

class SqStack
{
private:
	static constexpr int MaxSize = 50;
	std::array<int, MaxSize> data;
	int top;

public:
	SqStack()
	{
		top = 0;
	}

	bool IsEmpty() const
	{
		return top == 0;
	}

	bool IsFull() const
	{
		return top == MaxSize;
	}

	bool Push(int e)
	{
		if (IsFull())
			return false;

		data[top++] = e;
		return true;
	}

	bool Pop(int& e)
	{
		if (IsEmpty())
			return false;

		e = data[--top];
		return true;
	}

	bool GetTop(int& e) const
	{
		if (IsEmpty())
			return false;

		e = data[top - 1];
		return true;
	}

	void ClearStack()
	{
		top = 0;
	}

	void Print() const
	{
		int p = 0;

		std::cout << "’ªƒ⁄‘™Àÿ: ";

		while (p < top)
			std::cout <<data[p++] << " ";

		std::cout << '\n';
	}

	int GetLength()
	{
		return top;
	}
};

int main()
{
	SqStack st;
	st.Push(11);
	st.Push(22);
	st.Push(33);

	st.Print();

	std::cout << "’ª≥§: " << st.GetLength() << std::endl;

	int val;
	st.GetTop(val);
	std::cout << "’ª∂•‘™Àÿ£∫" << val << "\n";

	st.Pop(val);
	std::cout << "µØ≥ˆ‘™Àÿ£∫" << val << "\n";

	return 0;
}

#elif 0 // <vector> µœ÷À≥–Ú’ª

#include <iostream>
#include <vector>

class SqStack
{
private:
	std::vector<int> data;

public:
	bool IsEmpty() const
	{
		return data.empty();
	}

	bool Push(int e)
	{
		data.push_back(e);
		return true;
	}

	bool Pop(int e)
	{
		if (IsEmpty())
			return false;

		e = data.back();
		data.pop_back();
		return true;
	}

	bool GetTop(int& e) const
	{
		if (IsEmpty())
			return false;

		e = data.back();
		return true;
	}

	void ClearStack()
	{
		data.clear();
	}

	void Print() const
	{
		std::cout << "’ªƒ⁄‘™Àÿ: ";
		
		for (int val : data)
			std::cout << val << " ";

		std::cout << std::endl;
	}
};

int main()
{
	SqStack st;
	st.Push(11);
	st.Push(22);
	st.Print();

	int val;
	st.GetTop(val);
	std::cout << "’ª∂•‘™Àÿ£∫" << val << "\n";
	st.Pop(val);
	std::cout << "µØ≥ˆ‘™Àÿ£∫" << val << "\n";

	return 0;
}

#elif 0 // <stack> µœ÷À≥–Ú’ª

#include <iostream>
#include <stack>
#include <vector>

int main()
{
	std::stack<int, std::vector<int>> st;

	st.push(11);
	st.push(22);
	st.push(33);
	st.push(44);
	st.push(55);

	std::cout << "’ª∂•: " << st.top() << std::endl;
	st.pop();

	if (st.empty())
		std::cout << "’ªø’";

	std::cin.get();
}

#elif 0 // ¡¥’ª

#include <iostream>
#include <vector>

class LinkStack
{
private:
	struct LNode
	{
		int data;
		LNode* next;

		LNode(int val):data(val),next(nullptr){}
	};

	LNode* head;
public:
	LinkStack()
	{
		head = new LNode(0);
		head->next = nullptr;
		std::cout << "LinkStack is created.\n";
	}

	~LinkStack()
	{
		ClearStack();
		delete head;
		std::cout << "LinkStack is destroyed.\n";
	}

	bool IsEmpty() const
	{
		return head->next == nullptr;
	}

	bool Push(int e)
	{
		LNode* newNode = new LNode(e);
		newNode->next = head->next;
		head->next = newNode;
		return true;
	}

	bool Pop(int e)
	{
		if (IsEmpty())
			return false;

		LNode* p = head->next;
		e = p->data;
		head->next = p->next;
		delete p;
		return true;
	}

	bool GetTop(int& e) const
	{
		if (IsEmpty())
			return false;

		e = head->next->data;
		return true;
	}

	void ClearStack()
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

	void Print()
	{
		std::cout << "’ªƒ⁄‘™Àÿ(’ªµ◊->’ª∂•): ";
		std::vector<int> tmp;
		LNode* p = head->next;

		while (p != nullptr)
		{
			tmp.emplace_back(p->data);
			p = p->next;
		}

		for (auto it = tmp.rbegin(); it < tmp.rend(); it++)
		{
			std::cout << *it << " ";
		}

		std::cout << std::endl;
	}
};

int main()
{
	LinkStack st;
	st.Push(11);
	st.Push(22);
	st.Push(33);
	st.Print();

	int val;
	st.GetTop(val);
	std::cout << "’ª∂•‘™Àÿ£∫" << val << "\n";
	st.Pop(val);
	std::cout << "µØ≥ˆ‘™Àÿ£∫" << val << "\n";
	st.Print();
	return 0;
}

#endif