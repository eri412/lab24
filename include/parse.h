#ifndef _PARSE_H_
#define _PARSE_H_

#include "token_vec.h"

token_vec *split2toks(char *str);
token_vec *inf2post(token_vec *input_vec);
int check_str(char *str);

#endif
