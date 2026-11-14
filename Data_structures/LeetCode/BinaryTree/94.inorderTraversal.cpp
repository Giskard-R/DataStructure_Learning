#include <iostream>
#include <vector>
#include <stack>

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0),left(nullptr),right(nullptr) {}
	TreeNode(int x) : val(x),left(nullptr),right(nullptr) {}
	TreeNode(int x,TreeNode* left,TreeNode*right) : val(x),left(left),right(right) {}
};

class Solution
{
public:
	void dfs(TreeNode* p, std::vector<int>& ans)
	{
		if (!p)
			return;
		dfs(p->left, ans);
		ans.emplace_back(p->val);
		dfs(p->right, ans);
	}

	std::vector<int> inorderTraversal(TreeNode* root)
	{
		std::vector<int> ans;
		dfs(root, ans);
		return ans;
	}
};

class Solution2
{
	std::vector<int> inorderTraversal(TreeNode* root)
	{
		std::vector<int> ans;
		std::stack<TreeNode*> st;
		TreeNode* cur = root;
		if (!root)
			return ans;
		while (cur || !st.empty())
		{
			while (cur)
			{
				st.push(cur);
				cur = cur->left;
			}
			cur = st.top();
			st.pop();
			ans.emplace_back(cur->val);
			cur = cur->right;
		}
		return ans;
	}
};