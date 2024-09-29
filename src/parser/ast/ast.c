#include "../../../includes/parser.h"

bool check_token(t_lexeme token_lex, t_token **cur_tok)
{
    if (*cur_tok == NULL)
        return (NULL);
    if ((*cur_tok)->lexem == token_lex)
    {
        *cur_tok = (*cur_tok)->next;
        return (true);
    }
    *cur_tok = (*cur_tok)->next;    
    return (false);
}

t_ast_node *build_ast(t_token *tokens)
{
    t_ast_node *ast;
    t_token *cur_token;

    ast = NULL;
    cur_token = NULL;
    if (tokens == NULL)
        return (NULL);
    cur_token = tokens;
    ast = command_line(&cur_token);
    if (cur_token != NULL)
    {
        print_error("ast error!\n", 2);
        return (NULL);
    }
    return (ast);
}
