#include <iostream>

using namespace std;

void swap(float a[], float b[], int len) {
    float tmp;
    int i;
    
    for (i = 0; i < len; i++) {
        tmp=a[i];
        a[i]=b[i];
        b[i]=tmp;
    }
    
}

int main() {
    int i;
    float a[5] = {6,4,3,2,3};
    float b[5] = {2,9,3,6,7};
    
    swap(a,b,5);
    
    return 0;
}
