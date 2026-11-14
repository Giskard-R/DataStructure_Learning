#if 0 // 顺序表的查找

#include <iostream>
#include <vector>
//有序表
int SearchSeq(const std::vector<int>& a, int key)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == key)
			return i;
		if (a[i] > key)
			break;
	}
	return -1;
}

int BinarySearch(const std::vector<int>& a, int key)
{
	int low = 0;
	int high = static_cast<int>(a.size()) - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (a[mid] == key)
		{
			return mid;
		}
		else if (a[mid] > key)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return -1;
}

int LowerBound(const std::vector<int>& a, int key)
{
	int low = 0;
	int high = static_cast<int>(a.size()) - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (a[mid] >= key)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return low;
}

// ===================== 分块查找（索引顺序查找） =====================
struct IndexItem
{
	int maxKey;
	int startPos;
};

std::vector<IndexItem> BuildIndex(const std::vector<int>& a, int blockSize)
{
	std::vector<IndexItem> indexTable;
	int n = static_cast<int>(a.size());
	for (int i = 0; i < n; i += blockSize)
	{
		IndexItem item;
		item.startPos = i;
		int end = i + blockSize - 1;
		if (end >= n)
			end = n - 1;
		item.maxKey = a[end];
		indexTable.emplace_back(item);
	}

	std::cout << "\n===== 索引表信息 =====\n";
	std::cout << "maxKey\tstartPos\n";
	for (const auto& item : indexTable)
	{
		std::cout << item.maxKey << "\t" << item.startPos << std::endl;
	}
	std::cout << "======================\n\n";
	return indexTable;
}

int BlockSearch(std::vector<int>& a, const std::vector<IndexItem>& indexTable, int key)
{
	int l = 0;
	int r = static_cast<int>(indexTable.size()) - 1;
	int targetBlockId = -1;

	while (l <= r)
	{
		int mid = l + (r - l) / 2;
		if (indexTable[mid].maxKey >= key)
		{
			targetBlockId = mid;
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	if (targetBlockId == -1)
		return -1;

	int start = indexTable[targetBlockId].startPos;
	int end;
	if (targetBlockId + 1 < static_cast<int>(indexTable.size()))
	{
		end = indexTable[targetBlockId + 1].startPos - 1;
	}
	else
	{
		end = static_cast<int>(a.size()) - 1;
	}

	for (int i = start; i <= end; i++)
	{
		if (a[i] == key)
			return i;
	}
	return -1;
}

int main()
{
	std::vector<int> arr = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
	int blockSize = 3;
	auto index = BuildIndex(arr, blockSize);

	int target;
	std::cout << "input key: ";
	std::cin >> target;

	int posSeq = SearchSeq(arr, target);
	if (posSeq != -1)
		std::cout << "有序顺序查找：pos = " << posSeq << "\n";
	else
		std::cout << "有序顺序查找：not found\n";

	int posBin = BinarySearch(arr, target);
	if (posBin != -1)
		std::cout << "二分精准查找：pos = " << posBin << "\n";
	else
		std::cout << "二分精准查找：not found\n";

	int posLow = LowerBound(arr, target);
	std::cout << "lower_bound下标：" << posLow << "\n";

	int posBlock = BlockSearch(arr, index, target);
	if (posBlock != -1)
		std::cout << "分块查找：pos = " << posBlock << "\n";
	else
		std::cout << "分块查找：not found\n";

	return 0;
}
#elif 0 //树表的查找 -- BST

#include <iostream>

class BST
{
private:
	struct BSTNode
	{
		int key;
		BSTNode* left;
		BSTNode* right;
		BSTNode(int k) : key(k), left(nullptr), right(nullptr) {}
	};

	BSTNode* root;

	BSTNode* search(BSTNode* p, int key) const
	{
		if (p == nullptr || p->key == key)
		{
			return p;
		}
		if (key < p->key)
			return search(p->left, key);
		else
			return search(p->right, key);
	}

	BSTNode* insert(BSTNode* p, int key)
	{
		if (p == nullptr)
			return new BSTNode(key);
		if (key < p->key)
			p->left = insert(p->left, key);
		else if (key > p->key)
			p->right = insert(p->right, key);
		return p;
	}

	BSTNode* getMin(BSTNode* p) const
	{
		while (p->left)
			p = p->left;
		return p;
	}

	BSTNode* remove(BSTNode* p, int key)
	{
		if (!p)
			return nullptr;
		if (key < p->key)
			p->left = remove(p->left, key);
		else if (key > p->key)
			p->right = remove(p->right, key);
		else
		{
			if (!p->left)
			{
				BSTNode* temp = p->right;
				delete p;
				return temp;
			}
			if (!p->right)
			{
				BSTNode* temp = p->left;
				delete p;
				return temp;
			}
			BSTNode* succ = getMin(p->right);
			p->key = succ->key;
			p->right = remove(p->right, succ->key);
		}
		return p;
	}

	void inOrder(BSTNode* p) const
	{
		if (!p)
		{
			return;
		}
		inOrder(p->left);
		std::cout << p->key << " ";
		inOrder(p->right);
	}

	void destroy(BSTNode* p)
	{
		if (!p)
			return;
		destroy(p->left);
		destroy(p->right);
		delete p;
	}

public:
	BST() : root(nullptr) {}

	~BST()
	{
		destroy(root);
	}

	bool Search(int key) const
	{
		return search(root, key);
	}

	void Insert(int key)
	{
		root = insert(root, key);
	}

	void Remove(int key)
	{
		root = remove(root, key);
	}

	void InOrderPrint() const
	{
		inOrder(root);
		std::cout << std::endl;
	}
};

int main()
{
	BST bst;
	int arr[] = { 50, 30, 70, 20, 40, 60, 80 };
	int n = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < n; ++i)
	{
		bst.Insert(arr[i]);
	}

	std::cout << "BST中序遍历（升序）：";
	bst.InOrderPrint();

	int target = 40;
	if (bst.Search(target))
		std::cout << "找到 key = " << target << "\n";
	else
		std::cout << "未找到 key = " << target << "\n";

	std::cout << "删除 50\n";
	bst.Remove(50);
	std::cout << "删除后中序：";
	bst.InOrderPrint();

	return 0;
}

#elif 0  // AVL

#include <iostream>

class AVLTree
{
private:
	struct AVLNode
	{
		int key;
		int height;
		AVLNode* left;
		AVLNode* right;
		AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
	};

	AVLNode* root;

	int getHeight(AVLNode* p) const
	{
		if (!p)
			return 0;
		return p->height;
	}

	void updateHeight(AVLNode* p)
	{
		p->height = 1 + std::max(getHeight(p->left), getHeight(p->right));
	}

	int balanceFactor(AVLNode* p) const
	{
		if (!p)
			return 0;
		return getHeight(p->left) - getHeight(p->right);
	}

	AVLNode* rightRotate(AVLNode* y)
	{
		AVLNode* x = y->left;
		AVLNode* T3 = x->right;

		x->right = y;
		y->left = T3;
		updateHeight(y);
		updateHeight(x);
		return x;
	}

	AVLNode* leftRotate(AVLNode* y)
	{
		AVLNode* x = y->right;
		AVLNode* T3 = x->left;

		x->left = y;
		y->right = T3;
		updateHeight(y);
		updateHeight(x);
		return x;
	}

	AVLNode* insert(AVLNode* p, int key)
	{
		if (!p)
			return new AVLNode(key);
		if (key < p->key)
			p->left = insert(p->left, key);
		else if (key > p->key)
			p->right = insert(p->right, key);
		else
			return p;

		updateHeight(p);

		int bf = balanceFactor(p);
		// LL
		if (bf > 1 && key < p->left->key)
			return rightRotate(p);
		// RR
		if (bf < -1 && key > p->right->key)
			return leftRotate(p);
		// LR
		if (bf > 1 && key > p->left->key)
		{
			p->left = leftRotate(p->left);
			return rightRotate(p);
		}
		// RL
		if (bf < -1 && key < p->right->key)
		{
			p->right = rightRotate(p->right);
			return leftRotate(p);
		}

		return p;
	}

	AVLNode* getMin(AVLNode* p) const
	{
		while (p->left)
		{
			p = p->left;
		}
		return p;
	}

	AVLNode* remove(AVLNode* p, int key)
	{
		if (!p)
			return nullptr;
		if (key < p->key)
			p->left = remove(p->left, key);
		else if (key > p->key)
			p->right = remove(p->right, key);
		else
		{
			if (!p->left)
			{
				AVLNode* temp = p->right;
				delete p;
				return temp;
			}
			if (!p->right)
			{
				AVLNode* temp = p->left;
				delete p;
				return temp;
			}
			AVLNode* succ = getMin(p->right);
			p->key = succ->key;
			p->right = remove(p->right, succ->key);
		}
		if (!p)
			return nullptr;
		updateHeight(p);

		int bf = balanceFactor(p);
		// LL
		if (bf > 1 && balanceFactor(p->left) >= 0)
			return rightRotate(p);
		// LR
		if (bf > 1 && balanceFactor(p->left) < 0)
		{
			p->left = leftRotate(p->left);
			return rightRotate(p);
		}
		// RR
		if (bf < -1 && balanceFactor(p->right) <= 0)
			return leftRotate(p);
		// RL
		if (bf < -1 && balanceFactor(p->right) > 0)
		{
			p->right = rightRotate(p->right);
			return leftRotate(p);
		}
		return p;
	}

	AVLNode* search(AVLNode* p, int key) const
	{
		if (!p || p->key == key)
			return p;
		if (key < p->key)
			return search(p->left, key);
		else
			return search(p->right, key);
	}

	void inOrder(AVLNode* p) const
	{
		if (p == nullptr)
			return;
		inOrder(p->left);
		std::cout << p->key << " ";
		inOrder(p->right);
	}

	void freeTree(AVLNode* p)
	{
		if (p == nullptr)
			return;
		freeTree(p->left);
		freeTree(p->right);
		delete p;
	}

public:
	AVLTree() : root(nullptr) {}

	~AVLTree()
	{
		freeTree(root);
	}

	bool Search(int key) const
	{
		return search(root, key);
	}

	void Insert(int key)
	{
		root = insert(root, key);
	}

	void Remove(int key)
	{
		root = remove(root, key);
	}

	void InOrderPrint() const
	{
		inOrder(root);
		std::cout << "\n";
	}
};

int main()
{
	AVLTree avl;
	int arr[] = { 50, 30, 70, 20, 40, 60, 80 };
	int n = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < n; ++i)
	{
		avl.Insert(arr[i]);
	}

	std::cout << "AVL中序遍历（升序）：";
	avl.InOrderPrint();

	int target = 40;
	if (avl.Search(target))
		std::cout << "找到 key = " << target << "\n";
	else
		std::cout << "未找到 key = " << target << "\n";

	std::cout << "删除 50\n";
	avl.Remove(50);
	std::cout << "删除后中序：";
	avl.InOrderPrint();

	// 测试容易退化的序列，AVL会自动平衡
	AVLTree avl2;
	for (int i = 1; i <= 7; ++i)
	{
		avl2.Insert(i);
	}
	std::cout << "连续插入1~7，AVL中序：";
	avl2.InOrderPrint();

	return 0;
}

#elif 0 // 哈希表 -- 链地址法

#include <iostream>
#include <vector>
#include <list>
#include <array>

class HashTable
{
private:
	std::vector<std::list<int>> table;
	int tableSize;

private:
	int hashFunc(int key) const
	{
		return key % tableSize;
	}

public:
	HashTable(int size = 13)
		: tableSize(size)
	{
		table.resize(tableSize);
	}

	void insert(int key)
	{
		int idx = hashFunc(key);
		for (int val : table[idx])
		{
			if (val == key)
				return;
		}
		table[idx].emplace_back(key);
	}

	bool find(int key) const
	{
		int idx = hashFunc(key);
		for (int val : table[idx])
		{
			if (val == key)
				return true;
		}
		return false;
	}

	void remove(int key)
	{
		int idx = hashFunc(key);
		auto& lst = table[idx];
		for (auto it = lst.begin();it != lst.end();it++)
		{
			if (*it == key)
			{
				lst.erase(it);
				return;
			}
		}
	}

	void print() const
	{
		for (int i = 0; i < tableSize; i++)
		{
			std::cout << "[" << i << "]: ";
			for (auto v : table[i])
			{
				std::cout << v << "->";
			}
			std::cout << "nullptr\n";
		}
	}
};

int main()
{
	HashTable ht(7);
	std::array<int, 6> arr = { 12, 23, 45, 14, 7, 21 };
	for (int x : arr)
	{
		ht.insert(x);
	}

	ht.print();
	std::cout << (ht.find(23) ? "found 23" : "not found") << std::endl;
	ht.remove(23);
	ht.print();
	return 0;
}
#elif 0 // 哈希表 -- 开地址法.线性探测

#include <iostream>
#include <vector>

class HashTableLinear
{
private:
	enum State
	{
		EMPTY, EXIST, DELETE
	};

	struct HashElem
	{
		int key;
		State state;

		HashElem() : key(0),state(EMPTY) {}
	};

	std::vector<HashElem> data;
	int tableLen;

	int hashFunc(int k) const
	{
		return k % tableLen;
	}

public:
	HashTableLinear(int len = 11)
		:tableLen(len)
	{
		data.resize(tableLen);
	}

	bool insert(int key)
	{
		int pos = hashFunc(key);
		for (int i = 0; i < tableLen; i++)
		{
			int cur = (pos + i) % tableLen;
			if (data[cur].state == EMPTY || data[cur].state == DELETE)
			{
				data[cur].key = key;
				data[cur].state = EXIST;
				return true;
			}
			if (data[cur].state == EXIST && data[cur].key == key)
			{
				return true;
			}
		}
		return false;
	}

	int search(int key) const
	{
		int pos = hashFunc(key);
		for (int i = 0; i < tableLen; i++)
		{
			int cur = (pos + i) % tableLen;
			if (data[cur].state == EMPTY)
			{
				return -1;
			}
			if (data[cur].state == EXIST && data[cur].key == key)
			{
				return cur;
			}
		}
		return -1;
	}

	bool remove(int key)
	{
		int idx = search(key);
		if (idx == -1)
		{
			return false;
		}
		data[idx].state = DELETE;
		return true;
	}

	void print() const
	{
		for (int i = 0; i < tableLen; i++)
		{
			std::cout << "[" << i << "] ";
			if (data[i].state == EMPTY)
			{
				std::cout << "EMPTY";
			}
			else if (data[i].state == DELETE)
			{
				std::cout << "DELETE: " << data[i].key;
			}
			else
			{
				std::cout << data[i].key;
			}
			std::cout << std::endl;
		}
	}
};

int main()
{
	HashTableLinear ht(11);
	int arr[] = { 14, 23, 39, 9, 25 };
	for (int x : arr)
	{
		ht.insert(x);
	}
	ht.print();

	std::cout << "\nsearch 23: " << ht.search(23) << "\n";
	ht.remove(23);
	std::cout << "\nafter delete 23:\n";
	ht.print();

	return 0;
}
#endif