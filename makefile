NAME = minishell
CC = cc
LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror -ggdb
SRC =	./src/main.c\
		./src/signals/signal_handling.c\
		./src/executor/redirections/redirect.c\
		./src/executor/exec/pre_exec_errors.c\
		./src/executor/exec/group_exec.c\
		./src/executor/exec/built_ins_handling.c\
		./src/executor/exec/execute_command.c\
		./src/executor/exec/execute_pipeline.c\
		./src/executor/exec/and_exec.c\
		./src/executor/exec/or_exec.c\
		./src/executor/redirections/redirect_input.c\
		./src/executor/redirections/here_doc.c\
		./src/executor/redirections/redirect_output.c\
		./src/executor/redirections/append_redirect_output.c\
		./src/executor/exec/exec.c\
		./src/executor/exec/exec_tools.c\
		./src/parser/parser.c\
		./src/parser/tokenizer/string_utils.c\
		./src/parser/tokenizer/tokenizer_utils.c\
		./src/parser/tokenizer/validate_tok.c\
		./src/parser/tokenizer/invalid_tok.c\
		./src/parser/tokenizer/tok_tools.c\
		./src/parser/tokenizer/lexer.c\
		./src/parser/ast/ast_utils.c\
		./src/parser/ast/utils.c\
		./src/parser/ast/ast.c\
		./src/parser/expander/expander.c\
		./src/parser/expander/wildcards.c\
		./src/shell/utils.c\
		./src/built-in/pwd_cmd.c\
		./src/built-in/cd_cmd.c\
		./src/built-in/unset_cmd.c\
		./src/built-in/env_cmd.c\
		./src/built-in/echo_cmd.c\
		./src/built-in/exit_cmd.c\
		./src/parser/expander/env_utils.c\
		./src/built-in/export_cmd.c\
		./src/parser/gc/garbage_collector.c\
		./src/parser/tokenizer/tokenizer.c\
		./src/parser/expander/concat.c\
		./src/parser/expander/expand_no_quotes.c\
		./src/parser/expander/split_tokens.c\
		./src/parser/expander/expand_token.c\
		./src/parser/expander/expand_wildcard.c\
		./src/parser/ast/and_ast.c\
		./src/parser/ast/command_line_ast.c\
		./src/parser/ast/or_ast.c\
		./src/parser/ast/group_ast.c\
		./src/parser/ast/pipeline_ast.c\
		./src/parser/tokenizer/lexer_tools.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

	
clean:
	@rm -rf $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(LIBFT)
	@rm -rf $(NAME)

re: fclean all
