#include <stdio.h>





int digit_sum(int n) {
    int ans;
    if (n < 10) {
        return n;
    }
    else {
        ans = n % 10;
        return (ans + digit_sum(n / 10));
    }

}

int main() {
    int res;
    res = digit_sum(4876875);
    printf("%d", res);
}