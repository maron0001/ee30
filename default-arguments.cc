#include <iostream>

using namespace std;

int sum(int a, int b, int c=0, int d=0) {
    return a+b+c+d;
}

int main() {
    cout << sum(3,3) << endl;
    cout << sum(1,2,3) << endl;
    cout << sum(1,2,1,2) << endl;
    
    return 0;
}
