#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
int embedded_questions[150][6400] = {0};
int embedded_answers[150][6400] = {0};

void parsing(char questions[][100], char answers[][100], int *pairs_counter);
void tokenizeSentence(char *sentence, char *charset, int *charset_length);
void buildCharset(char *token, char *charset, int *charset_length);
void findMaxEncodingLength(char questions[][100], char answers[][100], int* max_encoding_length, int pairs_count);
void encodeSentence(int embedded[][6400], char data[][100], char charset[], int charset_length, int max_encoding_length, int pairs_length);
void writeToFile(int embedded_questions[][6400], int embedded_answers[][6400],int max_encoding_length, int charset_length, int pairs_count);
void writeCharsetToFile(char *charset, int charset_length);

int main() {
    char questions[500][100];
    char answers[500][100];
    char charset[256];
    int charset_length = 0, pairs_counter;
    int i;

    int max_encoding_length = 0;
    parsing(questions, answers, &pairs_counter); /* Takes the questions and answers, then add them to the arrays. Array indexes are equal. So questions and answers are paired */

    for (i = 0; i < pairs_counter; i++) {
        tokenizeSentence(answers[i], charset, &charset_length);   /* Gives sentence and tokenize its. Then send buildCharset function and add all unique characters to the charset array */
        tokenizeSentence(questions[i], charset, &charset_length);
    }
    charset[charset_length] = ' ';  /* Due to strtok tokenize sentences according to ' ' we lose space. So we add it here. */
    charset_length++;

    findMaxEncodingLength(questions, answers, &max_encoding_length, pairs_counter); /* Calculate maximum encoding length via using max_sentence_lengt * charset_length */
    max_encoding_length = max_encoding_length * charset_length;

    encodeSentence(embedded_questions, questions, charset, charset_length, max_encoding_length, pairs_counter);  /* Generating character based one hot vectors */
    encodeSentence(embedded_answers, answers, charset, charset_length, max_encoding_length, pairs_counter);

    writeCharsetToFile(charset, charset_length);
    writeToFile(embedded_questions, embedded_answers, max_encoding_length, charset_length, pairs_counter); /* Print one hot vectors to the file according to the sentences */
}

void parsing(char questions[][100], char answers[][100], int *pairs_counter){
    char temp_str[100];
    int q_index = 0, a_index = 0;
    FILE * database_file = fopen("database.txt", "r");  

    if (!database_file) {
        printf("File could not be opened!\n");
        exit(-1);
    }
    /* Pairing Questions and Answers*/
    while (fgets(temp_str, 100, database_file) != NULL) {
        temp_str[strcspn(temp_str, "\n")] = '\0';  /* Clear \n after fgets */

        while (strcmp(temp_str, "---") != 0) { /* Database.txt file has --- after question_answer pairs if we have that symbol that means get new pairs */
            if (temp_str[0] == 'Q') {   /* At starts Questions has a shape like Q: , and we use that information to find is it question or answer*/
                strcpy(questions[q_index++], &temp_str[3]);  
            } else if (temp_str[0] == 'A') { /* At starts answers has a shape like A: , and we use that information to find is it question or answer*/
                strcpy(answers[a_index++], &temp_str[3]); 
            }

            if (fgets(temp_str, 100, database_file) == NULL)
                break;

            temp_str[strcspn(temp_str, "\n")] = '\0';
        }
    }
    *pairs_counter = q_index;  /* Set how many question-answer pairs have in database.txt */
    fclose(database_file);
}

void tokenizeSentence(char *sentence, char *charset, int *charset_length) {
    char temp[100];

    strcpy(temp, sentence); /* Use temp string to tokenize it. Do not change original sentence. */

    char *token = strtok(temp, " "); /* Tokenize it according to whitespaces */
    while (token != NULL) {
        buildCharset(token, charset, charset_length); /* call buildCharset function to find unique characters in database.txt */
        token = strtok(NULL, " "); /* Takes new word after whitespace to the new whitespace. */
    }
}

void buildCharset(char *token, char *charset, int *charset_length) {
    int counter = 0, i, flag;

    while (token[counter] != '\0') {
        flag = 1;
        for (i = 0; i < *charset_length; i++) {
            if (token[counter] == charset[i]) { /* Check the character exist or not.*/
                flag = 0;
                break;
            }
        }

        if (flag) { /* If character does not exist add it to the charset. */
            charset[*charset_length] = token[counter];
            (*charset_length)++;
        }
        counter++;
    }
}

void findMaxEncodingLength(char questions[][100], char answers[][100],int* max_encoding_length, int pairs_count) {
    int i;
    int length_q, length_a;
    for (i = 0; i < pairs_count; i++) {
        length_q = strlen(questions[i]); 
        length_a = strlen(answers[i]);
        /* Find the longest sentence. Set it as max_encoding_length */
        if (length_q > length_a && length_q > *max_encoding_length) {
            *max_encoding_length = length_q;
        }
        else if (length_a > length_q && length_a > *max_encoding_length) {
            *max_encoding_length = length_a;
        }
    }
}

void encodeSentence(int embedded[][6400], char data[][100], char charset[], int charset_length, int max_encoding_length, int pairs_length) {
    int i, j, k;
    
    for (i = 0; i < pairs_length; i++) {
        char sentence[100];
        strcpy(sentence, data[i]); /* Takes sentences from questions or answers. */

        int sentence_length = strlen(sentence); /* Find length of sentence */
        int start_index = max_encoding_length - (sentence_length * charset_length); /* Find how many character should be left padded as 0. */

        for (k = 0; k < sentence_length; k++) {  /* Iterate it until sentence ending. */
            for (j = 0; j < charset_length; j++) { /* Find character's index in charset */
                if (sentence[k] == charset[j]) {
                    embedded[i][start_index + j] = 1; /* Set character's index as 1 */
                    break;
                }
            }
            start_index += charset_length; /* Update new start index. */
        }
    }
}

void writeToFile(int embedded_questions[][6400], int embedded_answers[][6400],int max_encoding_length, int charset_length, int pairs_count) {
    int i, j;
    FILE * embeddings_file;
    embeddings_file = fopen("embeddings.txt", "w");
    if (!embeddings_file) {
        printf("File could not be created.");
        exit(-1);
    }
    /* Write to the file*/
    fprintf(embeddings_file, "Metadata:\n");
    fprintf(embeddings_file, "Max encoding length: %d\n", max_encoding_length);
    fprintf(embeddings_file, "Embedding dimension: %d\n", charset_length);
    fprintf(embeddings_file, "Total pairs: %d\n", pairs_count);
    fprintf(embeddings_file, "#####\n\n");

    for (i = 0; i < pairs_count; i++) { /* Circulate all question and answer pairs */
        fprintf(embeddings_file, "Question: ");
        for (j = 0; j < max_encoding_length; j++) { /* Write to the file characters as a one-hot vectors */
            fprintf(embeddings_file, "%d", embedded_questions[i][j]);
        }
        fprintf(embeddings_file, "\n");
        fprintf(embeddings_file, "Answer: ");
        for (j = 0; j < max_encoding_length; j++) { /* Write to the file characters as a one-hot vectors */
            fprintf(embeddings_file, "%d", embedded_answers[i][j]);
        }
        fprintf(embeddings_file, "\n---\n");
    }
    fclose(embeddings_file);
}

void writeCharsetToFile(char *charset, int charset_length) {
    int i;
    FILE * charset_file;
    charset_file = fopen("charset.txt", "w");

    if (!charset_file) {
        printf("File could not be created.");
        exit(-1);
    }


    for (i = 0; i < charset_length; i++) {
        fprintf(charset_file, "%c",charset[i]);
    }

    fclose(charset_file);
}
