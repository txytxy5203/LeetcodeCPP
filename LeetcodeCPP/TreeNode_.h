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
		if (root == nullptr)
			return 0;
		int l = maxDepth(root->left);
		int r = maxDepth(root->right);
		return std::max(l, r) + 1;
	}	
};

