#include <stdio.h>
#include <string.h>
#include <ctype.h>


int isPalindrome(const char* string, int start_index, int end_index) {
    if (start_index >= end_index) return 1;

    if (!(isalpha(string[start_index]) || isalpha(string[end_index]))) {
        return isPalindrome(string, start_index+1, end_index-1);
    }
    else if (!isalpha(string[start_index])) {
        return isPalindrome(string, start_index+1, end_index);
    }   
    else if (!isalpha(string[end_index])) {
        return isPalindrome(string, start_index, end_index-1);
    }
    if (tolower(string[start_index]) != tolower(string[end_index])) {
        return 0;
    }
    return isPalindrome(string, start_index + 1, end_index - 1);
}

int main() {
    char word[100];
    int length, result;

    printf("Enter a word: ");
    fgets(word, 100, stdin);
    word[strcspn(word, "\n")] = '\0';

    length = strlen(word);
    result = isPalindrome(word, 0, length - 1);

    if (result)
        printf("Palindrome\n");
    else
        printf("Not a palindrome\n");
}
