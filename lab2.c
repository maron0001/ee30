#include <stdio.h>

int main() {
    int n;
    int i;
    int list[1000];
    double sum;
    double mean;
    int max;
    int min;
    int a;

    scanf("%d", &n);    

    while (n) {
        for (i=0; i<n; i++) {
            scanf("%d", &list[i]);
        }


        for(i=0; i<n; i++){
            sum = sum + list[i];
        }

        mean = sum/n;

        printf("the mean is %lf\n", mean);

        /* max = list[0];
            for(i=1; i<n ; i++){
                if (list[i]>max) {
                    max = list[i];   
                }
            }

            printf("the max is %d\n", max);

            min = list[0];
            for (i=1; i<n; i++) {
                if(list[i]<min){
                    min = list[i];
                }
            }
            printf("the min is %d\n", min);
            */

        max = min = list[0];
        for (i=1; i<n; i++) {
            if (list[i]>max) {
                max = list[i];
            }
            if (list[i]<min) {
                min = list[i];
            }
        }
        printf("the min is %d\n", min);
        printf("the max is %d\n", max);
        printf("the range is %d\n", max-min);

        scanf("%d", &n);
    }
}