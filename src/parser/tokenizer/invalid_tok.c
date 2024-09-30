#include "../../../includes/minishell.h"

int is_invalid_pipe_and(char *tmp, t_token *tok, t_token *prev_tok);
int is_invalid_greater_less(char *tmp, t_token *tok);
int is_invalid_tok_seq(char *tmp, t_token *tok);
int is_invalid_oparen(char *tmp, t_token *tok, t_token *prev_tok);
int is_invalid_cparen(char *tmp, t_token *tok, t_token *prev_tok);
int check_redirection(t_token *tok);

int is_invalid_special_char(char *tmp, t_token *tok, t_token *prev_tok)
{
    if (ft_strlen(tmp) > 2)
        return (EXIT_FAILURE);
    if (is_invalid_pipe_and(tmp, tok, prev_tok))
        return (EXIT_FAILURE);
    if (is_invalid_greater_less(tmp, tok))
        return (EXIT_FAILURE);
    if (is_invalid_tok_seq(tmp, tok))
        return (EXIT_FAILURE);
    if (tmp[0] == OPAREN && is_invalid_oparen(tmp, tok, prev_tok))
        return (EXIT_FAILURE);
    if (tmp[0] == CPAREN && is_invalid_cparen(tmp, tok, prev_tok))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int is_invalid_pipe_and(char *tmp, t_token *tok, t_token *prev_tok)
{
    if ((tmp[0] == CPIPE || (ft_strncmp(tmp, "&&", 2) == 0)) 
        && (tok->next == NULL || prev_tok == NULL))      
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
int is_invalid_greater_less(char *tmp, t_token *tok)
{
    if ((tmp[0] == GREATER || tmp[0] == LESS) && (!(tok->next) 
        || schar_detected((tok->next)->content[0])))
        return (EXIT_FAILURE);
    else if (tmp[0] == GREATER && (tok->content)[0] == LESS)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
int is_invalid_tok_seq(char *tmp, t_token *tok)
{
    if (tok->next && (tmp[0] != OPAREN && tmp[0] != CPAREN )
        && ft_strcmp(tmp, tok->next->content))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
int is_invalid_oparen(char *tmp, t_token *tok, t_token *prev_tok)
{
    if (tmp[0] == OPAREN && (!(tok->next) 
        || (tok->next)->content[0] == CPAREN))
        return (EXIT_FAILURE);
    if (tmp[0] == OPAREN && (prev_tok != NULL 
        && (!schar_detected((prev_tok->content)[0]) 
        && ((prev_tok->content)[0] != GREATER 
        || (prev_tok->content)[0] != LESS))))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
int is_invalid_cparen(char *tmp, t_token *tok, t_token *prev_tok)
{
    if (tmp[0] == CPAREN && (tok->next 
        && (((tok->next->content)[0] == OPAREN) 
        || ((tok->next->content)[0] != GREATER 
        && (tok->next->content)[0] != LESS
        && !schar_detected((tok->next->content)[0])))))    
        return (EXIT_FAILURE);
    if (tmp[0] == CPAREN && ((tok->next 
        && (!schar_detected((tok->next->content)[0]) 
        && ((prev_tok->content)[0] != GREATER 
        || (prev_tok->content)[0] != LESS))) 
        || !check_redirection(tok->next)))
        return (EXIT_FAILURE);    
    return (EXIT_SUCCESS);
}
int check_redirection(t_token *tok)
{
    int red_count;
    int file_count;
    char *tmp;

    tmp = NULL;
    red_count = 0;
    file_count = 0;
    if (tok == NULL)
        return 1;
    while (tok != NULL)
    {
        tmp = tok->content;
        if ((tmp[0] != GREATER && tmp[0] != LESS) 
            && schar_detected(tmp[0]))
            break;
        if (tmp[0] == GREATER || tmp[0] == LESS)
            red_count++;
        else
            file_count++;
        tok = tok->next;
    }
    if (file_count != red_count)
        return 0;
    return 1;
}