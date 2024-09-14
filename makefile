NAME = minishell
CC = cc
LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
SRC =	./src/main.c\
		./src/executor/exec/exec.c\
		./src/executor/exec/exec_tools.c\
		./src/parser/parser.c\
		./src/parser/tokenizer/string_utils.c\
		./src/parser/tokenizer/tokenizer_utils.c\
		./src/parser/tokenizer/lexer.c\
		./src/parser/tokenizer/stack_utils.c\
		./src/parser/ast/ast_utils.c\
		./src/parser/ast/utils.c\
		./src/parser/ast/ast.c\
		./src/parser/expander/expander.c\
		
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
