#include <stdio.h>

double power(double base, int exponent) {
    if (exponent == 0 || base == 1) {
        return 1;
    }
    if (exponent > 0) {
        return (base * power(base, exponent-1));
    }
    else if (exponent < 0) {
        return (1/base)*power(base, exponent+1);
    }
}  

int main() {
    double result;
    result = power(2.0, -2);
    printf("Result: %.4lf", result);
}