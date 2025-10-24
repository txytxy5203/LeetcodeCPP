#include "Array_.h"
using namespace std;




int main() {
    
    Array_ array;
    string s = "bbbbbbbbbbbbbbbbbbb";
    vector<int> v = { 5,7,7,8,8,10 };
    auto tag = array.searchRange(v, 8);
    for (int i : tag)
    {
        cout << i << endl;
    }
    return 0;
}
