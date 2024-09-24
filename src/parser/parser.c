#include "../../includes/minishell.h"

int parser (t_ast_node **ast, char *line)
{
    t_token *tokenlst;

    (void)ast;
    tokenlst = NULL;
    if (modify_line(&line) > 0)
        return (free(line), PARSE_ERROR);
    if (tokenizer(line, &tokenlst)  || syntax_err_check(tokenlst))
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
    // distroy_envlst(&sh->envlst);
    // exit(1);
    return (EXIT_SUCCESS);
}