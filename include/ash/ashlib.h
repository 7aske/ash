#ifndef ASH_ASHLIB_H
#define ASH_ASHLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ash/builtins.h"

extern builtin_func_t builtins[];

#include "config.h"

#define ASH_LINE_BUFSIZE        1024
#define ASH_TOK_BUFSIZE           64
#define ASH_TOK_DELIM    " \t\r\n\a"


//@formatter:off
void   ash_loop(void);
char*  ash_read_line();
char** ash_get_args(char* line);
int    ash_exec(char** args);
//@formatter:on

#endif //ASH_ASHLIB_H
