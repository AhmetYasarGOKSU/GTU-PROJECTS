#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main() {
    char str[10];
    char str2[10];
    char str3[10];
    char fullName[30];
    fullName[0] = '\0';

    strcpy(str2, "Yasar ");


    strncpy(str, "Ahmet ", 6);
    str[6] = '\0';
    printf("%s %s\n", str, str2);

    strcpy(str3, "Goksu");

    char test_string[30];




    strcat(fullName, str);
    strcat(fullName, str2);
    strcat(fullName, str3);

    printf("%s\n", fullName);
    strncpy(test_string, &fullName[12], 5);

    test_string[5] = '\0';
    printf("Test string: %s\n", test_string);

    printf("%d\n", strcmp("Ali", "Veli"));



    char s[100];
    int day = 5, month = 6, year = 2025;

    sprintf(s, "%d/%d/%d", day, month, year);

    printf("Date: %s\n", s);

    int a, b;
    char c[30];

    sscanf("100 200 kelime", "%d %d %s", &a, &b, c);

    printf("%d %d %s\n", a, b, c);


    char result[10], s1[15] = "Jan. 30, 1996";
    strcpy(result, &s1[9]);

    printf("%s\n", result);



    char f[15] = "Yakup", m[15] = "", l[15] = "Genc";
    strcat(f, l);
    strcat(m, l);
    printf("%d %d \n", strlen(m), strlen(l));
    strncat(m, l, 5);
    printf("%s\n", m);
    printf("%d \n", strncat(m, l, 15 - strlen(m) - 1));

    /*
    char inp[30];

    gets(inp);

    printf("INP: %s\n", inp);



    fgets(inp, 80, stdin);
    printf("INP: %s\n", inp);

*/


    char* str_poi = "Hello";

    printf("%s\n", str_poi);




    char aim[15]; 

    strncpy(aim, "C Programming", sizeof(aim));
    aim[sizeof(aim)-1] = '\0';


    char first_string[] = "First String";
    char second_string[] = "Second String";

    printf("First string: %s\n", first_string);
    printf("Second string: %s\n", second_string);

    strncpy(first_string, second_string, sizeof(first_string));
    first_string[sizeof(first_string)] = '\0';
    printf("%s\n", first_string);



    char user_inp[30];

    fgets(user_inp, sizeof(user_inp), stdin);
    user_inp[strcspn(user_inp, "\n")] = '\0';
    int i = 0;

    while (user_inp[i] != '\0') {
        user_inp[i] = tolower(user_inp[i]);
        i++;
    }

    printf("Lower Case: %s\n", user_inp);
    

    char name[10] = {'A', 'h', 'm', 'e', 't'};
    printf("%s\n", name);





    
    return 0;
}