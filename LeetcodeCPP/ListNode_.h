#pragma once
#include <vector>
#include <stack>
#include <set>
#include <unordered_set>

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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // https://leetcode.cn/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/description/ 

        int i = 0;
        int lastVal = head->val;
        int last = 0;
        int minAns = INT32_MAX;
        int first = 0;
        int end = 0;
        while (head != NULL)
        {
            if (i == 0)
            {
                i++;
            }
            if (head->next != nullptr)
            {
                if (lastVal > head->val && head->next->val > head->val       // 极小值
                    || lastVal < head->val && head->next->val < head->val)   // 极大值
                {
                    if (first == 0)     // first只能修改一次  好方法
                    {
                        first = i;
                        last = i;
                        end = i;
                    }
                    else
                    {
                        minAns = min(minAns, i - last);
                        last = i;
                        end = i;
                    }                  
                }
            }
            lastVal = head->val;
            head = head->next;
            i++;
        }
        if (first == end)
            return { -1, -1 };
        return { minAns, end - first};
    }
    ListNode* mergeNodes(ListNode* head) {
        // https://leetcode.cn/problems/merge-nodes-in-between-zeros/description/
        if (head == nullptr)
            return nullptr;
        ListNode* dummy = new ListNode(0);      // 哨兵节点
        ListNode* curr = dummy; 
        int sum = 0;
        head = head->next;
        while (head != nullptr)
        {
            if (head->val == 0) {
                curr->next = new ListNode(sum);
                sum = 0;
                curr = curr->next;
            }
            else {
                sum += head->val;
            }
            head = head->next;     
        }
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    ListNode* removeElements(ListNode* head, int val) {
        // https://leetcode.cn/problems/remove-linked-list-elements/description/
        // 链表的题目就认真一些  指针的方向弄清楚 再来个dummy就ok了
        ListNode* dummy = new ListNode(0);
        ListNode* last = dummy;
        dummy->next = head;
        while (head != nullptr)
        {
            if (head->val == val) {
                last->next = head->next;
                head = head->next;
            }
            else {
                last = head;
                head = head->next;
            }
        }
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        // https://leetcode.cn/problems/delete-nodes-from-linked-list-present-in-array/description/
        unordered_set<int> record(nums.begin(), nums.end());      // 直接在构造函数里面生成
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* last = dummy;
        while (head != nullptr){
            if (record.count(head->val) == 0) {
                last = head;
            }
            else {
                last->next = head->next;
            }
            head = head->next;
        }
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};
