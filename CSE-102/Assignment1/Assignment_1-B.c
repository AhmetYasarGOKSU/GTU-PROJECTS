#include <stdio.h>

#define PI 3.14

void main() {
    float radius, area;
    
    printf("r = ");
    scanf("%f", &radius);
    
    
    if (radius <= 0) {
        printf("Radius can not be zero or negative! Please try again.");
        return;
    
    }
    
    
    area = 4*PI*radius*radius;
    printf("Area of sphere: %.2f\n", area);

}
