#include <stdio.h>

int binominalCoeff(int n, int k);
int factorial(int n);

int main() {
        int row;
        printf("Please enter a row number: ");
        scanf("%d", &row);
        row = row - 1;
        int i, column, a, j;
        column = 1;

        for (i = 0; i <= row; i++) {
                for (j = row-i; j > 0; j--){
                        printf(" ");
                }
                a = binominalCoeff(i, column);
                column += 1;
                
        }
} 

int factorial(int n) {
        int total = 1;
        int i;
        if (n == 0 || n == 1)return 1;
        
        for (i = 2; i <= n; i++) {
                total *= i;
        
        }
        return total;
}

int binominalCoeff(int n, int k) {
        int i;
        int result, fact_n, fact_k, fact_n_k;
        fact_n = factorial(n);
        int j;

        for (i = 0; i < k; i++) {
                fact_k = factorial(i);

                fact_n_k = factorial(n-i);

                result = fact_n / (fact_k * fact_n_k);
                
                printf("%d ", result);

        }
        
        printf("\n");
        return result;


}
