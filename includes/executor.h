#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../lib/libft/libft.h"

//redirections
void redirect_input(const char *filename);
void redirect_output(const char *filename);
void append_redirect_output(const char *filename);
void here_doc(const char *delimiter);
