#include "../includes/minishell.h"

char *lexs_type[] = 
{
    "STRING",
    "ARG",
    "PIPE",
    "FILE",
    "CMD",
    "I_RED",
    "O_RED",
    "HERDOC",
    "DELIMITER",
    "APPEND",
    "AND",
    "OR",
    "OPEN_P",
    "CLOSE_P"
};

char *ast_node_types[] = 
{
    "GROUP",
    "AND",
    "OR",
    "PIPELINE",
    "COMMAND",
    "REDIRECTION",
    "ARGUMENTS"
};

t_token	*new_token(void *content, t_lexeme lex)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (0);
    token->content = content;
    token->lexem = lex;
	token->next = NULL;
	return (token);
}

// int main ()
// {
//     t_token *tokens = NULL;
//     t_ast_node *ast_tree = NULL;

//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("("), OPEN_P));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("ls"), CMD));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("-al"), ARG));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("|"), PIPE));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("grep"), CMD));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("txt"), ARG));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("&&"), AND));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("("), OPEN_P));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("cat"), CMD));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("file1"), ARG));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("||"), OR));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("cat"), CMD));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("file2"), ARG));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup(")"), CLOSE_P));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup(")"), CLOSE_P));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("||"), OR));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("("), OPEN_P));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("echo"), CMD));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("No files"), ARG));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("&&"), AND));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("touch"), CMD));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("newfile"), ARG));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup(")"), CLOSE_P));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("||"), OR));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("echo"), CMD));
//     ft_lstadd_token_back(&tokens, new_token(ft_strdup("Fallback"), ARG));


//     // print_lst(tokens);
//     // printf("============================================\n");
//     ast_tree = build_ast(tokens);

//     // printf("%s\n", ast_node_types[ast_tree->type]);
//     print_ast_tree(ast_tree, 0);
// }

int main (int ac, char **av)
{
    char *line;
    t_token *tokens = NULL;
    t_ast_node *ast_tree = NULL;

    (void)ac;
    (void)av;
    while (1)
    {
        line = readline("-> ");
        initial_parsing(line);
        line = modify_line(line);
        tokens = tokenizer(line);
        lexer(tokens);
        ast_tree = build_ast(tokens);
        print_ast_tree(ast_tree, 0);
        // print_lst(tokens);
        // printf("%s\n", line);
        free(line);
    }   
    return (0);
}
