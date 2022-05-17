//
// Created by Antony on 20.04.2022.
//
#ifndef LAB5_HUFFMAN_QUEUE_TREE_FUNC_H
#define LAB5_HUFFMAN_QUEUE_TREE_FUNC_H

#include <stdio.h>
#include <math.h>
#include <malloc.h>

#define ASCII 256

#define QUEUE struct queue
#define TREE struct tree

// Stack structure.
QUEUE {
    int freq;
    TREE *tree;
    QUEUE *next;
};

// Tree structure.
TREE {
    int symbol;
    TREE *right;
    TREE *left;
};

// Function that initializes stack.
QUEUE *INIT_STACK() {
    QUEUE *cur = malloc(sizeof(QUEUE));
    cur->next = NULL;
    return cur;
}

// Function that initializes root of tree.
TREE *INIT_TREE() {
    TREE *cur = malloc(sizeof(TREE));
    cur->left = NULL;
    cur->right = NULL;
    return cur;
}

// Function that creates element of stack.
QUEUE *CR_ELEM_QUEUE(int freq, TREE *tree) {
    QUEUE *cur = malloc(sizeof(QUEUE));
    cur->freq = freq;
    cur->tree = tree;
    cur->next = NULL;
    return cur;
}

// Function that creates node of tree.
TREE *CR_ELEM_TREE(int symbol) {
    TREE *cur = malloc(sizeof(TREE));
    cur->symbol = symbol;
    cur->right = NULL;
    cur->left = NULL;
    return cur;
}

// Function that removes the head element of stack.
TREE *POP(QUEUE *Q) {
    QUEUE *cur = Q->next;
    TREE *tmp = cur->tree;
    Q->next = cur->next;
    free(cur);
    return tmp;
}

// Function that creates parent node for two nodes.
TREE *CR_PARENT(QUEUE *Q) {
    TREE *left = POP(Q);
    TREE *right = POP(Q);
    TREE *cur = malloc(sizeof(TREE));
    cur->left = left;
    cur->right = right;
    cur->symbol = 0;
    return cur;
}

// Function that adds an element to the stack in ascending order of frequency.
void PUSH(QUEUE *elem, QUEUE *Q) {
    QUEUE *cur = Q;
    while ((cur->next != NULL) && (elem->freq > cur->next->freq))
        cur = cur->next;
    elem->next = cur->next;
    cur->next = elem;
}

// Function that free tree.
void MAKE_NULL(TREE *T) {
    if (T->left)
        MAKE_NULL(T->left);
    if (T->right)
        MAKE_NULL(T->right);
    free(T);
}

#endif //LAB5_HUFFMAN_QUEUE_TREE_FUNC_H