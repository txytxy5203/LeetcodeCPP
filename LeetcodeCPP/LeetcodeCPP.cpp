#include "Array_.h"
using namespace std;




int main() {
    
    Array_ array;
    string s = "bbbbbbbbbbbbbbbbbbb";
    vector<int> v = { 0 };
    auto tag = array.hIndex(v);
    /*for (int i : tag)
    {
        cout << i << endl;
    }*/
    cout << tag;
    return 0;
}
