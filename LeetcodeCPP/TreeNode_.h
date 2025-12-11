#pragma once
#include <utility>
#include <vector>
#include <queue>
#include <deque>
#include <numeric>
using namespace std;

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
	bool isSymmetric(TreeNode* root) {
		// https://leetcode.cn/problems/symmetric-tree/description/
		// 这题和 isSameTree 一个思路 反着传子节点就行了
		if (root->left == nullptr && root->right == nullptr)
			return true;
		if (root->left == nullptr && root->right != nullptr 
		 || root->left != nullptr && root->right == nullptr)
			return false;
		
		bool ans = isSymmetricRecur(root->left, root->right);
		return ans;
	}
	bool isSymmetricRecur(TreeNode* p, TreeNode* q) {
		// https://leetcode.cn/problems/same-tree/description/
		if (p == nullptr && q == nullptr)
			return true;
		if (p == nullptr && q != nullptr || p != nullptr && q == nullptr)
			return false;
		if (p->val != q->val)
			return false;
		bool l = isSymmetricRecur(p->left, q->right);
		bool r = isSymmetricRecur(p->right, q->left);
		return l && r;
	}
	vector<int> rightSideView(TreeNode* root) {
		// https://leetcode.cn/problems/binary-tree-right-side-view/description/
		// 灵神的 遍历节点的时候带一个深度 也挺不错 要了解
		/*vector<int> ans;
		if (!root)
			return ans;
		deque<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			int size = q.size();
			for (size_t i = 0; i < size; i++)
			{
				TreeNode* curr = q.front();
				q.pop();

				if (i == size - 1)
					ans.push_back(curr->val);

				if (curr->left != nullptr)
					q.push(curr->left);
				if (curr->right != nullptr)
					q.push(curr->right);
			}
		}
		return ans;*/
	}
	bool isValidBST(TreeNode* root) {
		// https://leetcode.cn/problems/validate-binary-search-tree/description/
		// 区间的思想 ！！！
		// 所以说这题的思想是在 递 的规程中解题   而我总是喜欢在 归 的过程中解题
		// 也可以中序遍历
		return isValidBSTRecur(root, LONG_MIN, LONG_MAX);
	}
	bool isValidBSTRecur(TreeNode* node, long left, long right)
	{
		if (!node)
			return true;
		long val = node->val;
		if (val <= left || val >= right)
			return false;
		bool l = isValidBSTRecur(node->left, left, val);
		bool r = isValidBSTRecur(node->right, val, right);
		return l && r;
	}
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		// https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/
		// 太巧妙了 这个思路
		if (root == nullptr || root == p || root == q)
			return root;
		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);
		if (left != nullptr && right != nullptr)
			return root;
		return left != nullptr ? left : right;	
	}	
	TreeNode* lowestCommonAncestorSearchTree(TreeNode* root, TreeNode* p, TreeNode* q) {
		// https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
		int min = std::min(p->val, q->val);
		int max = std::max(p->val, q->val);
		return lowestCommonAncestorSearchTreeRecur(root, min, max);
	}
	TreeNode* lowestCommonAncestorSearchTreeRecur(TreeNode* root, int min, int max) {
		if (root == nullptr || root->val == min || root->val == max)
			return root;
		TreeNode* left = nullptr;
		TreeNode* right = nullptr;
		if (root->val > min)
			left = lowestCommonAncestorSearchTreeRecur(root->left, min, max);
		if (root->val < max)
			right = lowestCommonAncestorSearchTreeRecur(root->right, min, max);
		if (left != nullptr && right != nullptr)
			return root;
		return left != nullptr ? left : right;
	}
	vector<vector<int>> levelOrder(TreeNode* root) {
		// 	https://leetcode.cn/problems/binary-tree-level-order-traversal/description/
		vector<vector<int>> ans;
		if (!root)
			return ans;
		std::queue<TreeNode*> queue;
		queue.push(root);
		while (!queue.empty())
		{
			int size = queue.size();
			ans.push_back(vector<int>());			// 实际上这里和c#差不多 只不过c#有一个new关键字而已
			for (size_t i = 0; i < size; i++)
			{
				TreeNode* curr = queue.front();
				queue.pop();
				ans.back().push_back(curr->val);
				if (curr->left)
					queue.push(curr->left);
				if (curr->right)
					queue.push(curr->right);
			}
		}
		return ans;
	}
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		// https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/description/
		vector<vector<int>> ans;
		if (!root)
			return ans;
		std::deque<TreeNode*> deque;
		deque.push_back(root);
		bool reverse = true;
		while (!deque.empty())
		{
			int size = deque.size();
			ans.push_back(vector<int>());			// 实际上这里和c#差不多 只不过c#有一个new关键字而已
			for (size_t i = 0; i < size; i++)
			{
				TreeNode* curr = reverse ? deque.front() : deque.back();
				reverse ? deque.pop_front() : deque.pop_back();
				ans.back().push_back(curr->val);
				if (reverse)			// 丑陋的代码
				{
					if (curr->left)
						reverse ? deque.push_back(curr->left) : deque.push_front(curr->left);
					if (curr->right)
						reverse ? deque.push_back(curr->right) : deque.push_front(curr->right);
				}
				else
				{
					if (curr->right)
						reverse ? deque.push_back(curr->right) : deque.push_front(curr->right);
					if (curr->left)
						reverse ? deque.push_back(curr->left) : deque.push_front(curr->left);
				}
				
			}
			reverse = !reverse;
		}
		return ans;
	}
	vector<vector<int>> zigzagLevelOrder2(TreeNode* root) {
		// 直接把ans的数组reverse一下不就行了吗
		vector<vector<int>> ans;
		if (!root)
			return ans;
		std::queue<TreeNode*> q;
		q.push(root);
		bool tag = false;
		while (!q.empty())
		{
			int size = q.size();
			vector<int> arr;
			for (size_t i = 0; i < size; i++)		// 优雅的代码elegant
			{
				TreeNode* curr = q.front();
				q.pop();
				arr.push_back(curr->val);

				if (curr->left)
					q.push(curr->left);
				if (curr->right)
					q.push(curr->right);			
			}
			if (tag)
				reverse(arr.begin(), arr.end());
			ans.push_back(arr);
			tag = !tag;
		}
		return ans;
	}
	int findBottomLeftValue(TreeNode* root) {
		// https://leetcode.cn/problems/find-bottom-left-tree-value/description/

		std::queue<TreeNode*> queue;
		queue.push(root);
		vector<int> arr;
		while (!queue.empty())
		{
			int size = queue.size();
			for (size_t i = 0; i < size; i++)
			{
				TreeNode* curr = queue.front();
				queue.pop();
				arr.push_back(curr->val);
				if (curr->left)
					queue.push(curr->left);
				if (curr->right)
					queue.push(curr->right);
			}
			arr.clear();
		}
		return arr[0];
	}
};

