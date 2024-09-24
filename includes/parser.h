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
    void *ptr;
    struct s_ast_gc *next;
}t_ast_gc;

void ptr_collector(void *ptr);

// TOKENIZER UTILS
char *remove_quote(char *str);
int rm_token_quotes(t_token *tokenlst);
char check_quotes(char *s);
void lexer(t_token *tokens);
int count_repetition(char *line, char c, int itr);
int modify_line(char **line);
int print_error(char *error, int exit_code);

void print_lst(t_token *tokens);
void	ft_lstadd_token_back(t_token **lst, t_token *new_arg);
int check_for_echo(t_token *tokens);
int initial_parsing(char *line);
t_token	*ft_lstnew_token(void *content);
int count_special_chars(char *line, int *s_count);
int tokenizer(char *line, t_token **tokenlst);
t_token	*ft_lstlast_token(t_token *lst);
bool	ft_strcmp(char *s1, char *s2);
void	tokens_lstclear(t_token **lst);
t_token *modify_redlst(t_token **tokens_list);
char *ft_getenv(char *env_name);
void	reverse_rotate(t_token **s);
void	rotate(t_token **s);

// AST UTILS
void	ft_argsadd_back(t_argument **lst, t_argument *new_arg);
t_argument	*ft_argsnew(void *content);
// t_ast_node *alloc_ast_node(t_node_type type, t_argument *args);
int redirection_found(t_token *tokens);
int is_schar (t_lexeme lexem);
t_argument *args_table(t_token **tokens, t_node_type type);
int pipe_exist(t_token *tokens);
t_ast_node *get_redirection_tree(t_node_type type);
void print_args(t_argument *args);
void print_space(int space);
void print_ast_tree(t_ast_node *ast_tree, int space);

// AST UTILS
// void ast_delete(t_ast_node *node);
t_ast_node *ast_create_node(t_node_type type, t_argument *args, t_file *files);

t_ast_node *build_ast(t_token *tokens);


// EXPANDER
int expander(t_token **tokens);
t_token *expand_noquotes(t_token **tokens);

// export
size_t str_arraysize(char **str);

// builtin
int export_cmd(t_argument *arguments);
int env_cmd(void);
int pwd_cmd(char **args);
int cd_cmd(char **args, char **env);
int unset_cmd(char **args);

int overwrite_env(char *name, char *value);

void free_strarray(char **str);
char **dupenv(char **env);

int delete_tokensnode(t_token **tokenlst, size_t index);

char **lst_tostrarray(t_argument *head);

// char **set_newenv(char *arg, char **env, int unset);

bool env_exist(char *name);

t_ast_node *form_command(t_token **tokenlst);

t_envlist *init_envlist(char **env);
void print_env(t_envlist *envlst);
void distroy_envlst(t_envlist **envlst);

void ast_distroy(t_ast_node **node);
void print_files(t_file *files);

t_ast_node *command_line(t_token **cur_token);

t_ast_node *command_line_or(t_token **cur_token);
t_ast_node *command_line_or_1(t_token **cur_token);
t_ast_node *command_line_or_2(t_token **cur_token);

t_ast_node *command_line_and(t_token **cur_token);
t_ast_node *command_line_and_1(t_token **cur_token);
t_ast_node *command_line_and_2(t_token **cur_token);

t_ast_node *grouped_command(t_token **cur_token);
t_ast_node *grouped_command_0(t_token **cur_token);
t_ast_node *grouped_command_1(t_token **cur_token);
t_ast_node *grouped_command_2(t_token **cur_token);

t_ast_node *pipe_line(t_token **cur_token);
t_ast_node *pipe_line_1(t_token **cur_token);
t_ast_node *pipe_line_2(t_token **cur_token);
t_ast_node *pipe_line_3(t_token **cur_token);
t_ast_node *pipe_line_4(t_token **cur_token);



t_ast_node *command_line_1(t_token **cur_token);
t_ast_node *command_line_2(t_token **cur_token);
t_ast_node *command_line_3(t_token **cur_token);
t_ast_node *command_line_4(t_token **cur_token);


t_file	*new_file(void *file_name, t_lexeme filetype);
void	addfile_back(t_file **lst, t_file *new);
int schar_detected(char c);
int syntax_err_check(t_token *tokenlst);
char *getenv_name(char *variable);
char *getenv_value(char *variable);
t_envlist *lstnew_env(char *name, char *value);
void    lstadd_env_back(t_envlist **lst, t_envlist *newenv);

char *expand_string(char *str);
char *expand_pid_or_exit(char *str, char curchr, char nextchr);
char	*concat(char *dest, char *src, int flag);
char *get_name(char *str, int itr);

t_argument *wildcard_core(char *pattern);
void	clear_argslst(t_argument **lst);
int expand_wildcard(t_token **toks);

int expander_core(t_token **toklst);
char *expand_heredoc(char *str);

#endif
