#include <stdio.h>
#include <ctype.h>
int countChar(const char *str, char target) {
    if (*str == '\0') {
        return 0;
    }
    else if (tolower(str[0]) == tolower(target)) {
        return 1 + countChar(str+1, target);
    }
    else{
        return countChar(str+1, target);
    }
}
int main() {
    int result;
    result = countChar("HELLO CCASDDccA", 'C');
    printf("%d", result);
}