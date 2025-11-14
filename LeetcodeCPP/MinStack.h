#pragma once
#include <vector>
#include <list>
using namespace std;

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