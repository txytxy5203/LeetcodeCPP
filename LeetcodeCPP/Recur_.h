#pragma once
#include <vector>
#include <string>
#include <map>
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
};

