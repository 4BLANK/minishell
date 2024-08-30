#include "../../../includes/minishell.h"

void print_error(char *error, int exit_code)
{
    ft_putstr_fd(error, 2);
    exit(exit_code);
}

t_token	*ft_lstnew_token(void *content)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (0);
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

t_token *tokenizer(char *line)
{
  t_token *tokens;
  char *holder;
  int quote_flag;
  char quote_type;
  int stop_flag;
  int i;
  int j;

  i = 0;
  stop_flag = 0;
  quote_flag = 0;
  holder = NULL;
  tokens = NULL;
  while (line[i])
  {
    if (tokens != NULL && check_for_echo(tokens))
    {
      stop_flag = 0;
      j = i;
      while (line[i] && stop_flag == 0)
      {
        if (quote_flag == 0  && (line[i] == QUOTE || line[i] == DQUOTE))
        {
          quote_flag = 1;
          quote_type = line[i++];
        }
        if (quote_flag == 1 && line[i] == quote_type)
          quote_flag = 0;
        if (stop_flag == 0 && (line[i] == CPIPE || line[i] == GREATER
          || line[i] == LESS))
        {
          stop_flag = 1;
          break;
        }
        i++;
      }
      if (quote_flag == 1)
        print_error("close quote\n", 1);
      if (stop_flag == 1)
        i--;
      if (i != j)
      {
        holder = ft_substr(line, j, i - j);
        if (holder != NULL)
        {
          ft_lstadd_token_back(&tokens, ft_lstnew_token(holder));
          // printf("%s\n", holder);
        }
        // i = j;
      }
      // holder = ft_substr(line, j, i - j);
      // if (ft_strchr(holder, DQUOTE))
      //     holder = remove_quote(holder, DQUOTE);
      // else if (ft_strchr(holder, QUOTE))
      //     holder = remove_quote(holder, QUOTE);
      // ft_lstadd_token_back(&tokens, ft_lstnew_token(holder));

    }
    else if (line[i] && !is_space(line[i]))
    {
      j = i;
      while (line[j])
      {
        if (quote_flag == 0 && (line[j] == QUOTE || line[j] == DQUOTE))
        {
          quote_flag = 1;
          quote_type = line[j];
          j++;
        }
        if (quote_flag == 1 && line[j] == quote_type)
        {
          quote_flag = 0;
          if (line[j + 1] && is_space(line[j + 1]))
          {
            j++;
            break;
          }
        }
        if (is_space(line[j]) && quote_flag == 0)
          break;
        j++;
      }
      if (quote_flag == 1)
        print_error("close quote\n", 1); // quote close
      if (i != j)
      {
        holder = ft_substr(line, i, j - i);
        if (holder != NULL)
        {
          ft_lstadd_token_back(&tokens, ft_lstnew_token(holder));
          // printf("%s\n", holder);
        }
      }
      i = j;
      // if (ft_strchr(holder, DQUOTE))
      //     holder = remove_quote(holder, DQUOTE);
      // else if (ft_strchr(holder, QUOTE))
      //     holder = remove_quote(holder, QUOTE);
    }
    i++;
  }
  return (tokens);
}


void initial_parsing(char *line)
{
    int i;

    i = 0;
    while (line[i] && is_space(line[i]))
        i++;
    if(line[i] && line[i] == CPIPE)
        print_error("parse error\n", 1);
    while(line[i++]);
    i -= 2;
    while (i >= 0 && is_space(line[i]))
        i--;
    if (line[i] == CPIPE || line[i] == GREATER || line[i] == LESS 
        || (line[i] == AMPERSAND && line[i - 1] == AMPERSAND))
        print_error("parse error\n", 1);
}
