#include "../../../includes/minishell.h"

int s_error(char *tmp)
{
    (void)tmp;
    ft_putstr_fd("changal :syntax error\n", 2);
    return (EXIT_FAILURE);
}

int chack_parn(t_token *tokenlst)
{
    t_token *tok;
    char *tmp;
    int p_count;

    tok = tokenlst;
    tmp = NULL;
    p_count = 0;
    while (tok != NULL)
    {
        tmp = tok->content;
        if (tmp[0] == OPAREN)
        p_count++;
        else if (tmp[0] == CPAREN)
        p_count--;
        tok = tok->next;
    }
    if (p_count > 0)
        return (s_error(")"));
    else if (p_count < 0)
        return (s_error("("));    
    return (EXIT_SUCCESS);
}

int is_quoted(char *str)
{
    size_t i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i])
    {
        if (str[i] == QUOTE || str[i] == DQUOTE)
            return (1);
        i++;
    }
    return (0);
}

int validate_token(t_token *tokenlst)
{
  t_token *tok;
  t_token *prev_tok;
  char *content;
  int status;
  int flag;

  tok = tokenlst;
  prev_tok = NULL;
  content = NULL;
  flag = 0;
  if (chack_parn(tok))
    return (EXIT_FAILURE);
  while (tok != NULL)
  {
    content = tok->content;
    if (schar_detected(content[0]))
    {
      if (is_invalid_special_char(content, tok, prev_tok))
        return (s_error(content));
    }
    if (ft_strcmp(content, "<<"))
    {
        if (!is_quoted((tok->next)->content))
            flag = 1;
        (tok->next)->content = remove_quote((tok->next)->content); 
        status = here_doc(&(tok->next)->content, flag);
        if (status != 0)
            return (status);
    }
    prev_tok = tok;
    tok = tok->next;
  }
  return (EXIT_SUCCESS);
}
