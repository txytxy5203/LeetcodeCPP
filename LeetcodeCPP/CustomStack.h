#pragma once
#include <vector>
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