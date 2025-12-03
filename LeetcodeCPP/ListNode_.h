#pragma once
#include <vector>
#include <stack>

using namespace std;

class ListNode
{
public:
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    // “冒号后面是‘成员初始化列表’，比函数体赋值更快、更安全、更简洁；
    // C++ 不是故意怪异，而是让你‘一次到位’。”
};
class ListNode_
{
public:
    vector<int> nextLargerNodes(ListNode* head) {
        // https://leetcode.cn/problems/next-greater-node-in-linked-list/description/
        stack<int> stk;
        int index = 1;
        ListNode* curr = head;
        while (curr != nullptr)
        {
            curr = curr->next;
            index++;
        }
        vector<int> ans(index, 0);
        vector<int> record;
        index = 0;
        curr = head;
        while (curr != nullptr)
        {
            record.push_back(curr->val);
            while (!stk.empty() && record[stk.top()] < curr->val)
            {
                ans[stk.top()] = curr->val;
                stk.pop();
            }
            stk.push(index);
            index++;
            curr = curr->next;
        }
        return ans;
    }
    int getDecimalValue(ListNode* head) {
        // https://leetcode.cn/problems/convert-binary-number-in-a-linked-list-to-integer/description/
        int ans = 0;
        while (head != NULL)
        {
            ans = ans*2 + head->val;
            head = head->next;
        }
        return ans;
    }
};
