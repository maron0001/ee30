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
    int i, n;

    std::cin >> n;

    while (n >= 0) {
        for (i = 2; i <= n; i++)
            if (isPrime(i))
                std::cout << i << " ";

        std::cout << std::endl;
        std::cin >> n;
    }    
}
