#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHARSET_LENGTH 100
#define MAX_EMBEDDING_LENGTH 8000
#define SENTENCE_LENGTH 200
#define PAIR_AMOUNT 150

typedef struct {
    int questions[MAX_EMBEDDING_LENGTH];
    int answers[MAX_EMBEDDING_LENGTH];
    int kb[MAX_EMBEDDING_LENGTH];
} QAPairs;



void getCharset(char charset[]);
void readEmbeddings(int* embedding_dim, int* max_embedding_length, int* total_pairs, QAPairs qa_pairs[]);
void generateKnowledgeBase(QAPairs qa_pairs[], int total_pairs, int max_embedding_length);
void encodeSentence(int query[], char sentence[], char charset[], int embedding_dim, int max_encoding_length, int total_pairs);
void matchingScore(int query[], QAPairs qa_pairs[], int total_pairs, int max_encoding_length,
                   int embedding_dim, int max_emb_size, char charset[]);
void decodeAnswer(int *region, char charset[], int embedding_dim, int max_encoding_length);


int main() {
    int embedding_dim, max_embedding_length, total_pairs;
    char charset[CHARSET_LENGTH], sentence[SENTENCE_LENGTH];
    int query[MAX_EMBEDDING_LENGTH] = {0}, answer_embedding[MAX_EMBEDDING_LENGTH], max_emb_size;
    getCharset(charset);
    QAPairs *qa_pairs = (QAPairs*)malloc(PAIR_AMOUNT * sizeof(*qa_pairs));

    readEmbeddings(&embedding_dim, &max_embedding_length, &total_pairs, qa_pairs);
    generateKnowledgeBase(qa_pairs, total_pairs, max_embedding_length);

    printf("Please enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0';
    max_emb_size = strlen(sentence) * embedding_dim;
    encodeSentence(query, sentence, charset, embedding_dim, max_embedding_length, total_pairs);
    matchingScore(query, qa_pairs, total_pairs, max_embedding_length, embedding_dim, max_emb_size, charset);
    free(qa_pairs);
    return 0;
}


void getCharset(char charset[]) {
    int i = 0;
    char ch;
    FILE * charset_file;
    charset_file = fopen("charset.txt", "r");

    if (!charset_file) {
        printf("charset.txt açılamadı");
        exit(-1);
    }

    while ((ch = getc(charset_file)) != EOF) {
        charset[i++] = ch;
        
    }
    charset[i] = '\0'; 
    fclose(charset_file);
}

void readEmbeddings(int* embedding_dim, int* max_embedding_length, int* total_pairs, QAPairs qa_pairs[]) {
    FILE * embedding_file;
    embedding_file = fopen("embeddings.txt", "r");
    
    char data[SENTENCE_LENGTH];
    char temp[MAX_EMBEDDING_LENGTH];
    int i, j;
    char* bits;
    if (!embedding_file) {
        printf("ERROR! embeddings.txt could not be opened.\n");
        exit(-1);
    }

    fgets(data, sizeof(data), embedding_file);
    while (strncmp(data, "#####", 5) != 0) {
        if (strncmp(data, "Max", 3) == 0) {
            sscanf(data, "Max encoding length: %d", max_embedding_length);
        }
        if (strncmp(data, "Emb", 3) == 0) {
            sscanf(data, "Embedding dimension: %d", embedding_dim);
        }
        if (strncmp(data, "Tot", 3) == 0) {
            sscanf(data, "Total pairs: %d", total_pairs);
        }
        fgets(data, sizeof(data), embedding_file);
    }
    fgets(temp, sizeof(temp), embedding_file);

    for (i = 0; i < *total_pairs; i++) {
        fgets(temp, sizeof(temp), embedding_file);
        temp[strcspn(temp, "\n")] = '\0'; 
        bits = temp + strlen("Question: "); 
        for (j = 0; j < *max_embedding_length; j++) {
            qa_pairs[i].questions[j] = bits[j] - '0';
        }

        fgets(temp, sizeof(temp), embedding_file);
        temp[strcspn(temp, "\n")] = '\0'; 

        bits = temp + strlen("Answer: "); 
        for (j = 0; j < *max_embedding_length; j++) {
            qa_pairs[i].answers[j] = bits[j] - '0';
        }
        fgets(temp, sizeof(temp), embedding_file);
    }

    fclose(embedding_file);
}

void generateKnowledgeBase(QAPairs qa_pairs[], int total_pairs, int max_embedding_length) {
    int i, j; 
    for (i = 0; i < total_pairs; i++) {
        for (j = 0; j < max_embedding_length; j++) {
            qa_pairs[i].kb[j] = qa_pairs[i].questions[j] ^ qa_pairs[i].answers[j];
        }
    }
}

void encodeSentence(int query[], char sentence[], char charset[], int embedding_dim, int max_encoding_length, int total_pairs) {
    int i, j, k;
    

    int sentence_length = strlen(sentence); /* Find length of sentence */
    if (sentence_length > max_encoding_length / embedding_dim) {
        sentence_length = max_encoding_length / embedding_dim;
    }
    int start_index = max_encoding_length - (sentence_length * embedding_dim); /* Find how many character should be left padded as 0. */

    for (k = 0; k < sentence_length; k++) {  /* Iterate it until sentence ending. */
        for (j = 0; j < embedding_dim; j++) { /* Find character's index in charset */
            if (sentence[k] == charset[j]) {
                query[start_index + j] = 1; /* Set character's index as 1 */
                break;
            }
        }
        start_index += embedding_dim; /* Update new start index. */
    }
}

void matchingScore(int query[], QAPairs qa_pairs[], int total_pairs, int max_encoding_length,
                   int embedding_dim, int max_emb_size, char charset[]) {
    int candidate[MAX_EMBEDDING_LENGTH], i, j, diff_count;
    int differences[MAX_EMBEDDING_LENGTH];
    double matching_score;
    int start = max_encoding_length - max_emb_size;         
    for (i = 0; i < total_pairs; i++) {
        diff_count = 0;
        
        for (j = max_encoding_length - max_emb_size; j < max_encoding_length; j++) {
            candidate[j] = qa_pairs[i].kb[j] ^ query[j];
            differences[j] = qa_pairs[i].answers[j] ^ candidate[j];
            if (differences[j]) {
                diff_count++;
            }
        }
        matching_score = 1.0 - ((double)diff_count / (double)max_emb_size);
        if (matching_score > 0.8) {
            printf("%d. pair eslesti (skor: %.2lf)\nCevap: ", i+1, matching_score);
            decodeAnswer(qa_pairs[i].answers,
                charset, embedding_dim, max_encoding_length);            
        }
    }
    
}
void decodeAnswer(int *region, char charset[], int embedding_dim, int max_encoding_length) {
    int num_chars = max_encoding_length / embedding_dim;
    int i, j, base;
    for (i = 0; i < num_chars; i++) {
        base = i * embedding_dim;
        for (j = 0; j < embedding_dim; j++) {
            if (region[base + j] == 1) {
                putchar(charset[j]);
                break;
            }
        }
    }
    putchar('\n');
}