#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_vec.h"
#include "token_tree.h"
#include "parse.h"

int main() {
    char str[257];
    while ((fgets(str, 257, stdin)) != NULL) {
        str[strlen(str) - 1] = '\0';
        token_vec *inf_vec, *post_vec;
        token_tree *expr_tree;
        if ((inf_vec = split2toks(str)) == NULL) {
            continue;
        }
        if ((post_vec = inf2post(inf_vec)) == NULL) {
            exit(1);
        }
        expr_tree = post2tree(post_vec);
        token_tree_print(expr_tree);
    }

    return 0;
}
