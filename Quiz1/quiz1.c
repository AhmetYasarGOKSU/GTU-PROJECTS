#include <stdio.h>


int main(){
    int a, b, c;
    printf("Please enter sides of triangle (a, b, c): ");
    scanf("%d %d %d", &a, &b, &c);

    if (a <= 0 || b <= 0 || c <= 0) {
      printf("Invalid Triangle\n");
      return 0;
    }
    
    if ((a + b) <= c) {
      printf("Invalid Triangle\n");
      return 0;
    }
    else {
      if ((b + c) <= a) {
        printf("Invalid Triangle\n");
      return 0;
      }
      else {
          if ((a + c) <= b) {
              printf("Invalid Triangle\n");
              return 0;
          
          } 
          else {
              printf("Valid Triangle\n");
              return 1;
    
          }
      }
  }
}
