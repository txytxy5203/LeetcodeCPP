#pragma once
#include <vector>
#include <string>
#include <map>
#include <algorithm>
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
};

