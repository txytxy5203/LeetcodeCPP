#include "Array_.h"
#include "Stack_.h"
using namespace std;




int main() {
    
    Array_ array;
    StockSpanner stk;
    string s = "ckidcdnrddddddddddddddrreeeeennnnppppppppppppppccc";
    vector<int> v = { 0,1,0,2,1,0,1,3,2,1,2,1 };
    vector<vector<int>> grid = {{5,50,39,37},
                                {2,19,36,26},
                                {27,3,23,10},
                                {20,33,8,39 } };
    auto tag = array.trap(v);

    //for (auto s : tag)
    //    cout << s << endl;
    /*for (auto i : tag)
    {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }*/
    cout << tag << endl;

    return 0;
}
