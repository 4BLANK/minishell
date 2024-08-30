#include "../../../includes/minishell.h"

char *get_envname(char *str, int itr)
{
    char *env_name;
    int i;
    int len;
    
    i = itr;
    len = 0;
    while (str[i] && !is_space(str[i]) && ft_isalpha(str[i]))
    {
        len++;
        i++;
    }
    env_name = ft_substr(str, itr, len);
    return env_name;
}

char *ft_getenv(char *env_name, char **env)
{
    char *str;
    int env_len;
    int i;

    i = 0;
    str = NULL;
    env_len = ft_strlen(env_name);
    while (env[i] != NULL)
    {
        if (ft_strncmp(env[i], env_name, env_len) == 0)
        {
            str = ft_substr(env[i], env_len + 1, ft_strlen(env[i]) - env_len - 1);
            break;
        }
        i++;
    }
    return (str);
}

char	*concat(char *dest, char *src, int flag)
{
	char *new_dest;
    char *holder;
    int i;
    int len;

    i = 0;
    new_dest = NULL;
    if (flag == 1)
    {
        holder = malloc(2);
        holder[0] = src[0];
        holder[1] = '\0';
    }
    if (!dest && !src)
		return (NULL);
	if (src == NULL)
		return (dest);
	if (dest == NULL)
    {
        if (flag == 1)
            return (holder);
		return (ft_strdup(src));
    }
	len = ft_strlen(dest) + ft_strlen(src) + 1;
	new_dest = (char *)malloc(len * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(new_dest, dest, len);
    if (flag == 1)
	    ft_strlcat(new_dest, holder, len);
    else
    	ft_strlcat(new_dest, src, len);
    free(dest);
    return new_dest;
}


char *expand_token(char *str, char **env)
{
    char *new_str;
    char *s1;
    char quote_type;
    int quote_flag;
    char *envname;
    int i;

    i = 0;
    quote_flag = 0;
    new_str = NULL;
    while (str[i])
    {
        if (quote_flag == 0 && (str[i] == QUOTE || str[i] == DQUOTE))
        {
            quote_flag = 1;
            quote_type = str[i];
        }
        else if (quote_flag == 1 && str[i] == quote_type)
            quote_flag = 0;
        if (quote_flag == 1 && str[i] == DOLLAR_SIGN && quote_type != QUOTE) 
        {
            envname = get_envname(str, i + 1);
            s1 = ft_getenv(envname, env);
            new_str = concat(new_str, s1, 0);
            i = i + ft_strlen(envname);
            if (s1 != NULL && envname != NULL)
            {
                free(s1);
                free(envname);
            }
        }
        else
            new_str = concat(new_str, str + i, 1);
        i++;
    }
    free(str);
    return new_str;
}

char *expand_string(char *str, char **env)
{
    int i;
    char *envname;
    char *new_str;
    char *s1;
    char quote_type;
    int quote_flag;
    
    i = 0;
    quote_flag = 0;
    new_str = NULL;
    s1 = NULL;
    while (str[i])
    {
        if (quote_flag == 0 && (str[i] == QUOTE || str[i] == DQUOTE))
        {
            quote_flag = 1;
            quote_type = str[i];
        }
        else if (quote_flag == 1 && str[i] == quote_type)
            quote_flag = 0;
        if (quote_flag == 0 && str[i] == DOLLAR_SIGN)
        {
            envname = get_envname(str, i + 1);
            s1 = ft_getenv(envname, env);
            new_str = concat(new_str, s1, 0);
            i = i + ft_strlen(envname);
            if (s1 != NULL && envname != NULL)
            {
                free(s1);
                free(envname);
            }
        }
        else
            new_str = concat(new_str, str + i, 1);
        i++;
    }
    return new_str;
}

t_token *split_tokens(char *str)
{
    int i;
    int j;
    int quote_flag;
    char quote_type;
    t_token *tokens;
    char *holder;

    i = 0;
    tokens = NULL;
    quote_flag = 0;
    while (str[i])
    {
        if (str[i] && !is_space(str[i]))
        {
            j = i;
            while (str[i])
            {
                if (quote_flag == 0 && (str[i] == QUOTE || str[i] == DQUOTE))
                {
                    quote_flag = 1;
                    quote_type = str[i];
                }
                else if (quote_flag == 1 && str[i] == quote_type)
                {
                    quote_flag = 0;
                    if (str[i + 1] && is_space(str[i + 1]))
                    {
                        i++;
                        break;
                    }
                }
                else if (is_space(str[i]) && quote_flag == 0)
                    break;
                i++;
            }
            if (i != j)
            {
                holder = ft_substr(str, j, i - j);
                if (holder != NULL)
                    ft_lstadd_token_back(&tokens, ft_lstnew_token(holder));
            }
        }
        if (str[i] != '\0')
            i++;
    }
    return tokens;
}

t_token *expand_noquotes(t_token **head, char **env)
{
    t_token *tokes_list;
    t_token *tmp;
    t_token *tokens;
    char *str;

    tokes_list = NULL;
    tmp = NULL;
    tokens = *head;
    while (tokens != NULL)
    {
        if (tokens->lexem == STRING || tokens->lexem == CMD 
            || tokens->lexem == O_FILE || tokens->lexem == ARG)
        {
            str = expand_string(tokens->content, env);
            tmp = split_tokens(str);
            tmp->lexem = tokens->lexem;
            ft_lstadd_token_back(&tokes_list, tmp);
            free(str);
        }
        else 
        {
            tmp = ft_lstnew_token(ft_strdup(tokens->content));
            tmp->lexem = tokens->lexem;
            tmp->next = NULL;
            ft_lstadd_token_back(&tokes_list, tmp);
        }
        tokens = tokens->next;
    }
    tokens_lstclear(head);
    return (tokes_list);
}

int expander(t_token **tokens, char **env)
{
    t_token *tmp;

    tmp = (*tokens);
    while ((*tokens) != NULL)
    {
        if ((*tokens)->lexem == STRING || (*tokens)->lexem == ARG 
            || (*tokens)->lexem == CMD || (*tokens)->lexem == O_FILE)
            (*tokens)->content = expand_token((*tokens)->content, env);
        *tokens = (*tokens)->next;
    }
    *tokens = tmp;
    lexer(*tokens);
    if (rm_token_quotes(*tokens))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}