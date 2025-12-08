#pragma once
#include <utility>

class TreeNode
{
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr){}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(0), left(left), right(right){}
};
class TreeNode_
{
	int maxDepth(TreeNode* root) {
		// https://leetcode.cn/problems/maximum-depth-of-binary-tree/description/
		// Recur 还是老套路哈  基础情况 -> 要信息 -> 整合
		if (root == nullptr)
			return 0;
		int l = maxDepth(root->left);
		int r = maxDepth(root->right);
		return std::max(l, r) + 1;
	}	
	bool isSameTree(TreeNode* p, TreeNode* q) {
		// https://leetcode.cn/problems/same-tree/description/
		if (p == nullptr && q == nullptr)
			return true;
		if (p == nullptr && q != nullptr || p != nullptr && q == nullptr)
			return false;
		if (p->val != q->val)
			return false;
		bool l = isSameTree(p->left, q->left);
		bool r = isSameTree(p->right, q->right);
		return l && r;
	}
};

