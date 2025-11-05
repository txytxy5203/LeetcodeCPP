#include "Array_.h"
using namespace std;




int main() {
    
    Array_ array;
    string s = "ckidcdnrddddddddddddddrreeeeennnnppppppppppppppccc";
    vector<int> v = { 2,6,13,13 };
    vector<vector<int>> grid = { {1,7,3},
                                 {9,8,2},
                                 {4,5,6}};
    auto tag = array.sortMatrix(grid);

    for (auto i : tag)
    {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }
    
    return 0;
}
