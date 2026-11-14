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
	void dfs(TreeNode* p, std::vector<int>& ans)
	{
		if (!p)
			return;
		ans.emplace_back(p->val);
		dfs(p->left, ans);
		dfs(p->right, ans);
	}

	std::vector<int> preorderTraversal(TreeNode* root) {
		std::vector<int> ans;
		dfs(root, ans);
		return ans;
	}
};

class Solution2 {
public:
	
	std::vector<int> preorderTraversal(TreeNode* root) {
		std::vector<int> ans;
		std::stack<TreeNode*> st;
		TreeNode* p = root;
		if (!root)
			return ans;
		while (p || !st.empty())
		{
			while (p)
			{
				st.push(p);
				ans.emplace_back(p->val);
				p = p->left;
			}
			p = st.top();
			st.pop();
			p = p->right;
		}
		return ans;
	}
};