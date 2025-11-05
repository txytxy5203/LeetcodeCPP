#include "Array_.h"
using namespace std;




int main() {
    
    Array_ array;
    string s = "ckidcdnrddddddddddddddrreeeeennnnppppppppppppppccc";
    vector<int> v = { 2,6,13,13 };
    vector<vector<int>> grid = {{5,50,39,37},
                                {2,19,36,26},
                                {27,3,23,10},
                                {20,33,8,39 } };
    auto tag = array.differenceOfDistinctValues(grid);

    for (auto i : tag)
    {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }
    
    return 0;
}
