//
// Created by Antony on 09.05.2022.
//
#ifndef LAB5_HUFFMAN_BUFF_FUNC_H
#define LAB5_HUFFMAN_BUFF_FUNC_H

#include <stdio.h>

// Decimal to binary conversion function.
void BINARY(int symbol, char *bin) {
    for (int i = 0; i < 8; i++) {
        bin[7 - i] = (char) (symbol % 2);
        symbol = symbol / 2;
    }
}

// Function that checks fill of the buffer.
int CHECK_BUFF_FILL(int buff_count, char *buff, FILE *file_out) {
    if (buff_count == 8) {                   // If buffer is full - create char from 8 elements of buffer.
        int ans = 0;
        for (int k = 7; k >= 0; k--) {
            ans += (int) (buff[k] * pow(2, 7 - k));
            buff[k] = 0;
        }
        fprintf(file_out, "%c", ans);
        return 0;
    } else
        return buff_count;                   // If buffer isn't full - continue filling buffer.
}

// Function that checks is buffer need to be recreated.
int CHECK_BUFF_EMPTY(int buff_pos, char *buff, FILE *file_in) {
    if (buff_pos == 7) {
        int symbol = fgetc(file_in);        // If reach end of buffer - recreate buffer and get at begin.
        BINARY(symbol, buff);
        return -1;
    } else
        return buff_pos;                    // If not reach end of buffer - continue go on the buffer.
}

#endif //LAB5_HUFFMAN_BUFF_FUNC_H