#include <stdio.h>

int main() {
    int i;
    int x=0;

    scanf("%d", &i);

    while (x<=i) {
        if (x%2==0) {
            printf("%d\n",x);
        }
        x++;
    }
}
/* int main() {

    int i;
    int x=0;
    scanf("%d", &i);

    while (i>x) {
        if(i%2==0){
            printf("%d\n",i);
        }
        i--;
    }

} */