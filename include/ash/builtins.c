#pragma once
#include "ash/builtins.h"

builtin_func_t builtins[] = {
		{"cd", &ash_cd},
		{"help", &ash_help},
		{"exit", &ash_exit},
};

int ash_num_builtins() {
	return sizeof(builtins) / sizeof(builtin_func_t);
}

int ash_cd(char** args) {
	if (args[1] == NULL) {
		fprintf(stderr, "ash: expected argument to \"cd\"\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("lsh");
		}
	}
	return 1;
}

int ash_help(char** args) {
	for (int i = 0; i < ash_num_builtins(); i++) {
		printf("  %s\n", builtins[i].cmd);
	}

	return 1;
}

int ash_exit(char** args) {
	return 0;
}
