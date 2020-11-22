#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_vec.h"
#include "parse.h"

int main() {
    char str[257];
    while ((fgets(str, 257, stdin)) != NULL) {
        str[strlen(str) - 1] = '\0';
        token_vec *inf_vec, *post_vec;
        if ((inf_vec = split2toks(str)) == NULL) {
            continue;
        }
        if ((post_vec = inf2post(inf_vec)) == NULL) {
            exit(1);
        }
        token_vec_print(post_vec);
    }

    return 0;
}