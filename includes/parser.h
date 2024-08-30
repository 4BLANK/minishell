#ifndef PARSER_H
#define PARSER_H 

// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../lib/libft/libft.h"

# define QUOTE 39
# define DQUOTE 34
# define CPIPE 124
# define GREATER 62
# define LESS 60
# define AMPERSAND 38
# define DOLLAR_SIGN 63

extern char *lexs_type[];
extern char *ast_node_types[];


// TOKENS LEXEME
typedef enum
{
    STRING,
    ARG,
    PIPE,
    O_FILE,
    CMD,
    I_REDIRECTION,
    O_REDIRECTION,
    HEREDOC,
    DELIMITER,
    APPEND,
    AND,
    OR,
    OPEN_P,
    CLOSE_P
} t_lexeme;

// AST NODE TYPES
typedef enum 
{
    GROUP_NODE,
    AND_NODE,
    OR_NODE,
    PIPELINE,
    COMMAND,
    REDIRECTION,
    ARGUMENTS
} t_node_type;

// TOKENS STRUCT
typedef struct s_token
{
    t_lexeme lexem;
    char *content;
    struct s_token *next;
} t_token;

// AST : ARGUMENTS STRUCT
typedef struct s_argument
{
    char *content;
    struct s_argument *next;
} t_argument;

// AST STRUCT
typedef struct s_ast_node
{
    t_node_type type;
    union 
    {
        t_argument *arg_list;
        struct 
        {
            struct s_ast_node *left;
            struct s_ast_node *right;
        } childs;
    } data;
} t_ast_node;

// TOKENIZER UTILS
char *remove_quote(char *holder, char quote_type);
char check_quotes(char *s);
void lexer(t_token *tokens);
int count_repetition(char *line, char c, int itr);
char *modify_line(char *line);
void print_error(char *error, int exit_code);
void print_lst(t_token *tokens);
void	ft_lstadd_token_back(t_token **lst, t_token *new);
int check_for_echo(t_token *tokens);
void initial_parsing(char *line);
t_token	*ft_lstnew_token(void *content);
int count_special_chars(char *line);
t_token *tokenizer(char *line);
t_token	*ft_lstlast_token(t_token *lst);
bool	ft_strcmp(char *s1, char *s2);


// AST UTILS
void	ft_argsadd_back(t_argument **lst, t_argument *new);
t_argument	*ft_argsnew(void *content);
// t_ast_node *alloc_ast_node(t_node_type type, t_argument *args);
int redirection_found(t_token *tokens);
int is_schar (t_lexeme lexem);
t_argument *args_table(t_token **tokens, t_node_type type);
int pipe_exist(t_token *tokens);
t_ast_node *get_redirection_tree(t_node_type type);
// t_ast_node *new_ast_node(t_node_type type, t_token *tokens);
// t_ast_node *generate_ast_tree(t_token *tokens);
void print_args(t_argument *args);
void print_space(int space);
void print_ast_tree(t_ast_node *ast_tree, int space);

// AST UTILS
void ast_delete(t_ast_node *node);
t_ast_node *ast_create_node(t_node_type type, t_argument *args);

t_ast_node *build_ast(t_token *tokens);

#endif