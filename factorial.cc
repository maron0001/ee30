#include <iostream>

long long factorial(int i) {
     if (i == 1) {return 1;}
     if (i == 0) {return 1;}

     return i * factorial(i-1);
}

int main () {
    int n = -1;
    
    while (n < 0) {
        std::cout << "n: ";
        std::cin >> n;
    }
    
    std::cout << "factorial = " << factorial(n) << std::endl;
    
    return 0;
}
