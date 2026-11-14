#if 0 //双亲表示法

#include <iostream>

class PTree
{
public:
	static constexpr int MAXSiZE = 100;

private:
	struct PTNode
	{
		int data;
		int parent;
	};

	PTNode nodes[MAXSiZE];
	int n;

public:
	PTree() : n(0) {}

	// the parentIdx of root node is -1
	bool AddNode(int val, int parentIdx)
	{
		if (n >= MAXSiZE)
			return false;

		nodes[n].data = val;
		nodes[n].parent = parentIdx;
		n++;
		return true;
	}

	bool IsEmpty() const
	{
		return n == 0;
	}

	bool GetElem(int i, int& e) const
	{
		if (i < 0 || i >= n)
			return false;
		e = nodes[i].data;
		return true;
	}

	int GetParent(int i) const
	{
		if (i < 0 || i >= n)
			return -2;
		return nodes[i].parent;
	}

	void PrintTree() const
	{
		std::cout << "idx/tdata/tparent\n";
		for (int i = 0; i < n; i++)
		{
			std::cout << i << '\t' << nodes[i].data << '\t' << nodes[i].parent << std::endl;
		}
	}
};

int main()
{
	PTree pt;
	pt.AddNode(1, -1);
	pt.AddNode(2, 0);
	pt.AddNode(3, 0);
	pt.AddNode(4, 1);

	std::cout << "====child tree====\n";
	pt.PrintTree();
	int e;
	pt.GetElem(2, e);
	std::cout << "data of index 2: " << e << std::endl;
	std::cout << "parent index of index 2: " << pt.GetParent(2) << std::endl;
}

#elif 0 // 孩子表示法

#include <iostream>

class CTree
{
public:
	static constexpr int MAXSIZE = 100;

private:
	struct CNode
	{
		int cIdx;
		CNode* next;
		CNode(int idx) :cIdx(idx), next(nullptr) {}
	};

	struct CTNode
	{
		int data;
		CNode* firstC;
	};

	CTNode nodes[MAXSIZE];
	int n;

	void ClearChildList(CNode* p)
	{
		CNode* q;
		while (p)
		{
			q = p;
			p = p->next;
			delete q;
		}
	}

public:
	CTree()
		:n(0)
	{
		for (int i = 0; i < MAXSIZE; i++)
		{
			nodes[i].firstC = nullptr;
		}
	}

	~CTree()
	{
		for (int i = 0; i < n; i++)
		{
			ClearChildList(nodes[i].firstC);
		}
	}

	bool IsEmpty() const
	{
		return n == 0;
	}

	bool AddNode(int val)
	{
		if (n >= MAXSIZE)
			return false;
		nodes[n].data = val;
		nodes[n].firstC = nullptr;
		n++;
		return true;
	}

	void AddChild(int parentIdx, int childIdx)
	{
		CNode* newNode = new CNode(childIdx);
		newNode->next = nodes[parentIdx].firstC;
		nodes[parentIdx].firstC = newNode;
	}

	void PrintTree() const
	{
		std::cout << "====child sibling tree====\n";
		for (int i = 0; i < n; i++)
		{
			std::cout << nodes[i].data << " : ";
			CNode* p = nodes[i].firstC;
			while (p)
			{
				std::cout << nodes[p->cIdx].data << " ";
				p = p->next;
			}
			std::cout << std::endl;
		}
	}
};

int main()
{
	CTree ct;
	ct.AddNode(1);
	ct.AddNode(2);
	ct.AddNode(3);
	ct.AddNode(4);
	ct.AddChild(0, 1);
	ct.AddChild(0, 2);
	ct.AddChild(1, 3);
	ct.PrintTree();
}

#elif 0 //孩子兄弟表示法

#include<iostream>

class CSTree
{
private:
	struct CSNode
	{
		int data;
		CSNode* firstChild;
		CSNode* rightSibling;
		CSNode(int val) : data(val), firstChild(nullptr), rightSibling(nullptr) {}
	};

	CSNode* root;

	void Destroy(CSNode* p)
	{
		if (!p)
			return;
		Destroy(p->firstChild);
		Destroy(p->rightSibling);
		delete p;
	}

	void PreOrder(CSNode* p)
	{
		if (!p)
			return;
		std::cout << p->data << " ";
		PreOrder(p->firstChild);
		PreOrder(p->rightSibling);
	}

	void PostOrder(CSNode* p)
	{
		if (!p)
			return;
		PostOrder(p->firstChild);
		std::cout << p->data << " ";
		PostOrder(p->rightSibling);
	}

	CSNode* FindNode(CSNode* p, int target) const
	{
		if (!p)
			return nullptr;
		if (p->data == target)
			return p;
		CSNode* res = FindNode(p->firstChild, target);
		if (res != nullptr)
			return res;
		return FindNode(p->rightSibling, target);
	}

	int GetDepth(CSNode* p)
	{
		if (!p)
			return 0;
		int childDepth = GetDepth(p->firstChild);
		int sibDepth = GetDepth(p->rightSibling);
		return (childDepth + 1 > sibDepth ? childDepth + 1 : sibDepth);
	}

public:
	CSTree() :root(nullptr) {}

	~CSTree()
	{
		Destroy(root);
	}

	bool IsEmpty() const
	{
		return !root;
	}

	void SetRoot(CSNode* p)
	{
		root = p;
	}

	void PreOrderTravers()
	{
		std::cout << "\n====先根遍历====\n";
		PreOrder(root);
		std::cout << std::endl;
	}

	void PostOrderTravers()
	{
		std::cout << "\n====后根遍历====\n";
		PostOrder(root);
		std::cout << std::endl;
	}

	CSNode* FindNode(int target) const
	{
		return FindNode(root, target);
	}

	int GetTreeDepth()
	{
		return GetDepth(root);
	}

	bool AddChild(int parentVal, int childVal)
	{
		CSNode* parent = FindNode(root, parentVal);
		if (parent == nullptr)
			return false;
		CSNode* newNode = new CSNode(childVal);
		if (parent->firstChild == nullptr)
			parent->firstChild = newNode;
		else
		{
			CSNode* p = parent->firstChild;
			while (p->rightSibling)
			{
				p = p->rightSibling;
			}
			p->rightSibling = newNode;
		}
		return true;
	}

	bool CreatRoot(int val)
	{
		if (root)
			return false;
		root = new CSNode(val);
		return true;
	}
};

int main()
{
	CSTree tree;
	tree.CreatRoot(1);
	tree.AddChild(1, 2);
	tree.AddChild(1, 3);
	tree.AddChild(1, 4);
	tree.AddChild(2, 5);
	tree.AddChild(2, 6);

	tree.PreOrderTravers();
	tree.PostOrderTravers();

	std::cout << "树深度 = " << tree.GetTreeDepth() << "\n";

	int target = 5;
	if (tree.FindNode(target))
		std::cout << "找到结点 " << target << "\n";
	else
		std::cout << "未找到结点 " << target << "\n";
	return 0;
}

#elif 0 //二叉树的顺序存储

#include <iostream>
#include <array>


class SqBiTree
{
private:
	static constexpr int MAXSIZE = 100;
	std::array<int, MAXSIZE> data;
	int length;

public:
	SqBiTree()
	{
		length = 0;
		data.fill(-1);
	}

	bool Create(int arr[], int n)
	{
		if (n >= MAXSIZE)
			return false;
		length = n;
		for (int i = 1; i <= n; i++)
		{
			data[i] = arr[i - 1];
		}
		return true;
	}

	void LevelOrder()
	{
		for (int i = 1; i <= length; i++)
		{
			if (data[i] != -1)
				std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}

	void PreOrder(int i)
	{
		if (i > length || data[i] == -1)
			return;
		std::cout << data[i] << " ";
		PreOrder(2 * i);
		PreOrder(2 * i + 1);
	}

	void InOrder(int i)
	{
		if (i > length || data[i] == -1)
			return;
		InOrder(2 * i);
		std::cout << data[i] << " ";
		InOrder(2 * i + 1);
	}

	void PostOrder(int i)
	{
		if (i > length || data[i] == -1)
			return;
		PostOrder(2 * i);
		PostOrder(2 * i + 1);
		std::cout << data[i] << " ";
	}

	void PreOrderTraverse()
	{
		PreOrder(1);
		std::cout << std::endl;
	}

	void InOrderTraverse()
	{
		InOrder(1);
		std::cout << std::endl;
	}

	void PostOrderTraverse()
	{
		PostOrder(1);
		std::cout << std::endl;
	}

	int GetDepth(int i)
	{
		if (i > length || data[i] == -1)
			return 0;
		int l = GetDepth(2 * i);
		int r = GetDepth(2 * i + 1);
		return (l > r ? l : r) + 1;
	}

	int GetTreeDepth()
	{
		return GetDepth(1);
	}
};

int main()
{
	int arr[] = { 1,2,3,4,5,-1,-1 };
	SqBiTree t;
	t.Create(arr, 7);
	std::cout << "层序遍历: ";
	t.LevelOrder();
	std::cout << "先序遍历: ";
	t.PreOrderTraverse();
	std::cout << "中序遍历: ";
	t.InOrderTraverse();
	std::cout << "后序遍历: ";
	t.PostOrderTraverse();
	std::cout << "树深度: " << t.GetTreeDepth() << "\n";
	return 0;
}

#elif 0 //二叉树的链式存储

#include <iostream>
#include <stack>
#include <queue>

class BiTree
{
private:
	struct BiNode
	{
		int data;
		BiNode* lChild;
		BiNode* rChild;
		BiNode(int val) : data(val), lChild(nullptr), rChild(nullptr) {}
	};

	BiNode* root;

private:
	void Destroy(BiNode* p)
	{
		if (!p)
			return;
		Destroy(p->lChild);
		Destroy(p->rChild);
		delete p;
	}

	void PreOrder(BiNode* p)
	{
		if (!p)
			return;
		std::cout << p->data << " ";
		PreOrder(p->lChild);
		PreOrder(p->rChild);
	}

	void InOrder(BiNode* p)
	{
		if (!p)
			return;
		InOrder(p->lChild);
		std::cout << p->data << " ";
		InOrder(p->rChild);
	}

	void PostOrder(BiNode* p)
	{
		if (!p)
			return;
		PostOrder(p->lChild);
		PostOrder(p->rChild);
		std::cout << p->data << " ";
	}

	void CreateByPre(BiNode*& p)
	{
		char ch;
		std::cin >> ch;
		if (ch == '#')
		{
			p = nullptr;
			return;
		}
		p = new BiNode(ch - '0');
		CreateByPre(p->lChild);
		CreateByPre(p->rChild);
	}

	BiNode* CopyTree(BiNode* src)
	{
		if (!src)
			return nullptr;
		BiNode* newNode = new BiNode(src->data);
		newNode->lChild = CopyTree(src->lChild);
		newNode->rChild = CopyTree(src->rChild);
		return newNode;
	}

	int GetDepth(BiNode* p)
	{
		if (!p)
			return 0;
		int lDep = GetDepth(p->lChild);
		int rDep = GetDepth(p->rChild);
		return (lDep > rDep ? lDep : rDep) + 1;
	}

	int GetNodeCount(BiNode* p)
	{
		if (!p)
			return 0;
		return GetNodeCount(p->lChild) + GetNodeCount(p->rChild) + 1;
	}

	int GetLeafCount(BiNode* p)
	{
		if (!p)
			return 0;
		if (!p->lChild && !p->rChild)
			return 1;
		return GetLeafCount(p->lChild) + GetLeafCount(p->rChild);
	}

	BiNode* InvertTree(BiNode* root)
	{
		if (!root)
			return nullptr;
		BiNode* temp = root->lChild;
		root->lChild = root->rChild;
		root->rChild = temp;
		InvertTree(root->lChild);
		InvertTree(root->rChild);
		return root;
	}

public:
	BiTree() :root(nullptr) {}

	~BiTree()
	{
		Destroy(root);
	}

	bool Create(int val)
	{
		if (root)
			return false;
		root = new BiNode(val);
		return true;
	}

	bool InsertLeft(BiNode* parent, int val)
	{
		if (!parent || parent->lChild)
			return false;
		parent->lChild = new BiNode(val);
		return true;
	}

	bool InsertRight(BiNode* parent, int val)
	{
		if (!parent || parent->rChild)
			return false;
		parent->rChild = new BiNode(val);
		return true;
	}

	BiNode* GetRoot()
	{
		return root;
	}

	void PreOrderTraverse()
	{
		PreOrder(root);
		std::cout << std::endl;
	}

	void InOrderTraverse()
	{
		InOrder(root);
		std::cout << std::endl;
	}

	void PostOrderTraverse()
	{
		PostOrder(root);
		std::cout << std::endl;
	}

	void PreOrderNonRec()
	{
		if (!root)
			return;
		std::stack<BiNode*> st;
		BiNode* p = root;
		while (p || !st.empty())
		{
			while (p)
			{
				std::cout << p->data << " ";
				st.push(p);
				p = p->lChild;
			}
			p = st.top();
			st.pop();
			p = p->rChild;
		}
		std::cout << std::endl;
	}

	void InOrderNonRec()
	{
		if (!root)
			return;
		std::stack<BiNode*> st;
		BiNode* p = root;
		while (p || !st.empty())
		{
			while (p)
			{
				st.push(p);
				p = p->lChild;
			}
			p = st.top();
			st.pop();
			std::cout << p->data << " ";
			p = p->rChild;
		}
		std::cout << std::endl;
	}

	void PostOrderNonRec()
	{
		if (!root)
			return;
		std::stack<BiNode*> st;
		BiNode* p = root;
		BiNode* lastVisit = nullptr;
		while (p || !st.empty())
		{
			while (p)
			{
				st.push(p);
				p = p->lChild;
			}
			p = st.top();
			if (!p->rChild || p->rChild == lastVisit)
			{
				std::cout << p->data << " ";
				st.pop();
				lastVisit = p;
				p = nullptr;
			}
			else
			{
				p = p->rChild;
			}
		}
		std::cout << std::endl;
	}

	void LevelOrder()
	{
		if (!root)
			return;
		std::queue<BiNode*> q;
		q.push(root);
		while (!q.empty())
		{
			BiNode* p = q.front();
			q.pop();
			std::cout << p->data << " ";
			if (p->lChild)
				q.push(p->lChild);
			if (p->rChild)
				q.push(p->rChild);
		}
		std::cout << std::endl;
	}

	void CreateByPreSeq()
	{
		CreateByPre(root);
	}

	void CopyFrom(const BiTree& src)
	{
		if (this == &src)
			return;
		Destroy(root);
		root = CopyTree(src.root);
	}

	int GetTotalNode()
	{
		return GetNodeCount(root);
	}

	int GetLeafNode()
	{
		return GetLeafCount(root);
	}

	int GetTreeDepth()
	{
		return GetDepth(root);
	}

	BiNode* Invert()
	{
		return InvertTree(root);
	}
};

int main()
{
	BiTree t;
	std::cout << "请按先序输入二叉树，#代表空节点：\n";
	std::cout << "样例输入：124##5##3##\n";
	t.CreateByPreSeq();

	std::cout << "递归先序: ";
	t.PreOrderTraverse();
	std::cout << "非递归先序: ";
	t.PreOrderNonRec();
	std::cout << "递归中序: ";
	t.InOrderTraverse();
	std::cout << "非递归中序: ";
	t.InOrderNonRec();
	std::cout << "递归后序: ";
	t.PostOrderTraverse();
	std::cout << "非递归后序: ";
	t.PostOrderNonRec();
	std::cout << "层次遍历: ";
	t.LevelOrder();

	std::cout << "树深度 = " << t.GetTreeDepth() << "\n";
	std::cout << "结点总数 = " << t.GetTotalNode() << "\n";
	std::cout << "叶子结点数 = " << t.GetLeafNode() << "\n";

	BiTree t2;
	t2.CopyFrom(t);
	std::cout << "复制后的树先序遍历：";
	t2.PreOrderTraverse();

	BiTree t3;
	t3.CopyFrom(t);
	t3.Invert();
	t3.PreOrderTraverse();
	t3.InOrderTraverse();
	return 0;
}

#elif 0 //线索二叉树

#include <iostream>

class ThreadBiTree
{
private:
	struct ThreadNode
	{
		int data;
		ThreadNode* lChild;
		ThreadNode* rChild;
		int ltag;
		int rtag;
		ThreadNode(int val) :data(val), lChild(nullptr), rChild(nullptr), ltag(0), rtag(0) {}
	};
	ThreadNode* root;
	ThreadNode* pre;

	void CreatePre(ThreadNode*& p)
	{
		char ch;
		std::cin >> ch;
		if (ch == '#')
		{
			p = nullptr;
			return;
		}
		p = new ThreadNode(ch - '0');
		CreatePre(p->lChild);
		CreatePre(p->rChild);
	}

	void InThread(ThreadNode*& p)
	{
		if (!p)
			return;
		InThread(p->lChild);
		if (!p->lChild)
		{
			p->ltag = 1;
			p->lChild = pre;
		}
		if (pre && !pre->rChild)
		{
			pre->rtag = 1;
			pre->rChild = p;
		}
		pre = p;
		InThread(p->rChild);
	}

	void Destroy(ThreadNode* p)
	{
		if (!p)
			return;
		if (p->ltag == 0)
			Destroy(p->lChild);
		if (p->rtag == 0)
			Destroy(p->rChild);
		delete p;
	}

	ThreadNode* GetFirst(ThreadNode* p)
	{
		while (p && p->ltag == 0)
		{
			p = p->lChild;
		}
		return p;
	}

	ThreadNode* GetNext(ThreadNode* p)
	{
		if (p->rtag == 1)
			return p->rChild;
		else
			return GetFirst(p->rChild);
	}

	ThreadNode* GetLast(ThreadNode* p)
	{
		while (p && p->rtag == 0)
		{
			p = p->rChild;
		}
		return p;
	}

	ThreadNode* GetPrev(ThreadNode* p)
	{
		if (p->ltag == 1)
			return p->lChild;
		else
			return GetLast(p->lChild);
	}

public:
	ThreadBiTree() :root(nullptr), pre(nullptr) {}

	~ThreadBiTree()
	{
		Destroy(root);
	}

	void CreateByPreSeq()
	{
		CreatePre(root);
	}

	void CreateInThread()
	{
		pre = nullptr;
		InThread(root);
		if (pre)
		{
			pre->rtag = 1;
			pre->rChild = nullptr;
		}
	}

	void InOrderTraverse()
	{
		ThreadNode* p = GetFirst(root);
		while (p)
		{
			std::cout << p->data << " ";
			p = GetNext(p);
		}
		std::cout << std::endl;
	}

	void ReverseInOrderTraverse()
	{
		ThreadNode* p = GetLast(root);
		while (p)
		{
			std::cout << p->data << " ";
			p = GetPrev(p);
		}
		std::cout << std::endl;
	}
};

int main()
{
	ThreadBiTree t;
	std::cout << "先序输入，#为空结点，样例：124##5##3##\n";
	t.CreateByPreSeq();
	t.CreateInThread();
	std::cout << "中序线索二叉树正序遍历：";
	t.InOrderTraverse();
	std::cout << "中序线索二叉树逆序遍历：";
	t.ReverseInOrderTraverse();
	return 0;
}

#elif 0 //HuffmanTree的顺序实现

#include <iostream>
#include <vector>
#include <string>

class HfTree
{
private:
	struct HfNode
	{
		int weight;
		int parent, lChild, rChild;

		HfNode() : weight(0), parent(-1), lChild(-1), rChild(-1) {}
		HfNode(int w) : weight(w), parent(-1), lChild(-1), rChild(-1) {}

	};
	std::vector<HfNode> nodeArr;
	int leafCnt;

	void SelectMin(int end, int& s1, int& s2)
	{
		s1 = -1;
		s2 = -1;
		for (int i = 0; i <= end; i++)
		{
			if (nodeArr[i].parent == -1)
			{
				if (s1 == -1 || nodeArr[i].weight < nodeArr[s1].weight)
				{
					s2 = s1;
					s1 = i;
				}
				else if (s2 == -1 || nodeArr[i].weight < nodeArr[s2].weight)
				{
					s2 = i;
				}
			}
		}
	}

public:
	HfTree(const std::vector<int>& w)
	{
		leafCnt = static_cast<int>(w.size());
		if (leafCnt <= 1)
			return;
		int totalNode = 2 * leafCnt - 1;
		nodeArr.resize(totalNode);
		for (int i = 0; i < leafCnt; i++)
		{
			nodeArr[i].weight = w[i];
		}
		for (int i = leafCnt; i < totalNode; i++)
		{
			int s1, s2;
			SelectMin(i - 1, s1, s2);
			nodeArr[s1].parent = i;
			nodeArr[s2].parent = i;
			nodeArr[i].lChild = s1;
			nodeArr[i].rChild = s2;
			nodeArr[i].weight = nodeArr[s1].weight + nodeArr[s2].weight;
		}
	}

	void PrintHuffCode() const
	{
		if (leafCnt <= 1)
			return;
		for (int i = 0; i < leafCnt; i++)
		{
			std::string code;
			int cur = i;
			int p = nodeArr[cur].parent;
			while (p != -1)
			{
				if (nodeArr[p].lChild == cur)
					code = "0" + code;
				else
					code = "1" + code;
				cur = p;
				p = nodeArr[cur].parent;
			}
			std::cout << "Weight: " << nodeArr[i].weight << " : " << code << std::endl;
		}
	}

	int GetWpl() const
	{
		int wpl = 0;
		for (int i = 0; i < leafCnt; i++)
		{
			int depth = 0;
			int cur = i;
			int p = nodeArr[cur].parent;
			while (p != -1)
			{
				depth++;
				cur = p;
				p = nodeArr[cur].parent;
			}
			wpl += nodeArr[i].weight * depth;
		}
		return wpl;
	}
};

int main()
{
	std::vector<int> weight = { 5, 9, 12, 13, 16, 45 };
	HfTree ht(weight);
	std::cout << "Huffman code: \n";
	ht.PrintHuffCode();
	std::cout << "WPL = " << ht.GetWpl() << std::endl;
}

#elif 0 //HuffmanTree的链式实现

#include <iostream>
#include <queue>
#include <string>
#include <vector>

class HfTree
{
private:
	struct HfNode
	{
		int weight;
		HfNode* lChild;
		HfNode* rChild;
		HfNode(int w) : weight(w), lChild(nullptr), rChild(nullptr) {}
	};
	HfNode* root;

	void Destory(HfNode*& p)
	{
		if (!p)
			return;
		Destory(p->lChild);
		Destory(p->rChild);
		delete p;
		p = nullptr;
	}

	void GetCode(HfNode* p, std::string str) const
	{
		if (!p->lChild && !p->rChild)
		{
			std::cout << "Weight: " << p->weight << " : " << str << std::endl;
			return;
		}
		GetCode(p->lChild, str + "0");
		GetCode(p->rChild, str + "1");
	}

	void CalcWpl(HfNode* p, int depth, int& wpl) const
	{
		if (!p->lChild && !p->rChild)
		{
			wpl += p->weight * depth;
			return;
		}
		CalcWpl(p->lChild, depth + 1, wpl);
		CalcWpl(p->rChild, depth + 1, wpl);
	}

public:
	HfTree(const std::vector<int>& w)
	{
		auto cmp = [](HfNode* a, HfNode* b)
			{
				return a->weight > b->weight;
			};
		std::priority_queue<HfNode*, std::vector<HfNode*>, decltype(cmp)> minHeap(cmp);
		for (int val : w)
		{
			minHeap.push(new HfNode(val));
		}
		while (minHeap.size() > 1)
		{
			HfNode* s1 = minHeap.top();
			minHeap.pop();
			HfNode* s2 = minHeap.top();
			minHeap.pop();
			HfNode* newNode = new HfNode(s1->weight + s2->weight);
			newNode->lChild = s1;
			newNode->rChild = s2;
			minHeap.push(newNode);
		}
		root = minHeap.top();
	}

	~HfTree()
	{
		Destory(root);
	}

	void PrintHfCode() const
	{
		if (!root)
			return;
		GetCode(root, "");
	}

	int GetWpl() const
	{
		int wpl = 0;
		if (!root)
			return 0;
		CalcWpl(root, 0, wpl);
		return wpl;
	}
};

int main()
{
	std::vector<int> weight = { 5, 9, 12, 13, 16, 45 };
	HfTree ht(weight);
	std::cout << "Huffman Code: \n";
	ht.PrintHfCode();
	std::cout << "WPL = " << ht.GetWpl() << std::endl;
}
#endif