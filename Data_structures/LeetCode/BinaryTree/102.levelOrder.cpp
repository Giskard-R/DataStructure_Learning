#include <iostream>
#include <vector>
#include <queue>

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
	std::vector<std::vector<int>> levelOrder(TreeNode* root) {
		std::vector<std::vector<int>> res;
		if (!root)
			return res;
		std::queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			int sz = q.size();
			std::vector<int> curLevel;
			for (int i = 0; i < sz; i++)
			{
				auto p = q.front();
				q.pop();
				curLevel.emplace_back(p->val);
				if (p->left)
					q.push(p->left);
				if (p->right)
					q.push(p->right);
			}
			res.emplace_back(curLevel);
		}
		return res;
	}
};