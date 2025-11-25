#pragma once
#include <vector>
#include <stack>
using namespace std;

class CustomStack {
	vector<int> stk;
	int maxSize;
public:
    CustomStack(int maxSize) {
		this->maxSize = maxSize;
    }

    void push(int x) {
        if (stk.size() == maxSize)
            return;
		stk.push_back(x);
    }

    int pop() {
        if(stk.empty())
			return -1;
		int val = stk.back();
		stk.pop_back();
        return val;
    }

    void increment(int k, int val) {
        for (int i = 0; i < k && i < stk.size(); i++)
        {
            stk[i] += val;
        }
    }
};
class MinStack
{
    // https://leetcode.cn/problems/min-stack/description/
    // 这怎么想的到
    std::vector<int> stk, minStk;
public:
    void push(int val) {
        stk.push_back(val);
        if (minStk.empty() || val <= minStk.back())
            minStk.push_back(val);
    }
    void pop() {
        if (stk.back() == minStk.back())
            minStk.pop_back();
        stk.pop_back();
    }
    int top() {
        return stk.back();
    }
    int getMin() {
        return minStk.back();
    }
};
class StockSpanner {
public:
    stack<int> stk;
    vector<int> vec;
    StockSpanner() {

    }

    int next(int price) {
        int ans = 1;
        vec.push_back(price);
        while (!stk.empty() && vec[stk.top()] <= price)
        {
            stk.pop();
        }
        if (stk.empty())
            ans = vec.size();       // 这里很关键
        else
            ans = vec.size() - 1 - stk.top();

        stk.push(vec.size() - 1);
        return ans;
    }
};