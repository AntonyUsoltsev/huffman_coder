//
// Created by Antony on 16.04.2022.
//
#include "queue&tree_func.h"
#include "code.h"
#include "decode.h"

int main() {
    FILE *file_in = fopen("4.txt", "rb");

    int action = fgetc(file_in);

    if (action == 'c')
        CODE(file_in);

    else if (action == 'd')
        DECODE(file_in);

    else {
        fclose(file_in);
        printf("wrong action");
    }
    return 0;
}