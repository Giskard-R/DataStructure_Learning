

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
	int maxDepth(TreeNode* root)
	{
		TreeNode* p = root;
		if (!p)
			return 0;
		int lDep = maxDepth(p->left);
		int rDep = maxDepth(p->right);
		return (lDep > rDep ? lDep : rDep) + 1;
	}
};