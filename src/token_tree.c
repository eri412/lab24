#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "token_tree.h"

token_tree *token_tree_create(token tok, token_tree *parent, token_tree *left, token_tree *right) {
    token_tree *tree;
    if ((tree = malloc(sizeof(token_tree))) == NULL) {
        perror("malloc");
        return NULL;
    }
    tree->tok = tok;
    tree->parent = parent;
    tree->left = left;
    tree->right = right;
    if (left != NULL) {
        left->parent = tree;
    }
    if (right != NULL) {
        right->parent = tree;
    }
    return tree;
}

void _token_tree_print_aux(token_tree *tree, int level) {
    if (tree != NULL) {
        _token_tree_print_aux(tree->right, level + 1);
        for (int i = 0; i < level; ++i) {
            printf("\t");
        }

        token cur_tok = tree->tok;
        if (cur_tok.expression == EXPR_VAR) {
            printf("%c\n", cur_tok.variable);
        }
        else if (cur_tok.expression == EXPR_NUM) {
            printf("%d\n", cur_tok.number);
        }
        else if (cur_tok.expression == EXPR_UN_PLUS) {
            printf("#\n");
        }
        else if (cur_tok.expression == EXPR_UN_MINUS) {
            printf("!\n");
        }
        else if (cur_tok.expression == EXPR_BIN_PLUS) {
            printf("+\n");
        }
        else if (cur_tok.expression == EXPR_BIN_MINUS) {
            printf("-\n");
        }
        else if (cur_tok.expression == EXPR_BIN_MULT) {
            printf("*\n");
        }
        else if (cur_tok.expression == EXPR_BIN_DIV) {
            printf("/\n");
        }
        else if (cur_tok.expression == EXPR_BIN_POW) {
            printf("^\n");
        }
        _token_tree_print_aux(tree->left, level + 1);
    }
}

void token_tree_print(token_tree *tree) {
    _token_tree_print_aux(tree, 0);
}

/////////////////////////////////////////////////////////

token_tree_vec *token_tree_vec_create() {
    token_tree_vec *vec;
    if ((vec = malloc(sizeof(token_tree_vec))) == NULL) {
        perror("malloc");
        return NULL;
    }
    vec->size = 0;
    vec->capacity = DEFAULT_CAPACITY;
    if ((vec->buff = malloc(sizeof(token_tree *) * DEFAULT_CAPACITY)) == NULL) {
        free(vec);
        perror("malloc");
        return NULL;
    }
   return vec; 
}

size_t token_tree_vec_size(token_tree_vec *vec) {
    return vec->size;
}

int _token_tree_vec_grow(token_tree_vec *vec) {
    token_tree **temp_buff;
    if ((temp_buff = realloc(vec->buff, sizeof(token_tree *) * vec->capacity * CAPACITY_MULTIPLIER)) == NULL) {
        perror("realloc");
        return 0;
    }
    vec->buff = temp_buff;
    vec->capacity *= CAPACITY_MULTIPLIER;
    return 1;
}

int token_tree_vec_push(token_tree_vec *vec, token_tree *tree) {
    assert(vec->size <= vec->capacity);
    if (vec->size == vec->capacity) {
        if (!_token_tree_vec_grow(vec)) {
            return 0;
        }
    }
    vec->buff[token_tree_vec_size(vec)] = tree;
    vec->size++;
    return 1;
}

int _token_tree_vec_shrink(token_tree_vec *vec) {
    if (vec->capacity / CAPACITY_MULTIPLIER < DEFAULT_CAPACITY) {
        return 0;
    }
    token_tree **temp_buff;
    if ((temp_buff = realloc(vec->buff, sizeof(token_tree *) * vec->capacity / CAPACITY_MULTIPLIER)) == NULL) {
        perror("realloc");
        return 0;
    }
    vec->buff = temp_buff;
    vec->capacity /= CAPACITY_MULTIPLIER;
    return 1;
}

token_tree *token_tree_vec_pop(token_tree_vec *vec) {
    assert(vec->size <= vec->capacity);
    if (vec->size == 0) {
        return NULL;
    }
    vec->size--;
    token_tree *temp_tree = vec->buff[vec->size];
    if (vec->capacity / CAPACITY_MULTIPLIER == vec->size) {
        _token_tree_vec_shrink(vec);
    }
    return temp_tree;
}

void token_tree_vec_delete(token_tree_vec *vec) {
    free(vec->buff);
    free(vec);
}
