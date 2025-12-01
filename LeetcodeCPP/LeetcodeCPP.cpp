#include "Array_.h"
#include "Stack_.h"
using namespace std;




int main() {
    
    Array_ array;
    StockSpanner stk;
    string s = "ckidcdnrddddddddddddddrreeeeennnnppppppppppppppccc";
    vector<int> v = { 1,4,3,7,4,5 };
    vector<vector<int>> grid = {{5,50,39,37},
                                {2,19,36,26},
                                {27,3,23,10},
                                {20,33,8,39 } };
    auto tag = array.maximumScore(v, 3);

    cout << tag;
    //for (auto i : tag)
    //{
    //    cout << i << endl;
    //}

    return 0;
}
