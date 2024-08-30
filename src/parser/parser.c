#include "../../includes/minishell.h"


int parser (t_ast_node **ast, char *line, char **env)
{
    t_token *tokenlst;

    tokenlst = NULL;
    if (initial_parsing(line))
        return (EXIT_FAILURE);
    if (modify_line(&line))
        return (EXIT_FAILURE);
    if (tokenizer(line, &tokenlst))
        return (EXIT_FAILURE);
    lexer(tokenlst);
    print_lst(tokenlst);
    // exit(1);
    tokenlst = modify_redlst(&tokenlst); 
    tokenlst = expand_noquotes(&tokenlst, env);
    
    if (expander(&tokenlst, env))
        return (EXIT_FAILURE);
    *ast = build_ast(tokenlst);
    return (EXIT_SUCCESS);
}