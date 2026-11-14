#if 0 //顺序队列

#include <iostream>
#include <array>

class SqQueue
{
private:
	static const int MaxSize = 50;
	std::array<int, MaxSize> data;
	int front;
	int rear;

public:
	SqQueue() :front(0), rear(0) { std::cout << "SqQueue is created.\n"; }

	~SqQueue()
	{
		ClearQueue();
		std::cout << "SqQueue is destroyed.\n";
	}

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool IsFull() const
	{
		return rear == MaxSize;
	}

	bool EnQueue(int e)
	{
		if (IsFull())
			return false;

		data[rear++] = e;
		return true;
	}

	bool DeQueue(int& e)
	{
		if (IsEmpty())
			return false;

		e = data[front++];
		return true;
	}

	bool GetFront(int& e) const
	{
		if (IsEmpty())
			return false;

		e = data[front];
		return true;
	}

	void Print() const
	{
		std::cout << "Queue elements(front to rear): ";

		for (int i = front; i < rear; i++)
		{
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}

	void ClearQueue()
	{
		front = rear = 0;
	}
};

int main()
{
	SqQueue q;
	int val;
	q.EnQueue(11);
	q.EnQueue(22);
	q.EnQueue(33);
	q.EnQueue(44);
	q.EnQueue(55);
	q.Print();

	q.GetFront(val);
	std::cout << "队头：" << val << "\n";

	q.DeQueue(val);
	std::cout << "出队：" << val << "\n";
	q.Print();

	q.DeQueue(val);
	q.DeQueue(val); //队空，返回false
	return 0;
}

#elif 0 //顺序循环队列

#include <iostream>
#include <array>

class SqCirQueue
{
private:
	static const int MaxSize = 51;
	std::array<int, MaxSize> data;
	int front;
	int rear;

public:
	SqCirQueue() :front(0), rear(0) { std::cout << "SqCycleQueue is created.\n"; }

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool IsFull() const
	{
		return (rear + 1) % MaxSize == front;
	}

	bool EnQueue(int e)
	{
		if (IsFull())
			return false;

		data[rear] = e;
		rear = (rear + 1) % MaxSize;
		return true;
	}

	bool DeQueue(int& e)
	{
		if (IsEmpty())
			return false;

		e = data[front];
		front = (front + 1) % MaxSize;
		return true;
	}

	int GetLength() const
	{
		return (rear - front + MaxSize) % MaxSize;
	}

	void Print() const
	{
		if (IsEmpty())
		{
			std::cout << "Empty.\n";
		}

		int p = front;
		
		while (p != rear)
		{
			std::cout << data[p] << " ";
			p = (p + 1) % MaxSize;
		}
		std::cout << std::endl;
	}
};

int main()
{
	SqCirQueue q;
	q.EnQueue(10);
	q.EnQueue(20);
	q.EnQueue(30);
	q.EnQueue(40);
	std::cout << "队列元素：";
	q.Print();
	std::cout << "长度 = " << q.GetLength() << std::endl;

	int val;
	q.DeQueue(val);
	std::cout << "出队元素：" << val << std::endl;
	q.EnQueue(50);
	std::cout << "入队50后：";
	q.Print();

	return 0;
}

#elif 0 // vector实现循环队列

#include <iostream>
#include <vector>

class SqCirQueue
{
private:
	std::vector<int> data;
	int front;
	int rear;

public:
	SqCirQueue(int MaxSize)
	{
		data.resize(MaxSize);
		front = 0;
		rear = 0;
	}

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool IsFull() const
	{
		int MaxSize = static_cast<int>(data.size());
		return (rear + 1) % MaxSize == front;
	}

	bool EnQueue(int e)
	{
		int max_size = static_cast<int>(data.size());
		if (IsFull())
			return false;

		data[rear] = e;
		rear = (rear + 1) % max_size;
		return true;
	}

	bool DeQueue(int& e)
	{
		if (IsEmpty())
			return false;

		int max_size = static_cast<int>(data.size());
		e = data[front];
		front = (front + 1) % max_size;
		return true;
	}

	int GetLength() const
	{
		int max_size = static_cast<int>(data.size());
		return (rear - front + max_size) % max_size;
	}

	void Print() const
	{
		int max_size = static_cast<int>(data.size());
		if (IsEmpty())
			std::cout << "Empty.\n";

		int p = front;
		while (p != rear)
		{
			std::cout << data[p] << " ";
			p = (p + 1) % max_size;
		}
		std::cout << std::endl;
	}
};


int main()
{
	// 容量为5，最多存4个元素（牺牲1位）
	SqCirQueue q(5);
	q.EnQueue(10);
	q.EnQueue(20);
	q.EnQueue(30);
	q.EnQueue(40);
	std::cout << "队列元素：";
	q.Print();
	std::cout << "长度 = " << q.GetLength() << std::endl;

	int val;
	q.DeQueue(val);
	std::cout << "出队元素：" << val << std::endl;
	q.EnQueue(50);
	std::cout << "入队50后：";
	q.Print();

	return 0;
}

#elif 0 // 裸指针实现链式队列

#include <iostream>

class LinkQueue
{
private:
	struct LNode
	{
		int data;
		LNode* next;
		LNode(int val = 0) :data(val), next(nullptr){}
	};

	LNode* front;
	LNode* rear;

public:
	LinkQueue()
	{
		front = new LNode(0);
		rear = front;
		std::cout << "LinkQueue created.\n";
	}

	~LinkQueue()
	{
		while (front != nullptr)
		{
			LNode* q = front;
			front = front->next;
			delete q;
		}

		std::cout << "LinkQueue destroyed.\n";
	}

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool EnQueue(int e)
	{
		LNode* newNode = new LNode(e);
		rear->next = newNode;
		rear = newNode;
		return true;
	}

	bool DeQueue(int& e)
	{
		if (IsEmpty())
			return false;

		LNode* p = front->next;
		e = p->data;
		front->next = p->next;

		if (p == rear)
			rear = front;

		delete p;
		return true;
	}

	bool Getfront(int& e) const
	{
		if (IsEmpty())
			return false;

		e = front->next->data;
		return true;
	}

	void Print() const
	{
		if (IsEmpty())
			std::cout << "Empty.\n";

		LNode* p = front->next;
		while (p != nullptr)
		{
			std::cout << p->data << " ";
			p = p->next;
		}
		std::cout << std::endl;
	}
};

int main()
{
	LinkQueue q;
	q.EnQueue(10);
	q.EnQueue(20);
	q.EnQueue(30);
	std::cout << "队列元素：";
	q.Print();

	int val;
	q.DeQueue(val);
	std::cout << "出队元素：" << val << "\n";
	std::cout << "出队后队列：";
	q.Print();

	q.EnQueue(40);
	std::cout << "入队40：";
	q.Print();

	return 0;
}

#elif 0 // <list>实现链式队列

#include <iostream>
#include <list>

class LinkQueue
{
private:
	std::list<int> dataList;

public:
	bool IsEmpty() const
	{
		return dataList.empty();
	}

	bool EnQueue(int e)
	{
		dataList.push_back(e);
		return true;
	}

	bool DeQueue(int& e)
	{
		if (IsEmpty())
			return false;

		e = dataList.front();
		dataList.pop_front();
		return true;
	}

	bool GetFront(int& e) const
	{
		if (IsEmpty())
			return false;

		e = dataList.front();
		return true;
	}

	int GetLength() const
	{
		return static_cast<int>(dataList.size());
	}

	void Print() const
	{
		if (IsEmpty())
			std::cout << "Empty.\n";

		for (int num : dataList)
			std::cout << num << " ";

		std::cout << std::endl;
	}

	void Clear()
	{
		dataList.clear();
	}
};

int main()
{
	LinkQueue q;
	q.EnQueue(10);
	q.EnQueue(20);
	q.EnQueue(30);
	std::cout << "队列元素：";
	q.Print();
	std::cout << "长度 = " << q.GetLength() << "\n";

	int val;
	q.DeQueue(val);
	std::cout << "出队元素：" << val << "\n";
	std::cout << "出队后队列：";
	q.Print();

	q.EnQueue(40);
	std::cout << "入队40：";
	q.Print();

	return 0;
}

#endif