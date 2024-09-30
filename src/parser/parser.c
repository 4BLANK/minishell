#include "../../includes/minishell.h"

int parser (t_ast_node **ast, char *line)
{
    t_token *tokenlst;

    tokenlst = NULL;
    if (modify_line(&line) > 0)
        return (free(line), PARSE_ERROR);    
    if (tokens_spliter(line, &tokenlst)  
        || validate_token(tokenlst))
    {
        tokens_lstclear(&tokenlst);
        return (free(line), PARSE_ERROR);
    }
    free(line);
    lexer(tokenlst);
    printf(GREEN "== TOKENS LIST =========>\n" RESET);
    print_lst(tokenlst);
    if (expander_core(&tokenlst))
        return (PARSE_ERROR);
    *ast = build_ast(tokenlst);
    tokens_lstclear(&tokenlst);
    return (EXIT_SUCCESS);
}
