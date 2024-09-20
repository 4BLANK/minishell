#include "../../includes/minishell.h"

//TODO: test for bash: $data: ambiguous redirect before you expand
//chack if the result of the expansion is more than 1 toks
int parser (t_ast_node **ast, char *line)
{
    t_token *tokenlst;

    tokenlst = NULL;
    // if (initial_parsing(line))
    //     return (PARSE_ERROR);
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
    // print_lst(tokenlst);
    // printf(RED "== WILDCARDS ===========>\n" RESET);
    // test if file before you lex -> ambiguous redirec
    // expand_wildcard(&tokenlst);
    print_lst(tokenlst);
    // exit(1);
    tokenlst = expand_noquotes(&tokenlst);
    if (expander(&tokenlst))
        return (PARSE_ERROR);
    printf(GREEN "\n== EXPANDER OUT =======>\n" RESET);
    print_lst(tokenlst);
    *ast = build_ast(tokenlst);
    tokens_lstclear(&tokenlst);
    return (EXIT_SUCCESS);
}