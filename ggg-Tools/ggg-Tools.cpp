#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <map>
#include <functional>
using namespace std;
#include "FUNC.h"
int main(){
    init();
    string str;
    while (!stt) {
        getline(cin, str);
        cout << loop(str) << endl;
    }
    return 0;
}
