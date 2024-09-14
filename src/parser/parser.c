#include "../../includes/minishell.h"


int parser (t_ast_node **ast, char *line)
{
    t_token *tokenlst;

    tokenlst = NULL;
    if (initial_parsing(line))
        return (PARSE_ERROR);
    if (modify_line(&line))
        return (free(line), PARSE_ERROR);
    if (tokenizer(line, &tokenlst))
    {
        tokens_lstclear(&tokenlst);
        return (free(line), PARSE_ERROR);
    }
    free(line);
    lexer(tokenlst);
    printf(GREEN "== TOKENS LIST =========>\n" RESET);
    print_lst(tokenlst);
    tokenlst = expand_noquotes(&tokenlst);
    if (expander(&tokenlst))
        return (PARSE_ERROR);
    printf(GREEN "\n== EXPANDER OUT =======>\n" RESET);
    print_lst(tokenlst);
    *ast = build_ast(tokenlst);
    tokens_lstclear(&tokenlst);
    return (EXIT_SUCCESS);
}