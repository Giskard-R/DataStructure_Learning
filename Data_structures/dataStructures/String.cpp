#if 0 // 串的顺序表示
#include <iostream>
#include <cstring>

class SqString
{
private:
	static const int MaxSize = 100;
	char data[MaxSize];
	int length;

public:
	SqString() : length(0) {}

	SqString(const char str[])
	{
		length = 0;
		while (str[length] != '\0' && length < MaxSize - 1)
		{
			data[length] = str[length];
			length++;
		}
	}

	bool IsEmpty() const
	{
		return length == 0;
	}

	int GetLength() const
	{
		return length;
	}

	bool Assign(const char str[])
	{
		length = 0;
		while (str[length] != '\0' && length < MaxSize - 1)
		{
			data[length] = str[length];
			length++;
		}

		return true;
	}

	int Compare(const SqString& other) const
	{
		int minLen = (length < other.length) ? length : other.length;
		int i = 0;
		while (i < minLen)
		{
			if (data[i] != other.data[i])
				return data[i] - other.data[i];

			i++;
		}
		return length - other.length;
	}

	bool Concat(const SqString& T)
	{
		if (length + T.length >= MaxSize)
			return false;

		for (int i = 0; i < T.length; i++)
		{
			data[length + i] = T.data[i];
		}

		length += T.length;
		return true;
	}

	bool SubString(SqString& sub, int pos, int len) const
	{
		if (pos<1 || pos>length || len<0 || pos + len - 1>length)
			return false;

		sub.length = 0;
		for (int i = 0; i < len; i++)
		{
			sub.data[i] = data[pos - 1 + i];
			sub.length++;
		}
		return true;
	}

	void Print() const
	{
		for (int i = 0; i < length; i++)
		{
			std::cout << data[i];
		}
		std::cout << std::endl;
	}
};

int main()
{
	SqString s1("abcde");
	SqString s2("xyz");
	std::cout << "s1: ";
	s1.Print();
	std::cout << "s2: ";
	s2.Print();

	SqString sub;
	s1.SubString(sub, 2, 3); // 从第2位取3个字符：bcd
	std::cout << "s1子串(2,3): ";
	sub.Print();

	s1.Concat(s2);
	std::cout << "s1连接s2：";
	s1.Print();

	SqString s3("abc");
	SqString s4("abd");
	std::cout << "s3 Compare s4 = " << s3.Compare(s4) << "\n";

	return 0;
}

#elif 0 // <string>实现顺序串

#include <iostream>
#include <string>

class SqString
{
private:
	std::string data;

public:
	SqString() :data("") {}

	SqString(const char* str) :data(str) {}

	SqString(const std::string& str) :data(str) {}

	bool IsEmpty() const
	{
		return data.empty();
	}

	int GetLength() const
	{
		return static_cast<int>(data.size());
	}

	bool Assign(const char* str)
	{
		data = str;
		return true;
	}

	int Compare(const SqString& other) const
	{
		return data.compare(other.data);
	}

	bool Concat(const SqString& T)
	{
		data += T.data;
		return true;
	}

	bool SubString(SqString& sub, int pos, int len) const
	{
		if (pos<1 || pos>GetLength() || len<=0 || pos + len - 1>GetLength())
			return false;

		sub.data = data.substr(pos - 1, len);
		return true;
	}

	void Print() const
	{
		std::cout << data << std::endl;
	}
};

int main()
{
	SqString s1("abcde");
	SqString s2("xyz");
	std::cout << "s1: ";
	s1.Print();
	std::cout << "s2: ";
	s2.Print();

	SqString sub;
	s1.SubString(sub, 2, 3); // 第2位置，取3个字符 → bcd
	std::cout << "s1子串(2,3): ";
	sub.Print();

	s1.Concat(s2);
	std::cout << "s1连接s2：";
	s1.Print();

	SqString s3("abc");
	SqString s4("abd");
	std::cout << "s3: ";
	s3.Print();
	std::cout << "s4: ";
	s4.Print();
	std::cout << "s3 Compare s4 = " << s3.Compare(s4) << "\n";

	return 0;
}

#elif 0 // 裸指针实现链式串

#include <iostream>

class LinkString
{
private:
	struct LNode
	{
		char ch;
		LNode* next;
		LNode(char c = '\0') :ch(c), next(nullptr) {}
	};

	LNode* head;

public:
	LinkString()
	{
		head = new LNode();
		std::cout << "LinkString created.\n";
	}

	LinkString(const char* str)
	{
		head = new LNode();
		LNode* rear = head;
		int i = 0;
		while (str[i] != '\0')
		{
			LNode* newNode = new LNode(str[i]);
			rear->next = newNode;
			rear = newNode;
			i++;
		}
	}

	~LinkString()
	{
		Clear();
		delete head;
		std::cout << "LinkString destroyed.\n";
	}

	bool IsEmpty() const
	{
		return head->next == nullptr;
	}

	int GetLength() const
	{
		int cnt = 0;
		LNode* p = head->next;
		while (p != nullptr)
		{
			cnt++;
			p = p->next;
		}

		return cnt;
	}

	bool Assign(const char* str)
	{
		Clear();
		LNode* rear = head;
		int i = 0;
		while (str[i] != '\0')
		{
			LNode* newNode = new LNode(str[i]);
			rear->next = newNode;
			rear = newNode;
			i++;
		}

		return true;
	}

	bool Concat(const LinkString& T)
	{
		LNode* rear = head;
		while (rear->next != nullptr)
		{
			rear = rear->next;
		}

		LNode* p = T.head->next;
		while (p != nullptr)
		{
			LNode* newNode = new LNode(p->ch);
			rear->next = newNode;
			rear = newNode;
			p = p->next;
		}

		return true;
	}

	bool SubString(LinkString& sub, int pos, int len) const
	{
		int totalLen = GetLength();
		if (pos<1 || pos>totalLen || len <= 0 || pos + len - 1 > totalLen)
			return false;

		sub.Clear();
		LNode* p = head->next;
		for (int i = 0; i < pos-1; i++)
		{
			p = p->next;
		}

		LNode* rear = sub.head;
		for (int i = 0; i < len; i++)
		{
			LNode* newNode = new LNode(p->ch);
			rear->next = newNode;
			rear = newNode;
			p = p->next;
		}
		return true;
	}

	void Print() const
	{
		if (IsEmpty())
			std::cout << "Empty\n";

		LNode* p = head->next;
		while (p != nullptr)
		{
			std::cout << p->ch;
			p = p->next;
		}
		std::cout << std::endl;
	}

	void Clear()
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
};

int main()
{
	LinkString s1("abcd");
	LinkString s2("xyz");
	std::cout << "s1: ";
	s1.Print();
	std::cout << "s2: ";
	s2.Print();

	LinkString sub;
	s1.SubString(sub, 2, 2); // 第2位取2个字符 bc
	std::cout << "s1子串(2,2): ";
	sub.Print();

	s1.Concat(s2);
	std::cout << "s1连接s2：";
	s1.Print();

	return 0;
}

#elif 0 // <list>实现链串

#include <iostream>
#include <list>

class LinkString
{
private:
	std::list<char> charList;
public:
	LinkString(){}

	LinkString(const char* str)
	{
		Assign(str);
	}

	bool IsEmpty() const
	{
		return charList.empty();
	}

	int GetLength() const
	{
		return static_cast<int>(charList.size());
	}

	bool Assign(const char* str)
	{
		Clear();
		int i = 0;
		while (str[i] != '\0')
		{
			charList.push_back(str[i]);
			i++;
		}

		return true;
	}

	bool Concat(const LinkString& T)
	{
		for (char ch : T.charList)
			charList.push_back(ch);

		return true;
	}

	bool SubString(LinkString& sub, int pos, int len)	const
	{
		int totalLen = GetLength();
		if (pos<1 || pos>totalLen || len <= 0 || pos + len - 1 > totalLen)
			return false;

		sub.Clear();
		auto it = charList.begin();
		for (int i = 0; i < pos-1; i++)
		{
			it++;
		}
		for (int i = 0; i < len; i++)
		{
			sub.charList.push_back(*it);
			it++;
		}
		return true;
	}

	void Print() const
	{
		if (IsEmpty())
			std::cout << "Empty.\n";

		for (char ch : charList)
			std::cout << ch;
		std::cout << std::endl;
	}

	void Clear()
	{
		charList.clear();
	}

	friend std::ostream& operator<<(std::ostream& os, const LinkString& str);
};

std::ostream& operator<<(std::ostream& os, const LinkString& str)
{
	for (char ch : str.charList)
		os << ch;
	return os;
}

int main()
{
	LinkString s1("abcd");
	LinkString s2("xyz");
	std::cout << "s1: ";
	s1.Print();
	std::cout << "s2: ";
	s2.Print();

	LinkString sub;
	s1.SubString(sub, 2, 2);
	std::cout << "s1子串(2,2): ";
	s1.Print();

	s1.Concat(s2);
	std::cout << "s1连接s2：";
	s1.Print();

	std::cout << "重载输出测试 s1 = " << s1 << "\n";

	return 0;
}
#endif