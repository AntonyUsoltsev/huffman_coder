//
// Created by Antony on 20.04.2022.
//
#ifndef LAB5_HUFFMAN_CODE_H
#define LAB5_HUFFMAN_CODE_H

#include "queue&tree_func.h"
#include "buff_func.h"

// Function that creates Huffman code tree.
TREE *CREATE_CODE_TREE(int *max_count, FILE *file_in) {
    int symbol = fgetc(file_in);
    if (symbol == EOF) {
        FILE *file_out = fopen("out.txt", "wb");
        fclose(file_out);
        fclose(file_in);
        return NULL;
    }

    int *freq = calloc(ASCII, sizeof(int));        // Сhar frequency array.
    while (symbol != EOF) {
        freq[symbol]++;
        symbol = fgetc(file_in);
    }

    QUEUE *Q = INIT_STACK();
    for (int i = 0; i < ASCII; i++)
        if (freq[i] != 0) {
            PUSH(CR_ELEM_QUEUE(freq[i], CR_ELEM_TREE(i)), Q);
            (*max_count)++;
        }

    while (Q->next->next) {
        int new_freq = Q->next->freq + Q->next->next->freq;
        PUSH(CR_ELEM_QUEUE(new_freq, CR_PARENT(Q)), Q);
    }

    TREE *T = Q->next->tree;

    free(Q->next);
    free(Q);
    free(freq);
    return T;
}

// Function that writes the code of each element to the matrix.
void CODE_PRE_ORDER(char transit, int pos, char *temp, char **code_table, TREE *T) {
    temp[pos] = transit;
    if (T->left)
        CODE_PRE_ORDER(0, pos + 1, temp, code_table, T->left);
    if (T->right)
        CODE_PRE_ORDER(1, pos + 1, temp, code_table, T->right);
    else {
        int code_len = pos;
        for (int i = 0; i <= code_len; i++)
            code_table[T->symbol][i] = temp[i];
        code_table[T->symbol][code_len + 1] = -1;        // -1 shows end of code.
        return;
    }
}

// Function that prints Huffman tree to output file.
void TREE_OUTPUT(int *pos, char *buff, TREE *T, FILE *file_out) {
    if (T->left) {
        *pos = CHECK_BUFF_FILL(*pos, buff, file_out);
        buff[*pos] = 1;
        (*pos)++;
        TREE_OUTPUT(pos, buff, T->left, file_out);
    }
    if (T->right)
        TREE_OUTPUT(pos, buff, T->right, file_out);
    else {
        *pos = CHECK_BUFF_FILL(*pos, buff, file_out);
        buff[*pos] = 0;
        (*pos)++;
        char *bin = calloc(8, sizeof(char));
        BINARY(T->symbol, bin);
        for (int i = 0; i < 8; i++) {
            *pos = CHECK_BUFF_FILL(*pos, buff, file_out);
            buff[*pos] = bin[i];
            (*pos)++;
        }
        free(bin);
        return;
    }
}

// Function that encodes the input data.
void CODING(char **code_table, FILE *file_in, FILE *file_out) {
    int buff_count = 0;
    char *buff = calloc(8, sizeof(char));

    fseek(file_in, 1, SEEK_SET);
    int symbol = fgetc(file_in);
    while (symbol != EOF) {
        int i = 0;
        while (code_table[symbol][i] != -1) {       // Write code of symbol to the buffer.
            buff_count = CHECK_BUFF_FILL(buff_count, buff, file_out);
            buff[buff_count] = code_table[symbol][i];
            i++;
            buff_count++;
        }
        symbol = fgetc(file_in);
    }

    buff_count = CHECK_BUFF_FILL(buff_count, buff, file_out);

    if (buff_count != 0) {
        int extra_zero = 0;                         // Count of non-significant zeros
        for (int i = buff_count; i < 8; i++) {
            buff[i] = 0;
            extra_zero++;
        }
        CHECK_BUFF_FILL(8, buff, file_out);
        fprintf(file_out, "%d", extra_zero);
    } else
        fprintf(file_out, "%d", 0);
    free(buff);
}

void CODE(FILE *file_in) {

    int max_count = 0;
    TREE *T = CREATE_CODE_TREE(&max_count, file_in);
    if (T == NULL)
        return;

    char **code_table = malloc(ASCII * sizeof(char *));
    for (int i = 0; i < ASCII; i++) {
        code_table[i] = malloc((max_count + 5) * sizeof(char));
    }

    if (T->left && T->right) {
        char *temp = malloc(max_count * sizeof(char));
        CODE_PRE_ORDER(0, 0, temp, code_table, T->left);
        CODE_PRE_ORDER(1, 0, temp, code_table, T->right);
        free(temp);
    } else {
        code_table[T->symbol][0] = 1;
        code_table[T->symbol][1] = -1;
    }

    FILE *file_out = fopen("3.txt", "wb");
    fprintf(file_out,"d");

    char *buff = calloc(8, sizeof(char));

    int pos = 0;
    TREE_OUTPUT(&pos, buff, T, file_out);

    if (pos != 0)
        CHECK_BUFF_FILL(8, buff, file_out);
    free(buff);

    CODING(code_table, file_in, file_out);

    MAKE_NULL(T);
    for (int i = 0; i < ASCII; i++)
        free(code_table[i]);
    free(code_table);

    fclose(file_in);
    fclose(file_out);
}

#endif //LAB5_HUFFMAN_CODE_H