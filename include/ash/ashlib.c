#include "ash/ashlib.h"

void ash_loop(void) {
	char* line;
	char** args;
	int status;

	do {
		fputs(ash_prompt, stdout);
		line = ash_read_line();
		args = ash_get_args(line);
		status = ash_exec(args);

		free(line);
		free(args);
	} while (status);
}

char* ash_read_line() {
	int size = ASH_LINE_BUFSIZE;
	char* buf = (char*) malloc(ASH_LINE_BUFSIZE);

	int pos = 0;
	char c;

	if (!buf) {
		perror("ash");
		exit(EXIT_FAILURE);
	}

	while (1) {
		c = (char) getchar();

		if (c == '\n' || c == EOF) {
			buf[pos] = '\0';
			return buf;
		}

		buf[pos++] = c;

		if (pos >= size) {
			size += ASH_LINE_BUFSIZE;
			buf = realloc(buf, size);
			if (!buf) {
				perror("ash");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char** ash_get_args(char* line) {
	int size = ASH_TOK_BUFSIZE;
	char** buf = calloc(size, sizeof(char*));
	char* token = NULL;
	int pos = 0;

	do {
		token = strtok(token ? NULL : line, ASH_TOK_DELIM);
		buf[pos++] = token;

		if (pos >= size) {
			size += ASH_TOK_BUFSIZE;
			buf = realloc(buf, size);
			if (!buf) {
				perror("ash");
				exit(EXIT_FAILURE);
			}
		}

	} while (token != NULL);

	return buf;
}

int ash_exec(char** args) {
	pid_t pid;
	int status;
	int i;

	if (args[0] == NULL) {
		return 1;
	}

	for (i = 0; i < ash_num_builtins(); i++) {
		if (strcmp(args[0], builtins[i].cmd) == 0) {
			return (builtins[i].func)(args);
		}
	}

	pid = fork();
	if (pid == 0) {
		// child
		if (execvp(args[0], args) == -1) {
			fprintf(stderr, "ash: ");
			perror(args[0]);
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		// error forking
		perror("ash");
	} else {
		// parent
		do {
			(void) waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}
