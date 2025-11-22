#include "Array_.h"
#include "MinStack.h"
using namespace std;




int main() {
    
    Array_ array;
    MinStack minStack;
    string s = "ckidcdnrddddddddddddddrreeeeennnnppppppppppppppccc";
    vector<int> v = { 73,74,75,71,69,72,76,73 };
    vector<vector<int>> grid = {{5,50,39,37},
                                {2,19,36,26},
                                {27,3,23,10},
                                {20,33,8,39 } };
    //auto tag = array.buildArray(v, 9);

    //for (auto s : tag)
    //    cout << s << endl;
    /*for (auto i : tag)
    {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }*/
    //cout << minStack.index << endl;
    auto ans = array.dailyTemperatures(v);
    for (auto i : ans)
        cout << i << endl;
    return 0;
}
