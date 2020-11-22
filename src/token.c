#include <stdlib.h>

#include "token.h"

int op_precedence(token *tok) {
    if (tok == NULL) {
        return PRECEDENCE_EMPTY;
    }
    if (tok->expression == EXPR_UN_PLUS || tok->expression == EXPR_UN_MINUS) {
        return 4;
    }
    else if (tok->expression == EXPR_BIN_POW) {
        return 3;
    }
    else if (tok->expression == EXPR_BIN_MULT || tok->expression == EXPR_BIN_DIV) {
        return 2;
    }
    else if (tok->expression == EXPR_L_BRACE) {
        return 0;
    }
    else {
        return 1;
    }
}
