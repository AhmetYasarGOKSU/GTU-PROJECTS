#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *my_realloc(int *ptr, size_t old_size, size_t new_size) {
    if (ptr == NULL) {
        return malloc(new_size);
    }

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    void* new_ptr;
    new_ptr = malloc(new_size);
    for (size_t i = 0; i < old_size/4; i++) {
        ((int*)new_ptr)[i] = ptr[i];
    }

    free(ptr);
    return new_ptr;
}

int main(void) {
    int i;
    int *arr = malloc(5 * sizeof *arr);
    if (!arr) return 1;
    for (i = 0; i < 5; i++) arr[i] = i;

    arr = my_realloc(arr, 5 * sizeof *arr, 10 * sizeof *arr);
    if (!arr) return 1;
    for (i = 5; i < 10; i++) arr[i] = i;

    printf("Dizi elemanları: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    arr = my_realloc(arr, 10 * sizeof *arr, 3 * sizeof *arr);
    printf("Küçültülmüş dizi elemanları: ");
    for (i = 0; i < 3; i++) {
        printf("%d ", arr[i]);   
    }
    printf("\n");

    free(arr);
    return 0;
}

