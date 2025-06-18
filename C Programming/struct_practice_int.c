#include <stdio.h>

struct Rectangle {
    int width;
    int height;
};

void resize(struct Rectangle* r, int newWidth, int newHeight) {
    (*r).height = newHeight;
    (*r).width = newWidth;
}


int main() {
    struct Rectangle r;
    r.height = 100;
    r.width = 50;

    resize(&r, 100, 50);

    printf("%d %d", r.height, r.width);
}