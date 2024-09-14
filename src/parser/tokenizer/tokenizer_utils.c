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

int is_all_quotes(char *str)
{
  size_t i;
  size_t quote_count;

  i = 0;
  quote_count = 0;
  if (str == NULL)
    return 0;
  while (str[i])
  {
    if (str[i] == QUOTE || str[i] == DQUOTE)
      quote_count++;
    i++;
  }
  if (quote_count == ft_strlen(str))
    return 1;
  return 0;
}

//TODO: handel echo command
int tokenizer(char *line, t_token **tokenlst)
{
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
  while (line[i])
  {
    if (*tokenlst != NULL && check_for_echo(*tokenlst))
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
        return (print_error("unclosed quote detected!\n", 2));
      if (stop_flag == 1)
        i--;
      if (i != j)
      {
        holder = ft_substr(line, j, i - j);
        if (holder != NULL)
          ft_lstadd_token_back(tokenlst, ft_lstnew_token(holder));
      }
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
        }
        else if (quote_flag == 1 && line[j] == quote_type)
        {
          quote_flag = 0;
          if (line[j + 1] && is_space(line[j + 1]))
          {
            j++;
            break;
          }
        }
        else if (is_space(line[j]) && quote_flag == 0)
        {
          break;
        }
        j++;
      }
      if (quote_flag == 1)
      {
        return (print_error("unclosed quote detected!\n", 2));
      }
      if (i != j)
      {
        holder = ft_substr(line, i, j - i);        
        if (holder != NULL /*&& !is_all_quotes(holder)*/)
          ft_lstadd_token_back(tokenlst, ft_lstnew_token(holder));
      }
      i = j;
    }
    if(line[i] != '\0')
      i++;
  }
  return (EXIT_SUCCESS);
}


int initial_parsing(char *line)
{ 
  int i;

  i = 0;
  if (line == NULL)
    return (EXIT_SUCCESS);
  while (line[i] && is_space(line[i]))
      i++;
  if(line[i] && line[i] == CPIPE)
      return (print_error("parse error\n", 2));
  while(line[i++]);
  i -= 2;
  while (i >= 0 && is_space(line[i]))
      i--;
  if (line[i] == CPIPE || line[i] == GREATER || line[i] == LESS 
      || (line[i] == AMPERSAND && line[i - 1] == AMPERSAND))
      return (print_error("parse error\n", 2));
  return (EXIT_SUCCESS);
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

void	tokens_lstclear(t_token **lst)
{
	t_token	*node;
	t_token	*next;

	if (lst && *lst)
	{
		node = *lst;
		while (node != NULL)
		{
			next = node->next;
		  free(node->content);
		  free(node);
			node = next;
		}
		*lst = NULL;
	}
}

int rm_token_quotes(t_token *tokenlst)
{
  while (tokenlst != NULL)
  {
    tokenlst->content = remove_quote(tokenlst->content);
    if (tokenlst->content == NULL)
      return (print_error("malloc_error", 2));
    tokenlst = tokenlst->next;
  }
  return (EXIT_SUCCESS);
}

t_token *tokendup(t_token *token)
{
  t_token *dup;

  if (token == NULL)
    return NULL;
  dup = ft_lstnew_token(ft_strdup(token->content));
  if (dup == NULL)
    return NULL;
  dup->lexem = token->lexem;
  dup->next = NULL;
  return dup;
}

void	ft_lstadd_token_front(t_token **lst, t_token *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

//use a stack
t_token *getlst(t_token *tokenlst)
{
  t_token *newlst;
  int flag;

  flag = 0;
  newlst = NULL;
  while (tokenlst != NULL && is_schar(tokenlst->lexem) != 2)
  {
    if (newlst == NULL)
      ft_lstadd_token_back(&newlst, tokendup(tokenlst));
    else
    {
      if (is_schar(tokenlst->lexem) == 1 || tokenlst->lexem == O_FILE 
        || tokenlst->lexem == DELIMITER)
        ft_lstadd_token_back(&newlst, tokendup(tokenlst));
      else if (newlst->lexem == CMD)
      {
        rotate(&newlst);
        ft_lstadd_token_front(&newlst, tokendup(tokenlst));
        reverse_rotate(&newlst);
      }
      else 
      {
        ft_lstadd_token_front(&newlst, tokendup(tokenlst));        
      }
    }
    tokenlst = tokenlst->next;
  }
  return newlst;
}

t_token *modify_redlst(t_token **tokenlst)
{
  t_token *new_token;
  t_token *tmp;
  int cmd_flag;

  cmd_flag = 0;
  tmp = *tokenlst;
  new_token = NULL;
  while (tmp != NULL)
  {
    if (redirection_found(tmp))
    {
      ft_lstadd_token_back(&new_token, getlst(tmp));
      while (tmp != NULL && is_schar(tmp->lexem) != 2)
        tmp = tmp->next;        
    }
    else 
    {
      ft_lstadd_token_back(&new_token, tokendup(tmp));      
      tmp = tmp->next;
    }
  }
  tokens_lstclear(tokenlst);
  return (new_token);
}

int delete_tokensnode(t_token **tokenlst, size_t position)
{
  size_t i;
  t_token *tmp;
  t_token *node;

  i = 0;
  if (*tokenlst == NULL)
    return EXIT_FAILURE;
  tmp = *tokenlst;

  if (position == 0)
  {
    *tokenlst = tmp->next;
    free(tmp);
    tmp = NULL;
    return (EXIT_SUCCESS);
  }
  else
  {
    while (tmp != NULL && i < position - 1)
    {
      tmp = tmp->next;
      i++;
    }
    if (tmp == NULL || tmp->next == NULL)
      return EXIT_FAILURE;
    node = tmp->next->next;
    free(tmp->next);
    tmp->next = node;
    tmp = NULL;
  }
  return EXIT_SUCCESS;
}