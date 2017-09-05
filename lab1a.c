#include <stdio.h>

int main() {
    int i;
    int x;

    scanf("%d", &i);

    for (x=0; x<=i; x++) {
        if (x%2==0) {
            printf("%d\n", x);
        }
    }

}