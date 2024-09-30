#include "../../../includes/minishell.h"

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
    "AMBIGUOUS",
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

int print_error(char *error, int exit_code)
{
  ft_putstr_fd(error, 2);
  return (exit_code);
} 

t_token	*ft_lstnew_token(void *content)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
    token->content = content;
    token->lexem = STRING;
	token->next = NULL;
	return (token);
}

void print_lst(t_token *tokens)
{
    int i;

    i = 1;
    while (tokens != NULL)
    {
        printf("%d -> [%s | %s] \n", i++, tokens->content, lexs_type[tokens->lexem]);
        tokens = tokens->next;
    }
}

t_token	*ft_lstlast_token(t_token *lst)
{
	t_token	*node;

	node = NULL;
	while (lst)
	{
		if (lst->next == NULL)
			node = lst;
		lst = lst->next;
	}
	return (node);
}

void	ft_lstadd_token_back(t_token **lst, t_token *new)
{
	t_token	*token;

	if (new != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			token = *lst;
			while (token->next != NULL)
				token = token->next;
			token->next = new;
		}
	}
}

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

int rm_token_quotes(t_token *tokenlst)
{
  int flag;

  flag = 0;
  while (tokenlst != NULL)
  {
    if (flag == 0 && tokenlst->lexem == CMD 
      && ft_strcmp(tokenlst->content, "export"))
      flag = 1;
    else if (flag == 1 && is_schar(tokenlst->lexem) == 2)
      flag = 0;
    if (flag == 0)
    {
      tokenlst->content = remove_quote(tokenlst->content);
      if (tokenlst->content == NULL)
        return (print_error("malloc_error", 2));
    }
    tokenlst = tokenlst->next;
  }
  return (EXIT_SUCCESS);
}
