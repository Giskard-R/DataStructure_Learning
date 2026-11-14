#include <iostream>
#include <vector>
#include <stack>

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	void dfs(TreeNode* root, std::vector<int>& ans)
	{
		if (!root)
			return;
		TreeNode* p = root;
		dfs(p->left, ans);
		dfs(p->right, ans);
		ans.emplace_back(p->val);
	}

	std::vector<int> postorderTraversal(TreeNode* root) {
		std::vector<int> ans;
		dfs(root, ans);
		return ans;
	}
};

class Solution2 {
public:
	std::vector<int> postorderTraversal(TreeNode* root) {
		std::vector<int> ans;
		std::stack<TreeNode*> st;
		TreeNode* p = root;
		TreeNode* last = nullptr;
		while (p || !st.empty())
		{
			while (p)
			{
				st.push(p);
				p = p->left;
			}
			p = st.top();
			if (!p->right || p->right == last)
			{
				ans.emplace_back(p->val);
				st.pop();
				last = p;
				p = nullptr;
			}
			else
			{
				p = p->right;
			}
		}
		return ans;
	}
};