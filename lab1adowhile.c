#include <stdio.h>

int main() {
    int i;
   
    
    scanf("%d", &i);

    do{
        if(i%5==0) {
            printf("%d\n", i);
        }

        i--;

    } while (i>=0);

}