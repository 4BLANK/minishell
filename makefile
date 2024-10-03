NAME = minishell
CC = cc
LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror -ggdb
SRCDIR = ./src/ ./src/signals/ ./src/executor/redirections/ ./src/executor/exec/ ./src/parser/ ./src/parser/expander/ ./src/shell/ ./src/built-in/ ./src/parser/gc/ ./src/parser/ast/ ./src/parser/tokenizer/
BIN_DIR = bin

SRC:= $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c)) 
OBJ:=$(patsubst %.c, $(BIN_DIR)/%.o, $(notdir $(SRC)))

vpath %.c $(SRCDIR)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

$(BIN_DIR)/%.o: %.c | $(BIN_DIR)
	$(CC) $(FLAGS) -c -o $@ $<

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

clean:
	@rm -rf $(BIN_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(LIBFT)
	@rm -rf $(NAME)

re: fclean all

.SECONDARY: