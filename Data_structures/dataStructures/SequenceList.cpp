#if 0 //顺序表 array实现

#include <iostream>
#include <array>
#define MaxSize 50

class SqList
{
private:
	std::array<int, MaxSize> data = { 0 };
	int length; //实际元素个数

public:
	SqList() :length(0) {}

	bool IsEmpty() const
	{
		return length == 0;
	}

	//按位查找, i从1开始
	bool GetElem(int i, int& e)
	{
		if (i<1 || i>length)
			return false;
		e = data[i - 1];
		return true;
	}

	//第i个位置插入元素e(i从1开始)
	bool InsertList(int i, int e)
	{
		if (i<1 || i>length + 1)
			return false;

		if (length >= MaxSize)
			return false;

		for (int j = length; j >= i; j--)
			data[j] = data[j - 1];

		data[i - 1] = e;
		length++;
		return true;
	}

	bool DeleteList(int i, int& e)
	{
		if (i<1 || i>length + 1)
			return false;

		e = data[i - 1];

		for (int j = i; j < length; j++)
		{
			data[j - 1] = data[j];
		}

		length--;
		return true;
	}

	void PrintList()
	{
		for (int i = 0; i < length; i++)
		{
			std::cout << data[i] << " ";
		}

		std::cout << '\n';
	}

	int GetLength()
	{
		return length;
	}

	void ClearList()
	{
		length = 0;
	}

};

int main()
{
	SqList L;

	L.InsertList(1, 10);
	L.InsertList(2, 20);
	L.InsertList(3, 30);
	std::cout << "插入后：";
	L.PrintList();

	int e;
	L.DeleteList(2, e);
	std::cout << "被删除元素：" << e << "\n";
	std::cout << "删除后：";
	L.PrintList();

	L.GetElem(2, e);
	std::cout << "第2个元素：" << e << "\n";

	L.ClearList();
}
#elif 0 // vector实现

#include <iostream>
#include <vector>

class SqList
{
private:
	std::vector<int> data;
public:
	int Length() const
	{
		return data.size();
	}

	bool IsEmpty() const
	{
		return data.empty();
	}

	void InsertTail(int val)
	{
		return data.emplace_back(val);
	}

	bool InsertList(int pos, int val)
	{
		if (pos < 0 || pos>data.size())
			return false;

		data.insert(data.begin() + pos, val);
		return true;
	}

	bool DeleteList(int pos, int& val)
	{
		if (pos<0 || pos>data.size())
			return false;

		val = data[pos];
		data.erase(data.begin() + pos);
		return true;
	}

	bool GetElem(int pos, int& val) const
	{
		if (pos<0 || pos>data.size())
			return false;

		val = data[pos];
		return true;
	}

	int LocateElem(int val) const
	{
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i] == val)
				return i;
		}
		return -1;
	}

	void ClearList()
	{
		return data.clear();
	}

	void PrintList() const
	{
		for (int num : data)
		{
			std::cout << num << " ";
		}
		std::cout << '\n';
	}
};

int main()
{
	SqList L;
	L.InsertTail(10);
	L.InsertTail(20);
	L.InsertTail(30);
	std::cout << "插入后：";
	L.PrintList();

	L.InsertList(1, 15);
	std::cout << "下标1插入15：";
	L.PrintList();

	int delVal;
	L.DeleteList(2, delVal);
	std::cout << "删除下标2元素：";
	L.PrintList();
	std::cout << "被删除元素：" << delVal << "\n";

	return 0;
}

#elif 0 //顺序表的有序合并

#include <iostream>
#include <array>
#define MaxSize 50

class SqList
{
private:
	std::array<int, MaxSize> data = { 0 };
	int length; //实际元素个数

public:
	SqList() :length(0) {}

	bool IsEmpty() const
	{
		return length == 0;
	}

	//按位查找, i从1开始
	bool GetElem(int i, int& e) const
	{
		if (i<1 || i>length)
			return false;
		e = data[i - 1];
		return true;
	}

	//第i个位置插入元素e(i从1开始)
	bool InsertList(int i, int e)
	{
		if (i<1 || i>length + 1)
			return false;

		if (length >= MaxSize)
			return false;

		for (int j = length; j >= i; j--)
			data[j] = data[j - 1];

		data[i - 1] = e;
		length++;
		return true;
	}

	bool DeleteList(int i, int& e)
	{
		if (i<1 || i>length + 1)
			return false;

		e = data[i - 1];

		for (int j = i; j < length; j++)
		{
			data[j - 1] = data[j];
		}

		length--;
		return true;
	}

	void Print()
	{
		for (int i = 0; i < length; i++)
		{
			std::cout << data[i] << " ";
		}

		std::cout << '\n';
	}

	int GetLength() const
	{
		return length;
	}

	void ClearList()
	{
		length = 0;
	}

	bool InsertTail(int val)
	{
		if (length >= MaxSize)
			return false;
		data[length++] = val;
		return true;
	}

	// ===== 有序合并函数（静态，La Lb有序，结果存入Lc，去重）=====
	static void MergeSqList_deduplicate(const SqList& La, const SqList& Lb, SqList& Lc)
	{
		Lc.ClearList();
		int i = 0;
		int j = 0;
		int lenA = La.length;
		int lenB = Lb.length;

		while (i < lenA && j < lenB)
		{
			if (La.data[i] < Lb.data[j])
			{
				Lc.InsertTail(La.data[i]);
				i++;
			}
			else if (Lb.data[j] < La.data[i])
			{
				Lc.InsertTail(Lb.data[j]);
				j++;
			}
			else
			{
				Lc.InsertTail(La.data[i]);
				i++;
				j++;
			}
		}

		while (i < lenA)
		{
			Lc.InsertTail(La.data[i]);
			i++;
		}

		while (j < lenB)
		{
			Lc.InsertTail(Lb.data[j]);
			j++;
		}
	}

	// ===== 有序合并函数【不去重】=====
	static void MergeSqList_duplicate(const SqList& La, const SqList& Lb, SqList& Lc)
	{
		Lc.ClearList();
		int i = 0;
		int j = 0;
		int lenA = La.length;
		int lenB = Lb.length;

		while (i < lenA && j < lenB)
		{
			if (La.data[i] <= Lb.data[j])
			{
				Lc.InsertTail(La.data[i]);
				i++;
			}
			else
			{
				Lc.InsertTail(Lb.data[j]);
				j++;
			}
			
		}

		while (i < lenA)
		{
			Lc.InsertTail(La.data[i]);
			i++;
		}

		while (j < lenB)
		{
			Lc.InsertTail(Lb.data[j]);
			j++;
		}
	}

	static void MergeAppend(const SqList& La, const SqList& Lb, SqList& Lc)
	{
		Lc.ClearList();
		int val;
		for (int i = 1; i <= La.GetLength(); i++)
		{
			La.GetElem(i, val);
			Lc.InsertTail(val);
		}

		for (int i = 1; i <= Lb.GetLength(); i++)
		{
			Lb.GetElem(i, val);
			Lc.InsertTail(val);
		}
	}
};

int main()
{
	SqList La, Lb, Lc;
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

	SqList::MergeAppend(La, Lb, Lc);
	std::cout << "拼接合并后Lc：";
	Lc.Print();

	std::cout << std::endl;

	std::cout << "La: ";
	La.Print();
	std::cout << "Lb: ";
	Lb.Print();

	SqList::MergeSqList_duplicate(La, Lb, Lc);
	std::cout << "不去重合并后Lc：";
	Lc.Print();

	std::cout << std::endl;

	std::cout << "La: ";
	La.Print();
	std::cout << "Lb: ";
	Lb.Print();

	SqList::MergeSqList_deduplicate(La, Lb, Lc);
	std::cout << "去重合并后Lc：";
	Lc.Print();


	return 0;
}

#endif