#include "../../../includes/minishell.h"

t_envlist *lstnew_env(char *name, char *value)
{
	t_envlist	*token;

	token = (t_envlist *)malloc(sizeof(t_envlist));
	if (token == NULL)
		return (NULL);
    token->name = name;
    token->value = value;
	token->next = NULL;
	return (token);
}

void    lstadd_env_back(t_envlist **lst, t_envlist *newenv)
{
	t_envlist	*token;

	if (newenv != NULL)
	{
		if (*lst == NULL)
			*lst = newenv;
		else
		{
			token = *lst;
			while (token->next != NULL)
				token = token->next;
			token->next = newenv;
		}
	}
}

char *getenv_name(char *variable)
{
    char *var_name;
    size_t i;
    
    i = 0;
    if (variable == NULL)
        return NULL;
    while (variable[i] && variable[i] != '=')
        i++;
    var_name = ft_substr(variable, 0, i);
    return (var_name);
}

char *getenv_value(char *variable)
{
    char *value;
    size_t start;

    start = 0;
    value = NULL;
    if (variable == NULL)
        return NULL;
    while (variable[start] && variable[start] != '=')
        start++;
    value = ft_substr(variable, start + 1, ft_strlen(variable) - start);
    return (value);
}

void print_env(t_envlist *envlst)
{
    while (envlst != NULL)
    {
        printf("declare -x %s=\"%s\"\n", envlst->name, envlst->value);
        envlst = envlst->next;
    }
}

void distroy_envlst(t_envlist **envlst)
{
	t_envlist	*node;
	t_envlist	*next;

	if (envlst && *envlst)
	{
		node = *envlst;
		while (node != NULL)
		{
		    next = node->next;
		    free(node->name);
            free(node->value);
		    free(node);
			node = next;
		}
		*envlst = NULL;
	}
}

char *ft_getenv(char *name)
{
    t_envlist *lst;

    lst = sh->envlst;
    if (name == NULL || name [0] == '\0')
        return NULL;
    while (lst != NULL)
    {
        if (ft_strcmp(name, lst->name))
            return (lst->value);
        lst = lst->next;
    }
    return (NULL);
}

t_envlist *init_envlist(char **env)
{
    t_envlist *envlst;
    t_envlist *tmp;
    size_t i;
    
    i = 0;
    envlst = NULL;
    tmp = NULL;
    while (env[i])
    {
        tmp = lstnew_env(getenv_name(env[i]), getenv_value(env[i]));
        lstadd_env_back(&envlst, tmp);
        i++;
    }
    return (envlst);
}
