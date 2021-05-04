#ifndef ASH_BUILTINS_H
#define ASH_BUILTINS_H

#include <stdio.h>
#include <unistd.h>

typedef struct {
	char* cmd;
	int (* func)(char**);
} builtin_func_t;

int ash_exit(char** args);
int ash_help(char** args);
int ash_cd(char** args);
int ash_num_builtins();

#endif //ASH_BUILTINS_H
