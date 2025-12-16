#pragma once
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

class Recur_
{
    vector<string> ans;
public:
    vector<string> letterCombinations(string digits) {
        map<char, string> m = { {'2', "abc"},{'3', "def"}, {'4', "ghi"}, 
                                {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, 
                                {'8', "tuv"}, {'9', "wxyz"} };
        letterCombinationsRecur(digits, 0, &m, "");
        return ans;
    }
    void letterCombinationsRecur(string str, int i, map<char, string>* m, string curr)
    {
        if (i == str.size()){
            ans.push_back(curr);
            return;
        }
        for (auto item : (*m)[str[i]]) {
            string nextCurr = curr + item;
            letterCombinationsRecur(str, i + 1, m, nextCurr);         
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        // https://leetcode.cn/problems/subsets/description/
        vector<vector<int>> ans;
        subsetsRecur(nums, 0, ans, vector<int>());
        return ans;
    }
    void subsetsRecur(vector<int>& nums, int i, vector<vector<int>>& ans, vector<int> curr) {
        if (i == nums.size())
        {
            ans.push_back(curr);
            return;
        }

        // 不要
        vector<int> a(curr);
        subsetsRecur(nums, i + 1, ans, a);
        // 要
        a.push_back(nums[i]);
        subsetsRecur(nums, i + 1, ans, a);
    }
    vector<vector<string>> partition(string s) {
        // https://leetcode.cn/problems/palindrome-partitioning/description/
        vector<vector<string>> ans;
        partitionRecur(s, 0, ans, "", vector<string>());
        return ans;
    }
    void partitionRecur(string& s, int i, vector<vector<string>>& ans, 
                        string curr, vector<string> currList) {
        if (i == s.size() - 1) {
            curr = curr + s[i];
            if (isPalindrome(curr)){
                currList.push_back(curr);
                ans.push_back(currList);
            }
            return;
        }

        curr += s[i];
        
        // 不分隔
        partitionRecur(s, i + 1, ans, curr, currList);

        // 分隔
        if (isPalindrome(curr)) {
            currList.push_back(curr);
            partitionRecur(s, i + 1, ans, "", currList);
        }
    }
    // 是否是回文串
    bool isPalindrome(const std::string& s) {
        return std::equal(s.begin(), s.end(), s.rbegin());
    }
    vector<vector<int>> combine(int n, int k) {
        // https://leetcode.cn/problems/combinations/description/
        // 它这种写法要学习一下
        vector<vector<int>> ans;
        vector<int> curr;
        combineRecur(n, 1, k, ans, curr);
        return ans;
    }
    void combineRecur(int n, int start, int k, vector<vector<int>>& ans, vector<int>& curr) {
        if (k == 0) {
            ans.push_back(curr);
            return;
        }

        // 剪枝优化：如果剩余数字不够组成k个数，则提前结束
        if (start > n - k + 1) {
            return;
        }

        for (int i = start; i <= n - k + 1; i++) {  // 剪枝：i <= n - k + 1
            curr.push_back(i);           // 选择当前数字
            combineRecur(n, i + 1, k - 1, ans, curr);  // 递归
            curr.pop_back();             // 回溯，撤销选择  难怪人家叫递归
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        // https://leetcode.cn/problems/combination-sum-iii/description/
        vector<vector<int>> ans;
        vector<int> curr;
        combinationSum3Recur(1, n , k, curr, ans);
        return ans;
    }
    void combinationSum3Recur(int index, int remain, int k, 
                            vector<int>& curr, vector<vector<int>>& ans) {
        if (remain == 0 && k == 0)
        {
            ans.push_back(curr);
            return;
        }

        // 剪枝
        if (k < 0)
            return;
        if (9 - index + 1 < k)
            return;

        curr.push_back(index);        // 为什么反过来就行？ 
        combinationSum3Recur(index + 1, remain - index, k - 1, curr, ans);
        curr.pop_back();
        combinationSum3Recur(index + 1, remain, k, curr, ans);
        
    }
    vector<string> generateParenthesis(int n) {
        // https://leetcode.cn/problems/generate-parentheses/description/
        vector<string> ans;
        auto valid = [&](string& str) -> bool {
            // 判断是不是有效的括号
            stack<char> stk;
            for (auto ch : str) {
                if (ch == ')') {        // 从要加入的字符分类看
                    if (!stk.empty() && stk.top() == '(')
                        stk.pop();
                    else
                        return false;
                }
                else {
                    stk.push('(');
                }
            }
            return stk.empty();
            };
        auto recur = [&](this auto&& self, string& curr, int left, int right) -> void{
            if (left == n && right == n && valid(curr)) {
                ans.push_back(curr);
                return;
            }
            
            // 剪枝
            if (left > n || right > n)
                return;

            curr.push_back('(');
            self(curr, left + 1, right);
            curr.pop_back();
            curr.push_back(')');
            self(curr, left, right + 1);
            curr.pop_back();
            };
        string curr;
        recur(curr, 0, 0);
        return ans;
    }
    vector<string> generateParenthesis2(int n) {
        // https://leetcode.cn/problems/generate-parentheses/description/
        // 优化版本  一定注重剪枝的过程 能够优化很多
        // 也就是说在有效的时候才添加
        vector<string> ans;
        string curr;

        auto recur = [&](this auto&& self, int open, int close) {
            if (curr.size() == 2 * n)
            {
                ans.push_back(curr);
                return;
            }

            // 左括号 < n 时 才可以加左括号
            if (open < n) {
                curr.push_back('(');
                self(open + 1, close);
                curr.pop_back();
            }
            // 右括号 < 左括号时 才可以加右括号
            if (close < open){
                curr.push_back(')');
                self(open, close + 1);
                curr.pop_back();
            }
            };
        recur(0,0);
        return ans;
    }
    vector<vector<int>> permute(vector<int>& nums) {
        // https://leetcode.cn/problems/permutations/description/
        vector<vector<int>> ans;
        vector<int> curr;
        int n = nums.size();
        // 创建一个布尔数组 used，大小与 nums 相同，初始值为 false
        vector<bool> used(n, false);

        // 递归函数，captures ans, curr, nums, used, n by reference
        auto recur = [&](this auto&& self) -> void {
            // 递归终止条件：当前路径的长度等于原数组长度
            if (curr.size() == n) {
                ans.push_back(curr);
                return;
            }
            // 遍历所有数字，尝试将每一个未使用的数字加入当前路径
            for (int i = 0; i < n; ++i) {
                // 剪枝：如果当前数字已被使用，则跳过
                if (used[i]) {
                    continue;
                }
                // 做选择：将数字加入当前路径，并标记为已使用
                curr.push_back(nums[i]);
                used[i] = true;
                // 递归进入下一层
                self();
                // 撤销选择（回溯）：将数字从当前路径移除，并标记为未使用
                curr.pop_back();
                used[i] = false;
            }
            };
        // 启动递归
        if (n > 0) {
            recur();
        }
        return ans;
    }
    vector<vector<string>> solveNQueens(int n) {
        // https://leetcode.cn/problems/n-queens/description/
        vector<vector<string>> ans;
        vector<string> curr;
        auto check = [&](int col, int row) {
            // 不能在同一列  不能在同一个斜线
            for (size_t i = 0; i < curr.size(); i++) {
                int q = curr[i].find('Q');
                if (curr[i][col] == 'Q' || (row - i) == abs(col - q))
                    return false;
            }
            return true;

            };
        auto recur = [&](this auto&& self, int row) {
            if (row == n )
            {
                ans.push_back(curr);
                return;
            }
            for (size_t i = 0; i < n; i++)
            {
                if (check(i, row)) {
                    string str(n, '.');
                    str[i] = 'Q';
                    curr.push_back(str);
                    self(row + 1);
                    curr.pop_back();
                }
            }
            };
        recur(0);
        return ans;
    }
};

