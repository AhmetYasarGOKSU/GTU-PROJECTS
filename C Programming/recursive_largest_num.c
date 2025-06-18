#include <stdio.h>


int findLargest(int arr[], int start, int end) {
    if (start == end) {
        return arr[start];
    }

    if (arr[start] > arr[end]) {
        return findLargest(arr, start, end-1);
    }
    else {
        return findLargest(arr, start+1, end);
    }

}

int main() {
    int arr[20];
    int size;
    int largest_num;
    printf("How many number you will enter(Max-20): ");
    scanf("%d", &size);

    printf("Enter numbers:\n");
    int i;
    for (i = 0; i < size; i++) {
        printf("%d.", i+1);
        scanf("%d", &arr[i]);
    }

    largest_num = findLargest(arr, 0, size-1);

    printf("Largest number: %d\n", largest_num);
}