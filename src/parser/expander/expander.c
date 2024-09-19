#include "../../../includes/minishell.h"

// int expand_exitstatus()
// {

// }

char *get_name(char *str, int itr)
{
    char *env_name;
    int i;
    int len;
    
    i = itr;
    len = 0;
    while (str[i] && !is_space(str[i]) 
        && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
    {
        len++;
        i++;
    }
    env_name = ft_substr(str, itr, len);
    return env_name;
}

// char *ft_getenv(char *env_name, char **env)
// {
//     char *str;
//     int env_len;
//     int i;

//     i = 0;
//     str = NULL;
//     if (env_name == NULL || env_name [0] == '\0')
//         return NULL;
//     env_len = ft_strlen(env_name);
//     while (env[i] != NULL)
//     {
//         if (ft_strncmp(env[i], env_name, env_len) == 0)
//         {
//             str = ft_substr(env[i], env_len + 1, ft_strlen(env[i]) - env_len - 1);
//             break;
//         }
//         i++;
//     }
//     return (str);
// }

char	*concat(char *dest, char *src, int flag)
{
	char *new_dest;
    char *holder;
    int len;

    new_dest = NULL;
    holder = NULL;
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
    free(holder);
    //dest = NULL;
    return new_dest;
}

char *expand_pid_or_exit(char *str, char curchr, char nextchr)
{
    char *tmp;
    char *new_str;

    tmp = NULL;
    new_str = NULL;
    if (curchr && nextchr == DOLLAR_SIGN)
    {
        tmp = ft_itoa((int)getpid());
        new_str = concat(str, tmp, 0);
    }
    else if (curchr && nextchr == QUESTION_MARK)
    {
        tmp = ft_itoa(sh->ex_status);
        new_str = concat(str, tmp, 0);
    }
    free(tmp);
    return new_str;
}

char *expand_token(char *str)
{
    char *new_str;
    char *envname;
    char *s1;

    char quote_type;
    int quote_flag;
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
        if (quote_flag == 1 && str[i] == DOLLAR_SIGN && quote_type != QUOTE && str[i + 1]) 
        {
            new_str = expand_pid_or_exit(new_str, str[i], str[i + 1]);
            if (new_str != NULL)
                i++;
            envname = get_name(str, i + 1);
            s1 = ft_strdup(ft_getenv(envname));
            new_str = concat(new_str, s1, 0);
            i = i + ft_strlen(envname);
            free(s1);
            free(envname);
        }
        else
            new_str = concat(new_str, str + i, 1);
        i++;
    }
    free(str);
    return new_str;
}

char *expand_string(char *str)
{
    int i;
    char *envname;
    char *new_str;
    char *s1;
    char *tmp;
    char quote_type;
    int quote_flag;
    
    i = 0;
    quote_flag = 0;
    new_str = NULL;
    s1 = NULL;
    // if (ft_strcmp("~", str))
    //     return (ft_strdup(getenv("HOME")));
    // printf("expand string\n");
    while (str[i])
    {
        if (quote_flag == 0 && (str[i] == QUOTE || str[i] == DQUOTE))
        {
            quote_flag = 1;
            quote_type = str[i];
        }
        else if (quote_flag == 1 && str[i] == quote_type)
            quote_flag = 0;
        // if (quote_flag == 0 && str[i] == TILDE && str[i + 1] && str[i + 1] == '/')
        // {
        //     tmp = getenv("HOME");
        //     new_str = concat(new_str, tmp, 0);
        // }
        if (quote_flag == 0 && str[i] == DOLLAR_SIGN && str[i + 1] 
            && (str[i + 1] == QUESTION_MARK || ft_isalpha(str[i + 1])))
        {   
            //printf("1\n");
            tmp = expand_pid_or_exit(new_str, str[i], str[i + 1]);
            if (tmp != NULL)
            {
                // free(new_str);
                // new_str = NULL;
                new_str = tmp;
                //new_str = concat(new_str, tmp, 0);
                // free(tmp);
                i++;
            }
            else 
            {
                envname = get_name(str, i + 1);
                if (envname != NULL)
                {
                    s1 = ft_strdup(ft_getenv(envname));
                    new_str = concat(new_str, s1, 0);
                    i = i + ft_strlen(envname);
                    if (s1 != NULL && envname != NULL)
                    {
                        free(s1);
                        free(envname);
                    }
                }
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

t_token *expand_noquotes(t_token **head)
{
    t_token *tokens_list;
    t_token *tmp;
    t_token *tokens;
    char *str;
    int flag;

    flag = 0;
    tokens_list = NULL;
    tmp = NULL;
    tokens = *head;
    while (tokens != NULL)
    {
        // removes schars
        if (flag == 0 && tokens->lexem == CMD 
            && ft_strcmp(tokens->content, "export"))
            flag = 1;
        else if (flag == 1 && is_schar(tokens->lexem) != 0)
            flag = 0;
        if (flag == 0 && (is_schar(tokens->lexem) == 0 
            || tokens->lexem == O_FILE))
        {    
            if (tokens->lexem == STRING || tokens->lexem == CMD 
                || tokens->lexem == O_FILE || tokens->lexem == ARG)
            {
                str = expand_string(tokens->content);
                tmp = split_tokens(str);
                free(str);
                if (tmp != NULL)
                {
                    tmp->lexem = tokens->lexem;
                    ft_lstadd_token_back(&tokens_list, tmp);
                }
            }
        }
        else 
        {
            tmp = ft_lstnew_token(ft_strdup(tokens->content));
            tmp->lexem = tokens->lexem;
            tmp->next = NULL;
            ft_lstadd_token_back(&tokens_list, tmp);
        }
        tokens = tokens->next;
    }
    tokens_lstclear(head);

    // printf(RED"\n-------------------------\n");
    // print_lst(tokens_list);
    // printf("\n-------------------------\n"RESET);

    return (tokens_list);
}

int is_quoted(char *str)
{
    size_t i;

    i = 0;
    if (str == NULL || str[i] == '=')
        return true;
    while (str[i] && str[i] != '=')
    {
        if (str[i] == DQUOTE || str[i] == DQUOTE)
            return true; 
        i++;
    }
    return false;
}

// int set_envlist(t_token **tokenlst, char ***env)
// {
//     t_token *tmp;
//     size_t position;
//     char **args;

//     args = NULL;
//     position = 0;
//     tmp = *tokenlst;
//     while (tmp != NULL)
//     {
//         if (tmp->lexem == CMD && ft_strchr(tmp->content, '=') != NULL && !is_quoted(tmp->content))
//         {
//             args = lst_tostrarray(args_table(&tmp, ARGUMENTS));
//             if (args == NULL || export_cmd(args, env, 0) 
//                 || delete_tokensnode(tokenlst, position))
//             {
//                 free(args);
//                 return EXIT_FAILURE;
//             }
//             free_strarray(args);
//         }else
//         {
//             position++;
//             tmp = tmp->next;
//         }
//     }
//     return (EXIT_SUCCESS);
// }

int expander(t_token **tokens)
{
    t_token *tmp;
    int flag;

    // if (set_envlist(tokens, env))
    //     return (EXIT_FAILURE);
    flag = 0;
    tmp = (*tokens);
    while ((*tokens) != NULL)
    {
        if (flag == 0 && (*tokens)->lexem == CMD 
            && ft_strcmp((*tokens)->content, "export"))
            flag = 1;
        else if (flag == 1 && is_schar((*tokens)->lexem) != 0)
            flag = 0;
        if (!(flag == 1 && (*tokens)->lexem == ARG))
        {
            if ((*tokens)->lexem == STRING || (*tokens)->lexem == ARG 
                || (*tokens)->lexem == CMD || (*tokens)->lexem == O_FILE)
                (*tokens)->content = expand_token((*tokens)->content);
        }
        *tokens = (*tokens)->next;
    }
    *tokens = tmp;
    lexer(*tokens);     
    if (rm_token_quotes(*tokens))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
