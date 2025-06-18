#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PI 3.14


typedef enum {CIRCLE, RECTANGLE} Shapetype;

typedef struct {
    double radius;
} circle;

typedef struct {
    double width, height;
} rectangle;

typedef union 
{
    circle Circle;
    rectangle Rectangle;
} Shapedata;

double calculateCircleArea(double r) {
    return PI*r*r;

}
double calculateRecantgleArea(double width, double height) {
    return height*width;
}


int main() {
    int n = 5, i, rndm;
    Shapetype *types;
    Shapedata *datas;
    srand(time(NULL));
    datas = (Shapedata*)malloc(sizeof(Shapedata)*n);
    types = (Shapetype*)malloc(sizeof(Shapetype)*n);
    
    for (i = 0; i < n; i++) {
        rndm = rand() % 2;
        if (rndm) {
            types[i] = RECTANGLE;
            datas[i].Rectangle.width = rand() % 25 + 1;
            datas[i].Rectangle.height = rand() % 25 + 1;
        }
        else {
            types[i] = CIRCLE; 
            datas[i].Circle.radius = rand() % 25 + 1;
        } 
    }   

    for (i = 0; i < n; i++) {
        if (types[i] == CIRCLE) {
            printf("%d. %d Sekil (r= %.2lf): ", i+1, types[i], datas[i].Circle.radius);
            printf("%.2lf\n",calculateCircleArea(datas[i].Circle.radius));

        } else {
            printf("%d. %d Sekil : (width= %.2lf height= %.2lf)", i+1, types[i], datas[i].Rectangle.width, datas[i].Rectangle.height);
            printf("%.2lf\n",calculateRecantgleArea(datas[i].Rectangle.width, datas[i].Rectangle.height));
        }
    }

    

    return 0;
}