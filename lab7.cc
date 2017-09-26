#include <iostream>
#include <cmath>

double rms(int *a, int n);
double sd(int *a, int n);
double mean(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
int range(int *a, int n);

main() {
    int n, *a;

    std::cout << "N: ";
    std::cin >> n;

    while (n > 0) {
        a = new int[n];

        for (int i = 0; i < n; i++)
            std::cin >> a[i];

        std::cout << "mean: " << mean(a, n) << std::endl;
        std::cout << "max: " << max(a, n) << std::endl;
        std::cout << "min: " << min(a, n) << std::endl;
        std::cout << "range: " << range(a, n) << std::endl;
        std::cout << "rms: " << rms(a, n) << std::endl;
        std::cout << "sd: " << sd(a, n) << std::endl;

        std::cout << "N: ";
        std::cin >> n;
    }

    return 0;
}

double rms(int *a, int n) {
    int *b = new int[n];

    for (int i = 0; i < n; i++) {
        b[i] = a[i] * a[i];
    }

    return std::sqrt(mean(b, n));
}

double sd(int *a, int n) {
    int *b = new int[n];

    for (int i = 0; i < n; i++) {
        b[i] = (a[i] - mean(a, n)) * (a[i] - mean(a, n));
    }

    return std::sqrt(mean(b, n));
}

double mean(int *a, int n) {
    double avg = 0;

    for (int i = 0; i < n; i++) {
        avg += (double)a[i] / n;
    }

    return avg;
}

int max(int *a, int n) {
    int max = a[0];

    for (int i = 1; i < n; i++)
        if (max < a[i])
            max = a[i];
    
    return max;
}

int min(int *a, int n) {
    int min = a[0];

    for (int i = 1; i < n; i++)
        if (min > a[i])
            min = a[i];
    
    return min;
}

int range(int *a, int n) {
    return max(a, n) - min(a, n);
}
