#pragma once
#include <iostream>
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
        // 可以当成模板  dummy
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
    ListNode* removeNodes(ListNode* head) {
        // https://leetcode.cn/problems/remove-nodes-from-linked-list/description/
        // 哟 这不单调栈嘛
        // 也可以使用递归
        stack<ListNode*> stk;
        ListNode* dummy = nullptr;
        //dummy->next = head;
        while (head != nullptr)
        {
            while (!stk.empty() && stk.top()->val < head->val)
            {
                stk.pop();
            }
            stk.push(head);
            head = head->next;
        }

        while (!stk.empty())
        {
            ListNode* curr = stk.top();
            stk.pop();
            curr->next = dummy;
            dummy = curr;
        }
        return dummy;
    }
    void Recur(ListNode* head)
    {
        // 所以说 递归的本质 就是 倒着遍历从最后出发 从结果出发！！！
        // of cource 也可以正向遍历    操作和递归调个顺序就行了 666
        if (head == nullptr)
            return;
        Recur(head->next);
        cout << head->val << endl;
        return;
    }
    //ListNode* insertGreatestCommonDivisors(ListNode* head) {
    //    // https://leetcode.cn/problems/insert-greatest-common-divisors-in-linked-list/description/
    //    ListNode* curr = head;
    //    while (curr != nullptr)
    //    {
    //        if (curr->next != nullptr) {
    //            int num = gcd(curr->val, curr->next->val);
    //            ListNode* add = new ListNode(num);
    //            add->next = curr->next;
    //            curr->next = add;
    //            curr = add->next;
    //        }
    //        else {
    //            break;
    //        }
    //    }
    //    return head;
    //}
    ListNode* reverseList(ListNode* head) {
        // https://leetcode.cn/problems/reverse-linked-list/description/
        ListNode* last = nullptr;
        ListNode* next = nullptr;
        while (head != nullptr) {
            next = head->next;
            head->next = last;
            last = head;
            head = next;
        }
        return last;
    }
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // https://leetcode.cn/problems/reverse-linked-list-ii/description/
        // 这个还需要好好理解一下 多练
        if (!head || left == right) {
            return head; // 空链表或无需反转
        }

        // 创建虚拟头节点，简化操作
        ListNode dummy(0);
        dummy.next = head;

        // prev 指向待反转部分的前一个节点
        ListNode* prev = &dummy;
        for (int i = 0; i < left - 1; ++i) {
            prev = prev->next;
        }

        // curr 指向待反转部分的第一个节点
        ListNode* curr = prev->next;

        // 执行反转
        // 在每次迭代中，将 curr 的下一个节点移动到反转区域的开头（prev 的后面）
        for (int i = 0; i < right - left; ++i) {
            ListNode* next_node = curr->next;
            curr->next = next_node->next;
            next_node->next = prev->next;
            prev->next = next_node;
        }

        // dummy.next 永远指向链表的实际头节点
        return dummy.next;
    }
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        int size = 0;
        ListNode* curr = head;
        while (curr != nullptr)
        {
            size++;
            curr = curr->next;
        }
        curr = dummy;
        for (size_t i = 0; i < size - n; i++)
        {
            curr = curr->next;
        }
        curr->next = curr->next->next;
        ListNode* ans = dummy;
        delete dummy;
        return ans;
    }
    ListNode* removeNthFromEnd2(ListNode* head, int n) {
        // 前后指针
        ListNode* dummy = new ListNode(0);
        ListNode* left = dummy;
        dummy->next = head;
        int length = 1;
        while (head->next != nullptr){
            if (length < n) {
                head = head->next;
                length++;
            }
            else {
                left = left->next;
                head = head->next;
            }
        }
        left->next = left->next->next;
        ListNode* ans = dummy;
        delete dummy;           // leetcode中不要delete不然会报错
        return ans->next;
    }
    ListNode* rotateRight(ListNode* head, int k) {
        // https://leetcode.cn/problems/rotate-list/description/
        if (head == nullptr)
            return nullptr;

        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        int size = 0;
        while (head != nullptr)
        {
            size++;
            head = head->next;
        }

        k = k % size;
        if (k == 0)
            return dummy->next;
        head = dummy->next;
        int length = 1;
        ListNode* left = dummy;
        while (head->next != nullptr) {
            if (length < k) {
                length++;
            }
            else {
                left = left->next;
            }
            head = head->next;
        }
        ListNode* newHead = left->next;
        left->next = nullptr;
        head->next = dummy->next;
        return newHead;
    }
};
