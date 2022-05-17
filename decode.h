//
// Created by Antony on 20.04.2022.
//

#ifndef LAB5_HUFFMAN_DECODE_H
#define LAB5_HUFFMAN_DECODE_H

#include "queue&tree_func.h"
#include "buff_func.h"

// // Function that creates Huffman code tree from file.
void CR_UNCODE_TREE(int *pos, char *buff, TREE *T, FILE *file_in) {
    if (buff[*pos] == 0) {
        *pos = CHECK_BUFF_EMPTY(*pos, buff, file_in);
        (*pos)++;
        int ans = 0;
        for (int i = 0; i < 8; i++) {
            ans += buff[*pos] * (int) pow(2, 7 - i);
            *pos = CHECK_BUFF_EMPTY(*pos, buff, file_in);
            (*pos)++;
        }
        T->symbol = ans;
        return;
    }

    T->left = CR_ELEM_TREE(0);
    *pos = CHECK_BUFF_EMPTY(*pos, buff, file_in);
    (*pos)++;
    CR_UNCODE_TREE(pos, buff, T->left, file_in);

    T->right = CR_ELEM_TREE(0);
    CR_UNCODE_TREE(pos, buff, T->right, file_in);
}

// Function that moves on tree and searches for a symbol by its code.
TREE *TREE_MOVEMENT(int symbol, int extra_zero, char *buff, TREE *cur, TREE *T, FILE *file_out) {
    if (cur->left != NULL && cur->right != NULL) {
        for (int i = 0; i < 8; i++) {
            buff[7 - i] = (char) (symbol % 2);
            symbol = symbol / 2;
        }
        for (int i = 0; i < (8 - extra_zero); i++) {
            if (buff[i] == 1)
                cur = cur->right;
            if (buff[i] == 0)
                cur = cur->left;
            if (cur->left == NULL && cur->right == NULL) {
                fprintf(file_out, "%c", cur->symbol);
                cur = T;
            }
            buff[i] = 0;
        }
    } else
        for (int i = 0; i < (8 - extra_zero); i++)
            fprintf(file_out, "%c", cur->symbol);
    return cur;
}

void DECODE(FILE *file_in) {
    int symbol = fgetc(file_in);
    if (symbol == EOF) {
        FILE *file_out = fopen("out.txt", "wb");
        fclose(file_out);
        fclose(file_in);
        return;
    }
    char *buff = calloc(8, sizeof(char));
    for (int i = 0; i < 8; i++) {
        buff[7 - i] = (char) (symbol % 2);
        symbol = symbol / 2;
    }
    int pos = 0;

    TREE *T = INIT_TREE();

    CR_UNCODE_TREE(&pos, buff, T, file_in);

    FILE *file_out = fopen("5.txt", "wb");
    fprintf(file_out,"d");

    TREE *cur = T;
    symbol = fgetc(file_in);
    int next_symbol = fgetc(file_in);
    int next_next_symbol = fgetc(file_in);

    while (next_next_symbol != EOF) {
        cur = TREE_MOVEMENT(symbol, 0, buff, cur, T, file_out);
        symbol = next_symbol;
        next_symbol = next_next_symbol;
        next_next_symbol = fgetc(file_in);
    }
    TREE_MOVEMENT(symbol, next_symbol - '0', buff, cur, T, file_out);

    free(buff);
    MAKE_NULL(T);
    fclose(file_in);
    fclose(file_out);
}

#endif //LAB5_HUFFMAN_DECODE_H