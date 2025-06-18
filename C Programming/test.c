#include <stdio.h>
#include <string.h>

// Karakter kümesi
char char_set[] = {' ', 'H', 'o', 'w', 'm', 'a', 'n', 'y', 't', 's', 'r', 'e', '1', '2'};

// One-hot encoding fonksiyonu
void one_hot_encode_char(char c, int* encoding) {
    for (int i = 0; i < sizeof(char_set) / sizeof(char_set[0]); i++) {
        encoding[i] = (char_set[i] == c) ? 1 : 0;
    }
}

// Cümleyi one-hot vektöre çevirme
void sentence_to_embedding(char* sentence, int* embedding, int* max_length) {
    int idx = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        int encoding[sizeof(char_set) / sizeof(char_set[0])];  // Her karakter için one-hot vektörü
        one_hot_encode_char(sentence[i], encoding);
        
        for (int j = 0; j < sizeof(char_set) / sizeof(char_set[0]); j++) {
            embedding[idx++] = encoding[j];
        }
    }
    *max_length = idx;
}

// Padding işlemi
void pad_embedding(int* embedding, int max_length, int desired_length) {
    for (int i = max_length; i < desired_length; i++) {
        embedding[i] = 0;  // Geriye kalanları sıfırla doldur
    }
}

int main() {
    // Örnek veri (soru ve cevaplar)
    char* questions[] = {"How many months are there in a year?", "What is Earth's satellite?"};
    char* answers[] = {"12", "Moon"};
    int num_pairs = 2;

    // En büyük embedding uzunluğunu bulma
    int max_embedding_length = 0;
    int embeddings[2][1000];  // 1000, cümle başına alacağımız embedding uzunluğu

    // Soruları ve cevapları işleme
    for (int i = 0; i < num_pairs; i++) {
        int question_embedding[1000];
        int answer_embedding[1000];
        
        int question_length, answer_length;
        sentence_to_embedding(questions[i], question_embedding, &question_length);
        sentence_to_embedding(answers[i], answer_embedding, &answer_length);
        
        // Maksimum uzunluğu güncelle
        if (question_length > max_embedding_length) max_embedding_length = question_length;
        if (answer_length > max_embedding_length) max_embedding_length = answer_length;
        
        // Padding ekle
        pad_embedding(question_embedding, question_length, max_embedding_length);
        pad_embedding(answer_embedding, answer_length, max_embedding_length);
        
        // Verileri çok boyutlu diziye yerleştirme
        for (int j = 0; j < max_embedding_length; j++) {
            embeddings[i][j] = question_embedding[j];  // Soru embedding'i
        }
        // Cevapları da aynı şekilde işleyebilirsiniz.
    }
    
    // Embeddingleri dosyaya yazma
    FILE* file = fopen("embeddings.txt", "w");
    fprintf(file, "Max embedding length: %d\n", max_embedding_length);
    fprintf(file, "Embedding dimension: %ld\n", sizeof(char_set) / sizeof(char_set[0]));
    fprintf(file, "Total question-answer pairs: %d\n", num_pairs);
    fprintf(file, "---\n");

    for (int i = 0; i < num_pairs; i++) {
        fprintf(file, "Question: ");
        for (int j = 0; j < max_embedding_length; j++) {
            fprintf(file, "%d ", embeddings[i][j]);
        }
        fprintf(file, "\nAnswer: ");
        // Benzer şekilde cevabı da yazabilirsiniz.
        fprintf(file, "\n---\n");
    }

    fclose(file);
    return 0;
}
