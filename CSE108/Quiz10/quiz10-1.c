#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, money, i, j, total = 0, temp_total;
    int* p;
    printf("Please enter n: ");
    scanf("%d", &n);
    printf("Please enter money: ");
    scanf("%d", &money);

    p = (int*)malloc(sizeof(int) * n);
    
    for (i = 0; i < n; i++) {
        printf("Please enter %d. number: ", i+1);
        scanf("%d", (p+i));
    }

    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            temp_total = p[i] + p[j];

            if (temp_total <= money && temp_total > total) {
                total = temp_total;
            }
      
        }
    }
    printf("Result: %d\n", money - total);    
    free(p);
}
