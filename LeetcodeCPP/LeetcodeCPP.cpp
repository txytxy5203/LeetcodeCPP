#include "Array_.h"
using namespace std;




int main() {
    
    Array_ array;
    string s = "bbbbbbbbbbbbbbbbbbb";
    vector<int> v = { 4,7,5 };
    auto tag = array.maximumCandies(v, 4);
    /*for (int i : tag)
    {
        cout << i << endl;
    }*/
    cout << tag;
    return 0;
}
