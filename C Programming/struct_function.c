#include <stdio.h>

struct Point
{
    int x; 
    int y;
};


struct Point createPoint(int x, int y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;    
    /* also can use
    return (sturct Point){x, y};
    */
}


int main() {
    struct Point p1;
    p1 = createPoint(5, 6);

    printf("%d %d", p1.x, p1.y);

}