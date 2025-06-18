#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {rgb, bgr, gray} Color;


void readInputs(int chunk[], int line_2[], int line_3[], int line_4[], int* chunk_size, int* line_size);
void push(char stackarray[][10], char operation[], int* top);
void pop(int* top);
int max_operation(int* chunk, int* corresponding_chunk_part, int chunk_size);
int avg_operation(int* chunk, int* corresponding_chunk_part, int chunk_size);
void print_output_file(int* chunk, int* line, int chunk_size, int(*operation)(int*, int*, int), int line_size, FILE * temp_file);
void print_color_type_file(FILE * temp_file, FILE * output_file, Color mode);

int main() {
    int chunk[9], line_2[80], line_3[80], line_4[80];
    int chunk_size = 0; int line_size = 0;
    int i, j;
    char operation[10];
    readInputs(chunk, line_2, line_3, line_4, &chunk_size, &line_size);

    char stackArray[3][10];
    int top = -1;
    i = 0;
    while (i < 3) {
        printf("Please type %d. operation (avg or max): ", i+1);
        fgets(operation, sizeof(operation), stdin);
        operation[strcspn(operation, "\n")] = '\0';
        
        for (j = 0; operation[j] != '\0'; j++) {
            operation[j] = tolower(operation[j]);
        }

        if (!(strcmp(operation, "avg") == 0 || strcmp(operation, "max") == 0)) {
            printf("Invalid input. Please try again!\n");
            continue;
        } else {
            i++;
        } 
        push(stackArray, operation, &top); 
    }

    char color_input[10];
    Color mode;
    while (1) {
        printf("Please enter color mode (rgb, bgr, gray): ");
        fgets(color_input, sizeof(color_input), stdin);
        color_input[strcspn(color_input, "\n")] = '\0';
  
        for (j = 0; color_input[j]; j++)
            color_input[j] = tolower(color_input[j]);

        if (strcmp(color_input, "rgb") == 0) {
            mode = rgb;
            break;
        } else if (strcmp(color_input, "bgr") == 0) {
            mode = bgr;
            break;
        } else if (strcmp(color_input, "gray") == 0) {
            mode = gray;
            break;
        } else {
            printf("Invalid color mode. Try again.\n");
        }
    }

    FILE* temp_file = fopen("temp_output.txt", "w");
    if (!temp_file) {
        printf("ERROR! Output file could not be created.\n");
        exit(1);
    }

    int (*operations[3])(int*, int*, int);

    if (strcmp(stackArray[0], "avg") == 0) {
        operations[0] = avg_operation;
    } else {
        operations[0] = max_operation;
    }

    if (strcmp(stackArray[1], "avg") == 0) {
        operations[1] = avg_operation;
    } else {
        operations[1] = max_operation;
    }

    if (strcmp(stackArray[2], "avg") == 0) {
        operations[2] = avg_operation;
    } else {
        operations[2] = max_operation;
    }
    print_output_file(chunk, line_2, chunk_size, operations[2], line_size, temp_file); 
    print_output_file(chunk, line_3, chunk_size, operations[1], line_size, temp_file); 
    print_output_file(chunk, line_4, chunk_size, operations[0], line_size, temp_file); 
    fclose(temp_file);

    FILE * output_file;
    output_file = fopen("output.txt", "wt");
    if (!output_file) {
        printf("ERROR! Output file could not be created.\n");
        exit(1);
    }

    temp_file = fopen("temp_output.txt", "rt");
    if (!temp_file) {
        printf("ERROR! Temp file could not be readed.\n");
        exit(1);
    }

    print_color_type_file(temp_file, output_file, mode);

    fclose(temp_file);
    fclose(output_file);
    return 0;
}


void readInputs(int chunk[], int line_2[], int line_3[], int line_4[], int* chunk_size, int* line_size) {
    FILE * read_input_file;
    int i;
    read_input_file = fopen("input.txt", "r");

    if (read_input_file == NULL) {
        printf("ERROR! File could not be opened.\n");
        exit(1);
    }
    char line[300];
    i = 0;
    if(fgets(line, sizeof(line), read_input_file)) {
        char *token = strtok(line, " ");
        while (token != NULL)
        {
            chunk[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
            (*chunk_size)++;
        }
    }
    i = 0;
    if (fgets(line, sizeof(line), read_input_file)) {
        char *token = strtok(line, " ");
        while (token != NULL)
        {
            line_2[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
            (*line_size)++;
        }
    }
    i = 0;
    if (fgets(line, sizeof(line), read_input_file)) {
        char *token = strtok(line, " ");
        while (token != NULL) 
        {
            line_3[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }
    }
    i = 0;
    if (fgets(line, sizeof(line), read_input_file)) {
        char *token = strtok(line, " ");
        while (token != NULL) 
        {
            line_4[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }
    }
    fclose(read_input_file);
}

void push(char stackarray[][10], char operation[], int* top) {
    if (*top < 2) {
        (*top)++;
        strcpy(stackarray[*top], operation);
    }
}

void pop(int* top) {
    if (*top > -1) {
        (*top)--;
    }
}

int max_operation(int* chunk, int* corresponding_chunk_part, int chunk_size) {
    int i;
    int max = chunk[0] * corresponding_chunk_part[0];
    for (i = 1; i < chunk_size; i++) {
        int val = chunk[i] * corresponding_chunk_part[i];
        if (val > max) {
            max = val;
        }
    }
    return max;
}

int avg_operation(int* chunk, int* corresponding_chunk_part, int chunk_size) {
    int i;
    int sum = 0;

    for (i = 0; i < chunk_size; i++) {
        sum += chunk[i] * corresponding_chunk_part[i];
    }

    return (sum/chunk_size);

}

void print_output_file(int* chunk, int* line, int chunk_size, int(*operation)(int*, int*, int), int line_size, FILE * temp_file) {
    int i;
    for ( i = 0; i <= line_size - chunk_size; i++) {
        int result = operation(chunk, line + i, chunk_size);
        fprintf(temp_file, "%d ", result);
    }
    fprintf(temp_file, "\n");
}

void print_color_type_file(FILE * temp_file, FILE * output_file, Color mode) {
    int temp_l1_results[80], temp_l2_results[80], temp_l3_results[80];
    char temp_str[300];
    int length;
    int i;


    i = 0;
    if(fgets(temp_str, sizeof(temp_str), temp_file)) {
        char* token = strtok(temp_str, " ");
        while (token != NULL) {
            temp_l1_results[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }
    }
    length = i-1;
    i = 0;
    if (fgets(temp_str, sizeof(temp_str), temp_file)) {
        char* token = strtok(temp_str, " ");
        while (token != NULL) {
            temp_l2_results[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }
    }
    i = 0;
    if (fgets(temp_str, sizeof(temp_str), temp_file)) {
        char* token = strtok(temp_str, " ");
        while (token != NULL) {
            temp_l3_results[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }
    }
    
        switch (mode) {
            case rgb:
                for (i = 0; i < length; i++) {
                    fprintf(output_file, "[%d,%d,%d]", temp_l1_results[i], temp_l2_results[i], temp_l3_results[i]);
                    if (i != length - 1) fprintf(output_file, ",");
                }
                break;

            case bgr:
                for (i = 0; i < length; i++) {
                    fprintf(output_file, "[%d,%d,%d]", temp_l3_results[i], temp_l2_results[i], temp_l1_results[i]);
                    if (i != length - 1) fprintf(output_file, ",");
                }
                break;

            case gray:
                fprintf(output_file, "[");
                for (i = 0; i < length; i++) {
                    fprintf(output_file, "%d", temp_l1_results[i]);
                    if (i != length - 1) fprintf(output_file, ",");
                }
                fprintf(output_file, "]\n[");

                for (i = 0; i < length; i++) {
                    fprintf(output_file, "%d", temp_l2_results[i]);
                    if (i != length - 1) fprintf(output_file, ",");
                }
                fprintf(output_file, "]\n[");

                for (i = 0; i < length; i++) {
                    fprintf(output_file, "%d", temp_l3_results[i]);
                    if (i != length - 1) fprintf(output_file, ",");
                }
                fprintf(output_file, "]\n");
                break;

            default:
                printf("Invalid color mode.\n");
                break;
    }
    

    
}
