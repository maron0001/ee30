#include <iostream>

bool isPrime(int n) {
    int i;

    for (i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }

    return true;
}

main() {
    int n;

    std::cin >> n;

    while (n >= 0) {
        if (n != 0 && n != 1 && isPrime(n))
            std::cout << n << " is a prime\n";
        else
            std::cout << n << " is NOT a prime\n";

        std::cin >> n;
    }    
}
