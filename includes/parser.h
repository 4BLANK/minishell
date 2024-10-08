#ifndef PARSER_H
#define PARSER_H 

// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../lib/libft/libft.h"

# define PARSE_ERROR 2

#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"

# define QUOTE 39
# define DQUOTE 34
# define CPIPE 124
# define GREATER 62
# define LESS 60
# define AMPERSAND 38
# define DOLLAR_SIGN 36
# define QUESTION_MARK 63
# define TILDE 126
# define OPAREN 40
# define CPAREN 41

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
    AMBIGUOUS,
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

// ENV LIST
typedef struct s_envlist
{
    char *name;
    char *value;
    struct s_envlist *next;
} t_envlist;

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

// AST : FILES STRUCT
typedef struct s_file
{
    char *name;
    t_lexeme type;
    struct s_file *next;
} t_file;

// AST STRUCT
typedef struct s_ast_node
{
    t_node_type type;
    union 
    {
        t_argument *arg_list;
        t_file *files;
        struct 
        {
            struct s_ast_node *left;
            struct s_ast_node *right;
        } childs;
    } data;
} t_ast_node;

typedef struct s_ast_gc
{
    t_ast_node *node;
    t_file *files;
    t_argument *args;
    struct s_ast_gc *next;
}t_ast_gc;


// TOKENIZER UTILS
int tokens_spliter(char *line, t_token **toklst);
size_t toklst_size(t_token *toks);
void red_lexer(t_token *tokens, int red_nbr);
int validate_token(t_token *tokenlst);
int is_invalid_special_char(char *tmp, t_token *tok, t_token *prev_tok);
int s_error(t_token *tok);
char    *remove_quote(char *str);
char **lst_tostrarray(t_argument *head);
int rm_token_quotes(t_token *tokenlst);
void lexer(t_token *tokens);
int modify_line(char **line);
int print_error(char *error, int exit_code);
void	ft_lstadd_token_back(t_token **lst, t_token *new_arg);
t_token	*ft_lstnew_token(void *content);
t_token	*ft_lstlast_token(t_token *lst);
bool	ft_strcmp(char *s1, char *s2);
char *ft_getenv(char *env_name);
int schar_detected(char c);

size_t handle_ampersand(char *line, ssize_t i);
size_t count_operator(char *line, ssize_t i);
size_t count_schar(char *line);

int	is_invalid_cparen(char *tmp, t_token *tok, t_token *prev_tok);
int	check_redirection(t_token *tok);
int	toggle_quotes(char c, int flag);
int	check_quote(char c, int *flag, char *quote);
void	check_tmp(char *tmp, char **newstr, size_t *itr);

// DEBUG TOOLS
void print_lst(t_token *tokens);
void print_args(t_argument *args);
void print_files(t_file *files);
void print_space(int space);
void print_ast_tree(t_ast_node *ast_tree, int space);
void	clear_fileslst(t_file **lst, int falg);


// AST UTILS
t_ast_node *ast_create_node(t_node_type type, t_argument *args, t_file *files);
t_ast_node *build_ast(t_token *tokens);
t_ast_node *command_line(t_token **cur_token);
t_ast_node *command_line_or(t_token **cur_token);
t_ast_node *command_line_and(t_token **cur_token);
t_ast_node *grouped_command(t_token **cur_token);
t_ast_node *pipe_line(t_token **cur_token);
t_ast_node *form_command(t_token **tokenlst);
bool check_token(t_lexeme token_lex, t_token **cur_tok);
t_file	*new_file(void *file_name, t_lexeme filetype);
void	addfile_back(t_file **lst, t_file *new);
void	ft_argsadd_back(t_argument **lst, t_argument *new_arg);
t_argument	*ft_argsnew(void *content);
int is_schar (t_lexeme lexem);


// EXPANDER
int expander(t_token **tokens);
t_token *expand_noquotes(t_token **tokens);
int expand_wildcard(t_token **toks);
int expander_core(t_token **toklst);
char *expand_heredoc(char *str);
char *expand_string(char *str);
char *expand_pid_or_exit(char *str, char curchr, char nextchr);
char	*concat(char *dest, char *src, int flag);
char *get_name(char *str, int itr);
t_argument *wildcard_core(char *pattern);
t_token *split_tokens(char *str);
char *expand_token(char *str);


// export
size_t str_arraysize(char **str);
int overwrite_env(char *name, char *value);
bool env_exist(char *name);
t_envlist *init_envlist(char **env);
void print_env(t_envlist *envlst);
char *getenv_name(char *variable);
char *getenv_value(char *variable);
t_envlist *lstnew_env(char *name, char *value);
void    lstadd_env_back(t_envlist **lst, t_envlist *newenv);


// builtin
int export_cmd(char **args);
int env_cmd(void);
int pwd_cmd(char **args);
int cd_cmd(char **args);
int unset_cmd(char **args);
int ft_error(char *cmd, char *arg, char *error);


// CLEAN UP
void free_strarray(char **str);
void ast_distroy(t_ast_node **node, int flag);
void	clear_argslst(t_argument **lst);
void distroy_envlst(t_envlist **envlst);
void	tokens_lstclear(t_token **lst);

#endif
