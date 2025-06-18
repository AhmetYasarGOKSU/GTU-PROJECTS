#include <stdio.h>
#include <math.h>


void applyFunction(int array[], double (*apply)())
{
    apply();
}

double findMean(int array[]);
double findRepetations(int array[]);
double countEvens(int array[]);
double calculateStd(int array[]);


int main() {
    int arr[10];
    int i;
    for (i = 0; i < 10; i++) {
        printf("Please type a %d. number of array: ", i+1);
        scanf("%d", &arr[i]);
    }

    applyFunction(arr, findMean);
    applyFunction(arr, countEvens);
    applyFunction(arr, findRepetations);
    applyFunction(arr, calculateStd);
    return 0;

}

double findMean(int array[]) {
    int i;
    double sum = 0;
    for (i = 0; i < 10; i++) {
        sum += array[i];
    
    }
    
    printf("Mean of the elements in array is: %.2lf\n", sum / 10);
    return (sum / 10.0);
}

double findRepetations(int array[]) {
    int i, counter = 0;
    
    for (i = 1; i < 10; i++) {
        if (array[i] == array[i-1]) {
            if (i >= 2) {
                if (array[i] != array[i-2]) {
                    counter++;
                }
            } else if (i < 2) counter++;
            
        }
    }
    printf("Repetatation is: %d\n", counter);
    
    return (double)counter;
}

double countEvens(int array[]) {
    int i, even_counter = 0;
    
    for (i = 0; i < 10; i++) {
        if (array[i] % 2 == 0) {
            even_counter++;
        }
    }

    printf("Even number count in array is: %d\n", even_counter);
    
    return (double)even_counter;
}

double calculateStd(int array[]) {
    int i;
    double sum = 0, mean, std, sum_std = 0;
    for (i = 0; i < 10; i++) {
        sum += array[i];
    
    }
    mean = sum / 10.0;

    for (i = 0; i < 10; i++) {
        sum_std += ((double)array[i] - mean) * ((double)array[i] - mean);
    
    }

    std = sqrt((0.1) * sum_std);

    printf("Standart Deviation: %lf\n", std);
    
    return std;
}
