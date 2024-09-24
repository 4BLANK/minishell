#include "../../../includes/minishell.h"

int s_error(char *tmp)
{
    (void)tmp;
    ft_putstr_fd("changal :syntax error\n", 2);
    // ft_putchar_fd(tmp[0], 2);
    // ft_putchar_fd('\n', 2);
    return (EXIT_FAILURE);
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

int is_invalid_pipe_and(char *tmp, t_token *tok, t_token *prev_tok)
{
    if ((tmp[0] == CPIPE || tmp[0] == AMPERSAND) 
        && (!prev_tok || !(tok->next)))      
    {
        printf("1\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
int is_invalid_greater_less(char *tmp, t_token *tok)
{
    if ((tmp[0] == GREATER || tmp[0] == LESS) && (!(tok->next) 
        || schar_detected((tok->next)->content[0])))
    {
        printf("1\n");
        return (EXIT_FAILURE);
    }
    else if (tmp[0] == GREATER && (tok->content)[0] == LESS)
    {
        printf("2\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
int is_invalid_tok_seq(char *tmp, t_token *tok)
{
    if (tok->next && (tmp[0] != OPAREN && tmp[0] != CPAREN )
        && ft_strcmp(tmp, tok->next->content))
    {
        printf("1\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
int is_invalid_oparen(char *tmp, t_token *tok, t_token *prev_tok)
{
    if (tmp[0] == OPAREN && (!(tok->next) 
        || (tok->next)->content[0] == CPAREN))
    {
        printf("1\n");
        return (EXIT_FAILURE);
    }
    if (tmp[0] == OPAREN && (prev_tok != NULL 
        && (!schar_detected((prev_tok->content)[0]) 
        && ((prev_tok->content)[0] != GREATER 
        || (prev_tok->content)[0] != LESS))))
    {
        printf("2\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
int is_invalid_cparen(char *tmp, t_token *tok, t_token *prev_tok)
{
    if (tmp[0] == CPAREN && (tok->next 
        && (((tok->next->content)[0] == OPAREN) 
        || ((tok->next->content)[0] != GREATER 
        && (tok->next->content)[0] != LESS
        && !schar_detected((tok->next->content)[0])))))    
    {
        printf("1\n");
        return (EXIT_FAILURE);
    }
    if (tmp[0] == CPAREN && ((tok->next 
        && (!schar_detected((tok->next->content)[0]) 
        && ((prev_tok->content)[0] != GREATER 
        || (prev_tok->content)[0] != LESS))) 
        || !check_redirection(tok->next)))
    {        
        printf("2\n");
        return (EXIT_FAILURE);    
    }    
    return (EXIT_SUCCESS);
}

int is_invalid_special_char(char *tmp, t_token *tok, t_token *prev_tok)
{
    if (ft_strlen(tmp) > 2)
    {
        printf("1\n");
        return (EXIT_FAILURE);
    }
    if (is_invalid_pipe_and(tmp, prev_tok, tok))
    {
        printf("2\n");
        return (EXIT_FAILURE);
    }
    if (is_invalid_greater_less(tmp, tok))
    {
        printf("3\n");
        return (EXIT_FAILURE);
    }
    if (is_invalid_tok_seq(tmp, tok))
    {
        printf("4\n");
        return (EXIT_FAILURE);
    }
    if (tmp[0] == OPAREN && is_invalid_oparen(tmp, tok, prev_tok))
    {
        printf("5\n");
        return (EXIT_FAILURE);
    }
    if (tmp[0] == CPAREN && is_invalid_cparen(tmp, tok, prev_tok))
    {
        printf("6\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int syntax_err_check(t_token *tokenlst)
{
  t_token *tok;
  t_token *prev_tok;
  char *content;
  int status;

  tok = tokenlst;
  prev_tok = NULL;
  content = NULL;
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
        status = here_doc(&(tok->next)->content);
        if (status != 0)
            return (status);
    }
    prev_tok = tok;
    tok = tok->next;
  }
  return (EXIT_SUCCESS);
}

void distroy_tmps(t_tmps **lst)
{
	t_tmps	*node;
	t_tmps	*next;

	if (lst && *lst)
	{
		node = *lst;
		while (node != NULL)
		{
			next = node->next;
			unlink(node->filename);
		    free(node);
			node = next;
		}
		*lst = NULL;
	}
}