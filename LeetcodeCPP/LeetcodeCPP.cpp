#include "Array_.h"
#include "Stack_.h"
#include "ListNode_.h"
#include "Recur_.h"
#include <iostream>
using namespace std;




int main() {
    
    Array_ array;
    StockSpanner stk;
    ListNode_ listNode;
    Recur_ recur;
    string s = "bcabc";
    vector<int> v = { 71,18,52,29,55,73,24,42,66,8,80,2 };
    vector<vector<int>> grid = {{5,50,39,37},
                                {2,19,36,26},
                                {27,3,23,10},
                                {20,33,8,39 } };
    auto a = recur.letterCombinations("23");
    for (auto str : a) {
        cout << str << endl;
    }
    return 0;
}
