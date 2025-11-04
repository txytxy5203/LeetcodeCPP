#include "Array_.h"
using namespace std;




int main() {
    
    Array_ array;
    string s = "ckidcdnrddddddddddddddrreeeeennnnppppppppppppppccc";
    vector<int> v = { 2,6,13,13 };
    auto tag = array.countPalindromicSubsequence("bbcbaba");
    /*for (int i : tag)
    {
        cout << i << endl;
    }*/
    cout << tag;
    return 0;
}
